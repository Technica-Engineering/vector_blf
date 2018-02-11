/*
 * Copyright (C) 2013 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#include <Vector/BLF/File.h>

#include <cstring>

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

File::File() :
    fileStatistics(),
    currentUncompressedFileSize(0),
    currentObjectCount(0),
    compressionLevel(6),
    writeUnknown115(true),
    m_openMode(),
    m_readWriteQueue(),
    m_uncompressedFile(),
    m_uncompressedFileThread(),
    m_uncompressedFileThreadRunning(),
    m_compressedFile(),
    m_compressedFileThread(),
    m_compressedFileThreadRunning()
{
    /* set performance/memory values */
    m_readWriteQueue.setMaxSize(10);
    m_uncompressedFile.setMaxFileSize(m_uncompressedFile.defaultLogContainerSize());
}

File::~File()
{
    close();
}

ULONGLONG File::currentFileSize()
{
    return static_cast<ULONGLONG>(m_compressedFile.tellp());
}

void File::open(const char * filename, std::ios_base::openmode mode)
{
    /* check */
    if (is_open()) {
        return;
    }

    /* try to open file */
    mode |= std::ios_base::binary;
    m_compressedFile.open(filename, mode);
    if (!m_compressedFile.is_open()) {
        return;
    }
    m_openMode = mode;

    /* open queue */
    m_readWriteQueue.open();
    m_uncompressedFile.open();

    /* read */
    if (mode & std::ios_base::in) {
        /* read file statistics */
        fileStatistics.read(m_compressedFile);

        /* fileStatistics done */
        currentUncompressedFileSize += fileStatistics.statisticsSize;

        /* prepare threads */
        m_uncompressedFileThreadRunning = true;
        m_compressedFileThreadRunning = true;

        /* create read threads */
        m_uncompressedFileThread = std::thread(uncompressedFileReadThread, this);
        m_compressedFileThread = std::thread(compressedFileReadThread, this);
    } else

    /* write */
    if (mode & std::ios_base::out) {
        /* write file statistics */
        fileStatistics.write(m_compressedFile);

        /* fileStatistics done */
        currentUncompressedFileSize += fileStatistics.statisticsSize;

        /* prepare threads */
        m_uncompressedFileThreadRunning = true;
        m_compressedFileThreadRunning = true;

        /* create write threads */
        m_uncompressedFileThread = std::thread(uncompressedFileWriteThread, this);
        m_compressedFileThread = std::thread(compressedFileWriteThread, this);
    }
}

void File::open(const std::string & filename, std::ios_base::openmode mode)
{
    open(filename.c_str(), mode);
}

bool File::is_open() const
{
    return m_compressedFile.is_open();
}

bool File::eof()
{
    return
        m_readWriteQueue.eof() &&
        m_uncompressedFile.eof();
        // @todo compressedFile.eof is not multi-thread safe, so don't use it here: m_compressedFile.eof();
}

ObjectHeaderBase * File::read()
{
    /* read object */
    ObjectHeaderBase * ohb = m_readWriteQueue.read();

    return ohb;
}

void File::write(ObjectHeaderBase * ohb)
{
    /* push to queue */
    m_readWriteQueue.write(ohb);
}

void File::close()
{
    /* check if file is open */
    if (!is_open()) {
        return;
    }

    /* read */
    if (m_openMode & std::ios_base::in) {
        /* finalize compressedFile thread */
        m_compressedFileThreadRunning = false;
        m_compressedFile.close();
        if (m_compressedFileThread.joinable()) {
            m_compressedFileThread.join();
        }

        /* finalize uncompressedFile thread */
        m_uncompressedFileThreadRunning = false;
        m_uncompressedFile.close();
        if (m_uncompressedFileThread.joinable()) {
            m_uncompressedFileThread.join();
        }

        m_readWriteQueue.close();
    } else

    /* write */
    if (m_openMode & std::ios_base::out) {
        m_readWriteQueue.setTotalObjectCount(m_readWriteQueue.tellp()); // eof

        /* wait till readWriteQueue is empty */
        m_readWriteQueue.flush();
        m_readWriteQueue.close();

        /* finalize uncompression thread */
        if (m_uncompressedFileThread.joinable()) {
            m_uncompressedFileThread.join();
        }
        if (m_readWriteQueue.size() > 0) {
            throw Exception("File::close(): readWriteQueue not empty");
        }
        if (m_uncompressedFileThreadRunning) {
            throw Exception("File::close(): uncompressedFileThread still running");
        }

        /* wait till uncompressedFile is empty */
        m_uncompressedFile.flush();
        m_uncompressedFile.close();

        /* finalize compression thread */
        if (m_compressedFileThread.joinable()) {
            m_compressedFileThread.join();
        }
        if (m_uncompressedFile.size() > 0) {
            throw Exception("File::close(): uncompressedFile not empty");
        }
        if (m_compressedFileThreadRunning) {
            throw Exception("File::close(): compressedFileThread still running");
        }

        /* write final LogContainer+Unknown115 */
        if (writeUnknown115) {
            fileStatistics.fileSizeWithoutUnknown115 = currentFileSize();

            /* write end of file message */
            Unknown115 * unknown115 = new Unknown115;
            m_readWriteQueue.write(unknown115);
            readWriteQueue2UncompressedFile();
            uncompressedFile2CompressedFile();
        }

        /* set file statistics */
        fileStatistics.fileSize = currentFileSize();
        fileStatistics.uncompressedFileSize = currentUncompressedFileSize;
        fileStatistics.objectCount = currentObjectCount;
        // @todo fileStatistics.objectsRead = ?

        /* write file statistics */
        m_compressedFile.seekp(0);
        fileStatistics.write(m_compressedFile);

        /* close file */
        m_compressedFile.flush();
        m_compressedFile.close();
    }
}

DWORD File::defaultLogContainerSize() const
{
    return m_uncompressedFile.defaultLogContainerSize();
}

void File::setDefaultLogContainerSize(DWORD defaultLogContainerSize)
{
    m_uncompressedFile.setDefaultLogContainerSize(defaultLogContainerSize);
}

ObjectHeaderBase * File::createObject(ObjectType type)
{
    ObjectHeaderBase * obj = nullptr;

    switch (type) {
    case ObjectType::UNKNOWN:
        break;

    case ObjectType::CAN_MESSAGE:
        obj = new CanMessage();
        break;

    case ObjectType::CAN_ERROR:
        obj = new CanErrorFrame();
        break;

    case ObjectType::CAN_OVERLOAD:
        obj = new CanOverloadFrame();
        break;

    case ObjectType::CAN_STATISTIC:
        obj = new CanDriverStatistic();
        break;

    case ObjectType::APP_TRIGGER:
        obj = new AppTrigger();
        break;

    case ObjectType::ENV_INTEGER:
    case ObjectType::ENV_DOUBLE:
    case ObjectType::ENV_STRING:
    case ObjectType::ENV_DATA:
        obj = new EnvironmentVariable();
        break;

    case ObjectType::LOG_CONTAINER:
        obj = new LogContainer();
        break;

    case ObjectType::LIN_MESSAGE:
        obj = new LinMessage();
        break;

    case ObjectType::LIN_CRC_ERROR:
        obj = new LinCrcError();
        break;

    case ObjectType::LIN_DLC_INFO:
        obj = new LinDlcInfo();
        break;

    case ObjectType::LIN_RCV_ERROR:
        obj = new LinReceiveError();
        break;

    case ObjectType::LIN_SND_ERROR:
        obj = new LinSendError();
        break;

    case ObjectType::LIN_SLV_TIMEOUT:
        obj = new LinSlaveTimeout();
        break;

    case ObjectType::LIN_SCHED_MODCH:
        obj = new LinSchedulerModeChange();
        break;

    case ObjectType::LIN_SYN_ERROR:
        obj = new LinSyncError();
        break;

    case ObjectType::LIN_BAUDRATE:
        obj = new LinBaudrateEvent();
        break;

    case ObjectType::LIN_SLEEP:
        obj = new LinSleepModeEvent();
        break;

    case ObjectType::LIN_WAKEUP:
        obj = new LinWakeupEvent();
        break;

    case ObjectType::MOST_SPY:
        obj = new MostSpy();
        break;

    case ObjectType::MOST_CTRL:
        obj = new MostCtrl();
        break;

    case ObjectType::MOST_LIGHTLOCK:
        obj = new MostLightLock();
        break;

    case ObjectType::MOST_STATISTIC:
        obj = new MostStatistic();
        break;

    case ObjectType::Reserved26:
    case ObjectType::Reserved27:
    case ObjectType::Reserved28:
        break;

    case ObjectType::FLEXRAY_DATA:
        obj = new FlexRayData();
        break;

    case ObjectType::FLEXRAY_SYNC:
        obj = new FlexRaySync();
        break;

    case ObjectType::CAN_DRIVER_ERROR:
        obj = new CanDriverError();
        break;

    case ObjectType::MOST_PKT:
        obj = new MostPkt();
        break;

    case ObjectType::MOST_PKT2:
        obj = new MostPkt2();
        break;

    case ObjectType::MOST_HWMODE:
        obj = new MostHwMode();
        break;

    case ObjectType::MOST_REG:
        obj = new MostReg();
        break;

    case ObjectType::MOST_GENREG:
        obj = new MostGenReg();
        break;

    case ObjectType::MOST_NETSTATE:
        obj = new MostNetState();
        break;

    case ObjectType::MOST_DATALOST:
        obj = new MostDataLost();
        break;

    case ObjectType::MOST_TRIGGER:
        obj = new MostTrigger();
        break;

    case ObjectType::FLEXRAY_CYCLE:
        obj = new FlexRayV6StartCycleEvent();
        break;

    case ObjectType::FLEXRAY_MESSAGE:
        obj = new FlexRayV6Message();
        break;

    case ObjectType::LIN_CHECKSUM_INFO:
        obj = new LinChecksumInfo();
        break;

    case ObjectType::LIN_SPIKE_EVENT:
        obj = new LinSpikeEvent();
        break;

    case ObjectType::CAN_DRIVER_SYNC:
        obj = new CanDriverHwSync();
        break;

    case ObjectType::FLEXRAY_STATUS:
        obj = new FlexRayStatusEvent();
        break;

    case ObjectType::GPS_EVENT:
        obj = new GpsEvent();
        break;

    case ObjectType::FR_ERROR:
        obj = new FlexRayVFrError();
        break;

    case ObjectType::FR_STATUS:
        obj = new FlexRayVFrStatus();
        break;

    case ObjectType::FR_STARTCYCLE:
        obj = new FlexRayVFrStartCycle();
        break;

    case ObjectType::FR_RCVMESSAGE:
        obj = new FlexRayVFrReceiveMsg();
        break;

    case ObjectType::REALTIMECLOCK:
        obj = new RealtimeClock();
        break;

    case ObjectType::Reserved52:
    case ObjectType::Reserved53:
        break;

    case ObjectType::LIN_STATISTIC:
        obj = new LinStatisticEvent();
        break;

    case ObjectType::J1708_MESSAGE:
    case ObjectType::J1708_VIRTUAL_MSG:
        obj = new J1708Message();
        break;

    case ObjectType::LIN_MESSAGE2:
        obj = new LinMessage2();
        break;

    case ObjectType::LIN_SND_ERROR2:
        obj = new LinSendError2();
        break;

    case ObjectType::LIN_SYN_ERROR2:
        obj = new LinSyncError2();
        break;

    case ObjectType::LIN_CRC_ERROR2:
        obj = new LinCrcError2();
        break;

    case ObjectType::LIN_RCV_ERROR2:
        obj = new LinReceiveError2();
        break;

    case ObjectType::LIN_WAKEUP2:
        obj = new LinWakeupEvent2();
        break;

    case ObjectType::LIN_SPIKE_EVENT2:
        obj = new LinSpikeEvent2();
        break;

    case ObjectType::LIN_LONG_DOM_SIG:
        obj = new LinLongDomSignalEvent();
        break;

    case ObjectType::APP_TEXT:
        obj = new AppText();
        break;

    case ObjectType::FR_RCVMESSAGE_EX:
        obj = new FlexRayVFrReceiveMsgEx();
        break;

    case ObjectType::MOST_STATISTICEX:
        obj = new MostStatisticEx();
        break;

    case ObjectType::MOST_TXLIGHT:
        obj = new MostTxLight();
        break;

    case ObjectType::MOST_ALLOCTAB:
        obj = new MostAllocTab();
        break;

    case ObjectType::MOST_STRESS:
        obj = new MostStress();
        break;

    case ObjectType::ETHERNET_FRAME:
        obj = new EthernetFrame();
        break;

    case ObjectType::SYS_VARIABLE:
        obj = new SystemVariable();
        break;

    case ObjectType::CAN_ERROR_EXT:
        obj = new CanErrorFrameExt();
        break;

    case ObjectType::CAN_DRIVER_ERROR_EXT:
        obj = new CanDriverErrorExt();
        break;

    case ObjectType::LIN_LONG_DOM_SIG2:
        obj = new LinLongDomSignalEvent2();
        break;

    case ObjectType::MOST_150_MESSAGE:
        obj = new Most150Message();
        break;

    case ObjectType::MOST_150_PKT:
        obj = new Most150Pkt();
        break;

    case ObjectType::MOST_ETHERNET_PKT:
        obj = new MostEthernetPkt();
        break;

    case ObjectType::MOST_150_MESSAGE_FRAGMENT:
        obj = new Most150MessageFragment();
        break;

    case ObjectType::MOST_150_PKT_FRAGMENT:
        obj = new Most150PktFragment();
        break;

    case ObjectType::MOST_ETHERNET_PKT_FRAGMENT:
        obj = new MostEthernetPktFragment();
        break;

    case ObjectType::MOST_SYSTEM_EVENT:
        obj = new MostSystemEvent();
        break;

    case ObjectType::MOST_150_ALLOCTAB:
        obj = new Most150AllocTab();
        break;

    case ObjectType::MOST_50_MESSAGE:
        obj = new Most50Message();
        break;

    case ObjectType::MOST_50_PKT:
        obj = new Most50Pkt();
        break;

    case ObjectType::CAN_MESSAGE2:
        obj = new CanMessage2();
        break;

    case ObjectType::LIN_UNEXPECTED_WAKEUP:
        obj = new LinUnexpectedWakeup();
        break;

    case ObjectType::LIN_SHORT_OR_SLOW_RESPONSE:
        obj = new LinShortOrSlowResponse();
        break;

    case ObjectType::LIN_DISTURBANCE_EVENT:
        obj = new LinDisturbanceEvent();
        break;

    case ObjectType::SERIAL_EVENT:
        obj = new SerialEvent();
        break;

    case ObjectType::OVERRUN_ERROR:
        obj = new DriverOverrun();
        break;

    case ObjectType::EVENT_COMMENT:
        obj = new EventComment();
        break;

    case ObjectType::WLAN_FRAME:
        obj = new WlanFrame();
        break;

    case ObjectType::WLAN_STATISTIC:
        obj = new WlanStatistic();
        break;

    case ObjectType::MOST_ECL:
        obj = new MostEcl();
        break;

    case ObjectType::GLOBAL_MARKER:
        obj = new GlobalMarker();
        break;

    case ObjectType::AFDX_FRAME:
        obj = new AfdxFrame();
        break;

    case ObjectType::AFDX_STATISTIC:
        obj = new AfdxStatistic();
        break;

    case ObjectType::KLINE_STATUSEVENT:
        obj = new KLineStatusEvent();
        break;

    case ObjectType::CAN_FD_MESSAGE:
        obj = new CanFdMessage();
        break;

    case ObjectType::CAN_FD_MESSAGE_64:
        obj = new CanFdMessage64();
        break;

    case ObjectType::ETHERNET_RX_ERROR:
        obj = new EthernetRxError();
        break;

    case ObjectType::ETHERNET_STATUS:
        obj = new EthernetStatus();
        break;

    case ObjectType::CAN_FD_ERROR_64:
        obj = new CanFdErrorFrame64();
        break;

    case ObjectType::LIN_SHORT_OR_SLOW_RESPONSE2:
        obj = new LinShortOrSlowResponse2;
        break;

    case ObjectType::AFDX_STATUS:
        obj = new AfdxStatus;
        break;

    case ObjectType::AFDX_BUS_STATISTIC:
        obj = new AfdxBusStatistic;
        break;

    case ObjectType::Reserved108:
        break;

    case ObjectType::AFDX_ERROR_EVENT:
        obj = new AfdxErrorEvent;
        break;

    case ObjectType::A429_ERROR:
        obj = new A429Error;
        break;

    case ObjectType::A429_STATUS:
        obj = new A429Status;
        break;

    case ObjectType::A429_BUS_STATISTIC:
        obj = new A429BusStatistic;
        break;

    case ObjectType::A429_MESSAGE:
        obj = new A429Message;
        break;

    case ObjectType::ETHERNET_STATISTIC:
        obj = new EthernetStatistic;
        break;

    case ObjectType::Unknown115:
        obj = new Unknown115;
        break;

    case ObjectType::Reserved116:
    case ObjectType::Reserved117:
        break;

    case ObjectType::TEST_STRUCTURE:
        obj = new TestStructure;
        break;

    case ObjectType::DIAG_REQUEST_INTERPRETATION:
        obj = new DiagRequestInterpretation;
        break;

    case ObjectType::ETHERNET_FRAME_EX:
        obj = new EthernetFrameEx;
        break;

    case ObjectType::ETHERNET_FRAME_FORWARDED:
        obj = new EthernetFrameForwarded;
        break;

    case ObjectType::ETHERNET_ERROR_EX:
        obj = new EthernetErrorEx;
        break;

    case ObjectType::ETHERNET_ERROR_FORWARDED:
        obj = new EthernetErrorForwarded;
        break;
    }

    return obj;
}

void File::uncompressedFile2ReadWriteQueue()
{
    /* identify type */
    ObjectHeaderBase ohb;
    ohb.read(m_uncompressedFile);
    if (m_uncompressedFile.eof()) {
        return;
    }
    m_uncompressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);

    /* create object */
    ObjectHeaderBase * obj = createObject(ohb.objectType);
    if (obj == nullptr) {
        /* in case of unknown objectType */
        return;
    }

    /* read object */
    obj->read(m_uncompressedFile);
    if (m_uncompressedFile.eof()) {
        delete obj;
        return;
    }

    /* push data into readWriteQueue */
    m_readWriteQueue.write(obj);

    /* statistics */
    if (obj->objectType != ObjectType::Unknown115) {
        currentObjectCount++;
    }

    /* drop old data */
    m_uncompressedFile.dropOldData();
}

void File::readWriteQueue2UncompressedFile()
{
    /* get from readWriteQueue */
    ObjectHeaderBase * ohb = m_readWriteQueue.read();

    /* process data */
    if (ohb == nullptr) {
        return;
    }

    /* write into uncompressedFile */
    ohb->write(m_uncompressedFile);

    /* statistics */
    if (ohb->objectType != ObjectType::Unknown115) {
        currentObjectCount++;
    }

    /* delete object */
    delete ohb;
}

void File::compressedFile2UncompressedFile()
{
    /* read header to identify type */
    ObjectHeaderBase ohb;
    ohb.read(m_compressedFile);
    if (m_compressedFile.eof()) {
        return;
    }
    m_compressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);
    if (ohb.objectType != ObjectType::LOG_CONTAINER) {
        throw Exception("File::compressedFile2UncompressedFile(): Object read for inflation is not a log container.");
    }

    /* read LogContaier */
    LogContainer * logContainer = new LogContainer;
    logContainer->read(m_compressedFile);
    if (m_compressedFile.eof()) {
        return;
    }

    /* statistics */
    currentUncompressedFileSize +=
        logContainer->internalHeaderSize() +
        logContainer->uncompressedFileSize;

    /* uncompress */
    logContainer->uncompress();

    /* copy into uncompressedFile */
    m_uncompressedFile.write(logContainer);
}

void File::uncompressedFile2CompressedFile()
{
    /* setup new log container */
    LogContainer logContainer;

    /* copy data into LogContainer */
    logContainer.uncompressedFile.resize(m_uncompressedFile.defaultLogContainerSize());
    m_uncompressedFile.read(
        reinterpret_cast<char *>(logContainer.uncompressedFile.data()),
        m_uncompressedFile.defaultLogContainerSize());
    logContainer.uncompressedFileSize = static_cast<DWORD>(m_uncompressedFile.gcount());
    logContainer.uncompressedFile.resize(logContainer.uncompressedFileSize);

    /* compress */
    if (compressionLevel == 0) {
        /* no compression */
        logContainer.compress(0, 0);
    } else {
        /* zlib compression */
        logContainer.compress(2, compressionLevel);
    }

    /* write log container */
    logContainer.write(m_compressedFile);

    /* statistics */
    currentUncompressedFileSize +=
        logContainer.internalHeaderSize() +
        logContainer.uncompressedFileSize;

    /* drop old data */
    m_uncompressedFile.dropOldData();
}

void File::uncompressedFileReadThread(File * file)
{
    while(file->m_uncompressedFileThreadRunning) {
        /* process */
        file->uncompressedFile2ReadWriteQueue();

        /* check for eof */
        if (file->m_uncompressedFile.eof()) {
            file->m_readWriteQueue.setTotalObjectCount(file->m_readWriteQueue.tellp()); // eof
            file->m_uncompressedFileThreadRunning = false;
        }
    }
}

void File::uncompressedFileWriteThread(File * file)
{
    while(file->m_uncompressedFileThreadRunning) {
        /* process */
        file->readWriteQueue2UncompressedFile();

        /* check for eof */
        if (file->m_readWriteQueue.eof()) {
            file->m_uncompressedFile.setFileSize(file->m_uncompressedFile.tellp()); // eof
            file->m_uncompressedFileThreadRunning = false;
        }
    }
}

void File::compressedFileReadThread(File * file)
{
    while(file->m_compressedFileThreadRunning) {
        /* process */
        file->compressedFile2UncompressedFile();

        /* check for eof */
        if (file->m_compressedFile.eof()) {
            file->m_uncompressedFile.setFileSize(file->m_uncompressedFile.tellp()); // eof
            file->m_compressedFileThreadRunning = false;
        }
    }
}

void File::compressedFileWriteThread(File * file)
{
    while(file->m_compressedFileThreadRunning) {
        /* process */
        file->uncompressedFile2CompressedFile();

        /* check for eof */
        if (file->m_uncompressedFile.eof()) {
            // file->m_compressedFile.setFileSize(file->m_compressedFile.tellp()); // eof
            file->m_compressedFileThreadRunning = false;
        }
    }
}

}
}
