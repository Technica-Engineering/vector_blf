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

#include <cassert>
#include <cstring>
#include <iostream>

#include <zlib.h>

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

File::File() :
    fileStatistics(),
    currentUncompressedFileSize(0),
    currentObjectCount(0),
    compressionLevel(6),
    defaultLogContainerSize(0x20000),
    writeUnknown115(true),
    m_openMode(),
    m_readWriteQueue(),
    m_readWriteQueueMutex(),
    m_uncompressedFile(),
    m_uncompressedFileMutex(),
    m_uncompressedFileThread(),
    m_uncompressedFileThreadWakeup(),
    m_uncompressedFileThreadRunning(),
    m_compressedFile(),
    m_compressedFileThread(),
    m_compressedFileThreadWakeup(),
    m_compressedFileThreadRunning()
{
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
        throw Exception("File::open(): already open");
    }

    m_openMode = mode;

    /* open queue */
    m_readWriteQueue.open();
    m_uncompressedFile.open();

    /* read */
    if (mode & std::ios_base::in) {
        // std::cout << "File::open(): for reading" << std::endl;
        /* open file for reading */
        m_compressedFile.open(filename, std::ios_base::in | std::ios_base::binary);
        if (!m_compressedFile.is_open()) {
            return;
        }

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
        // std::cout << "File::open(): for writing" << std::endl;
        /* open file for writing */
        m_compressedFile.open(filename, std::ios_base::out | std::ios_base::binary);
        if (!m_compressedFile.is_open()) {
            return;
        }

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
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_readWriteQueueMutex);

    return
        m_compressedFile.eof() &&
        m_uncompressedFile.eof() &&
        m_readWriteQueue.eof();
}

ObjectHeaderBase * File::read()
{
    ObjectHeaderBase * ohb = nullptr;
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_readWriteQueueMutex);

        /* read from readWriteQueue (blocks when waiting for new data) */
        // std::cout << "File::read(): wait" << std::endl;
        ohb = m_readWriteQueue.read();
    }

    /* notify thread */
    m_uncompressedFileThreadWakeup.notify_all();

    return ohb;
}

void File::write(ObjectHeaderBase * ohb)
{
    {
        /* mutex lock */
        std::unique_lock<std::mutex> lock(m_readWriteQueueMutex);

        /* wait until readWrite has space free */
        m_uncompressedFileThreadWakeup.wait(lock, [this]{
            return m_readWriteQueue.size() < 10;
        });

        /* push to queue */
        m_readWriteQueue.write(ohb);
    }

    /* notify thread */
    m_uncompressedFileThreadWakeup.notify_all();
}

void File::close()
{
    /* check if file is open */
    if (!is_open()) {
        return;
    }

    /* read */
    if (m_openMode & std::ios_base::in) {
        // std::cout << "File::close(): for reading" << std::endl;

        /* finalize compressedFile thread */
        if (m_compressedFileThread.joinable()) {
            /* abort operation */
            m_compressedFileThreadRunning = false;
            m_compressedFileThreadWakeup.notify_all();

            /* wait for thread to finish */
            m_compressedFileThread.join();
        }

        /* finalize uncompressedFile thread */
        if (m_uncompressedFileThread.joinable()) {
            /* abort operation */
            m_uncompressedFileThreadRunning = false;
            m_uncompressedFileThreadWakeup.notify_all();

            /* wait for thread to finish */
            m_uncompressedFileThread.join();
        }
        // std::cout << "File::close(): done for reading" << std::endl;
    } else

    /* write */
    if (m_openMode & std::ios_base::out) {
        // std::cout << "File::close(): for writing" << std::endl;
        /* finalize uncompressedFile thread */
        m_readWriteQueue.setTotalObjectCount(m_readWriteQueue.tellp()); // eof
        // std::cout << "File::close(): readWriteQueue closed" << std::endl;

        /* finalize uncompression thread */
        if (m_uncompressedFileThread.joinable()) {
            m_uncompressedFileThread.join();
        }
        // std::cout << "File::close(): uncompressedFileThread finished" << std::endl;

        /* finalize compression thread */
        if (m_compressedFileThread.joinable()) {
            m_compressedFileThread.join();
        }
        // std::cout << "File::close(): compressedFileThread finished" << std::endl;

        /* write final LogContainer+Unknown115 */
        if (writeUnknown115) {
            // std::cout << "File::close(): write Unknown115" << std::endl;
            fileStatistics.fileSizeWithoutUnknown115 = currentFileSize();

            /* write end of file message */
            Unknown115 * unknown115 = new Unknown115;
            m_readWriteQueue.write(unknown115);
            m_readWriteQueue.setTotalObjectCount(m_readWriteQueue.tellp()); // eof
            // std::cout << "File::close(): readWriteQueue closed" << std::endl;

            /* run uncompressedFileThread once */
            m_uncompressedFileThreadRunning = true;
            m_uncompressedFileThread = std::thread(uncompressedFileWriteThread, this);
            if (m_uncompressedFileThread.joinable()) {
                m_uncompressedFileThread.join();
            }
            // std::cout << "File::close(): uncompressedFileThread finished" << std::endl;

            /* run compressedFilethread once */
            m_compressedFileThreadRunning = true;
            m_compressedFileThread = std::thread(compressedFileWriteThread, this);
            if (m_compressedFileThread.joinable()) {
                m_compressedFileThread.join();
            }
            // std::cout << "File::close(): compressedFileThread finished" << std::endl;
        }

        /* set file statistics */
        fileStatistics.fileSize = currentFileSize();
        fileStatistics.uncompressedFileSize = currentUncompressedFileSize;
        fileStatistics.objectCount = currentObjectCount;
        // @todo fileStatistics.objectsRead = 0;

        /* write file statistics */
        m_compressedFile.seekp(0, std::ios_base::beg);
        fileStatistics.write(m_compressedFile);
        // std::cout << "File::close(): done for writing" << std::endl;
    }

    /* close files */
    m_readWriteQueue.close();
    m_uncompressedFile.close();
    m_compressedFile.close();

    // std::cout << "File::close(): reset files" << std::endl;
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
    // std::cout << "File::uncompressedFile2readWriteQueue(): read head" << std::endl;
    ohb.read(m_uncompressedFile);
    if (m_uncompressedFile.eof()) {
        return;
    }
    m_uncompressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);

    /* read object */
    ObjectHeaderBase * obj = createObject(ohb.objectType);
    // std::cout << "File::uncompressedFile2readWriteQueue(): read full" << std::endl;
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
    m_uncompressedFile.dropOldData(static_cast<std::streamsize>(defaultLogContainerSize));
}

void File::readWriteQueue2UncompressedFile()
{
    /* get from readWriteQueue */
    ObjectHeaderBase * ohb = m_readWriteQueue.read();

    /* process data */
    if (ohb == nullptr) {
        return;
    }

    // std::cout << "File::readWriteQueue2UncompressedFile(): write object into uncompressedFile" << std::endl;

    /* write into uncompressedFile */
    ohb->write(m_uncompressedFile);

    /* statistics */
    if (ohb->objectType != ObjectType::Unknown115) {
        currentObjectCount++;
    }
}

void File::compressedFile2UncompressedFile()
{
    /* read header to identify type */
    ObjectHeaderBase ohb;
    ohb.read(m_compressedFile);
    if (m_compressedFile.eof()) {
        // std::cout << "File::compressedFile2UncompressedFile(): set eof when reading header" << std::endl;
        return;
    }
    m_compressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);
    if (ohb.objectType != ObjectType::LOG_CONTAINER) {
        throw Exception("File::compressedFile2UncompressedFile(): Object read for inflation is not a log container.");
    }

    /* read LogContaier */
    LogContainer logContainer;
    logContainer.read(m_compressedFile);
    if (m_compressedFile.eof()) {
        // std::cout << "File::compressedFile2UncompressedFile(): set eof when reading LogContainer" << std::endl;
        return;
    }

    /* statistics */
    currentUncompressedFileSize +=
        logContainer.internalHeaderSize() +
        logContainer.uncompressedFileSize;

    // std::cout << "File::compressedFile2UncompressedFile(): uncompress" << std::endl;

    /* uncompress */
    switch(logContainer.compressionMethod) {
    case 0: /* no compression */
    {
        m_uncompressedFile.write(
            reinterpret_cast<const char *>(logContainer.compressedFile.data()),
            static_cast<std::streamsize>(logContainer.compressedFileSize));
    }
        break;

    case 2: /* zlib compress */
    {
        /* create buffer */
        uLong bufferSize = static_cast<uLong>(logContainer.uncompressedFileSize);
        std::vector<char> buffer;
        buffer.resize(bufferSize);

        /* inflate */
        int retVal = uncompress(
             reinterpret_cast<Byte *>(buffer.data()),
             &bufferSize,
             reinterpret_cast<Byte *>(logContainer.compressedFile.data()),
             static_cast<uLong>(logContainer.compressedFileSize));
        if (retVal != Z_OK) {
            throw Exception("File::compressedFile2UncompressedFile(): uncompress error");
        }

        /* copy into uncompressedFile */
        m_uncompressedFile.write(buffer.data(), static_cast<std::streamsize>(bufferSize));
    }
        break;

    default:
        throw Exception("File::compressedFile2UncompressedFile(): unknown compression");
    }
}

void File::uncompressedFile2CompressedFile()
{
    /* setup new log container */
    LogContainer logContainer;

    /* compress */
    if (compressionLevel == Z_NO_COMPRESSION) {
        /* no compression */
        logContainer.compressionMethod = 0;

        /* copy data into LogContainer */
        // std::cout << "File::uncompressedFile2CompressedFile(): read from uncompressedFile" << std::endl;
        logContainer.compressedFile.resize(defaultLogContainerSize);
        m_uncompressedFile.read(
            reinterpret_cast<char *>(logContainer.compressedFile.data()),
            defaultLogContainerSize);
        logContainer.compressedFile.resize(static_cast<size_t>(m_uncompressedFile.gcount()));

        /* set sizes */
        logContainer.compressedFileSize = static_cast<DWORD>(logContainer.compressedFile.size());
        logContainer.uncompressedFileSize = static_cast<DWORD>(logContainer.compressedFile.size());
    } else {
        /* zlib compression */
        logContainer.compressionMethod = 2;

        /* create buffer */
        std::vector<char> bufferIn;
        bufferIn.resize(defaultLogContainerSize);

        /* copy data into buffer */
        // std::cout << "File::uncompressedFile2CompressedFile(): read from uncompressedFile" << std::endl;
        m_uncompressedFile.read(bufferIn.data(), defaultLogContainerSize);
        bufferIn.resize(static_cast<size_t>(m_uncompressedFile.gcount()));

        /* deflate/compress data */
        uLong bufferSizeOut = compressBound(logContainer.uncompressedFileSize);
        logContainer.compressedFile.resize(bufferSizeOut); // extend
        int retVal = compress2(
            reinterpret_cast<Byte *>(logContainer.compressedFile.data()),
            &bufferSizeOut,
            reinterpret_cast<Byte *>(bufferIn.data()),
            logContainer.uncompressedFileSize,
            compressionLevel);
        if (retVal != Z_OK) {
            throw Exception("File::uncompressedFile2CompressedFile(): compress2 error");
        }
        logContainer.compressedFile.resize(bufferSizeOut); // shrink

        /* set sizes */
        logContainer.compressedFileSize = static_cast<DWORD>(sizeof(logContainer.compressedFile.size()));
        logContainer.uncompressedFileSize = static_cast<DWORD>(sizeof(bufferIn.size()));
    }

    /* write log container */
    logContainer.write(m_compressedFile);

    /* statistics */
    currentUncompressedFileSize +=
        logContainer.internalHeaderSize() +
        logContainer.uncompressedFileSize;

    /* drop old data */
    // @todo m_uncompressedFile.dropOldData(static_cast<std::streamsize>(logContainer.uncompressedFileSize));
}

void File::uncompressedFileReadThread(File * file)
{
    // std::cout << "File::uncompressedFileReadThread(): started" << std::endl;
    while(file->m_uncompressedFileThreadRunning) {
        // @todo wait until readWriteQueue has free space
#if 0
        /* wait until readWriteQueue has space free */
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_uncompressedFileThreadWakeup.wait(lock, [file]{
            return
                !file->m_uncompressedFileThreadRunning ||
                (file->m_readWriteQueue.size() < 10);
        });
#endif

        /* process */
        // std::cout << "File::uncompressedFileReadThread(): loop" << std::endl;
        file->uncompressedFile2ReadWriteQueue();
        file->m_compressedFileThreadWakeup.notify_all();

        /* check for eof */
        if (file->m_uncompressedFile.eof()) {
            file->m_readWriteQueue.setTotalObjectCount(file->m_readWriteQueue.tellp()); // eof
            file->m_uncompressedFileThreadRunning = false;
        }
    }
    // std::cout << "File::uncompressedFileReadThread(): stopped" << std::endl;
}

void File::uncompressedFileWriteThread(File * file)
{
    // std::cout << "File::uncompressedFileWriteThread(): started" << std::endl;
    while(file->m_uncompressedFileThreadRunning) {
        // @todo wait until uncompressedFile has free space
#if 0
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_uncompressedFileThreadWakeup.wait(lock, [file]{
            return
                !file->m_uncompressedFileThreadRunning ||
                file->m_uncompressedFile.size() < 0x20000;
        });
#endif

        /* process */
        // std::cout << "File::uncompressedFileWriteThread(): loop" << std::endl;
        file->readWriteQueue2UncompressedFile();

        /* check for eof */
        if (file->m_readWriteQueue.eof()) {
            file->m_uncompressedFile.setFileSize(file->m_uncompressedFile.tellp()); // eof
            file->m_uncompressedFileThreadRunning = false;
        }
    }
    // std::cout << "File::uncompressedFileWriteThread(): stopped" << std::endl;
}

void File::compressedFileReadThread(File * file)
{
    // std::cout << "File::compressedFileReadThread(): started" << std::endl;
    while(file->m_compressedFileThreadRunning) {
        // @todo wait until uncompressedFile has free space
#if 0
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_compressedFileThreadWakeup.wait(lock, [file]{
            return
                !file->m_compressedFileThreadRunning ||
                (file->m_uncompressedFile.size() < 0x20000);
        });
#endif

        /* process */
        // std::cout << "File::compressedFileReadThread(): loop" << std::endl;
        file->compressedFile2UncompressedFile();

        /* check for eof */
        if (file->m_compressedFile.eof()) {
            file->m_uncompressedFile.setFileSize(file->m_uncompressedFile.tellp()); // eof
            file->m_compressedFileThreadRunning = false;
        }
    }
    // std::cout << "File::compressedFileReadThread(): stopped" << std::endl;
}

void File::compressedFileWriteThread(File * file)
{
    // std::cout << "File::compressedFileWriteThread(): started" << std::endl;
    while(file->m_compressedFileThreadRunning) {
        /* wait until compressedFile has enough data */
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_compressedFileThreadWakeup.wait(lock, [file]{
            return
                !file->m_compressedFileThreadRunning ||
                (file->m_uncompressedFile.size() >= file->defaultLogContainerSize);
        });

        /* process */
        // std::cout << "File::compressedFileWriteThread(): process" << std::endl;
        file->uncompressedFile2CompressedFile();
        file->m_uncompressedFileThreadWakeup.notify_all();
        // std::cout << "File::compressedFileWriteThread(): process finished" << std::endl;

        /* check for eof */
        if (file->m_uncompressedFile.eof()) {
            // std::cout << "File::compressedFileWriteThread(): eof detected" << std::endl;
            file->m_compressedFileThreadRunning = false;
        }
    }
    // std::cout << "File::compressedFileWriteThread(): stopped" << std::endl;
}

}
}
