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

/* writes into the current directory the contents of compressedFile in read and in write case */
#undef DEBUG_WRITE_UNCOMPRESSED_FILE

#include <cstring>
#ifdef DEBUG_WRITE_UNCOMPRESSED_FILE
#include <fstream>
#include <sstream>
#endif

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
        m_readWriteQueue.eof() &&
        m_uncompressedFile.eof();
        // @todo compressedFile.eof is not multi-thread safe, so don't use it here: m_compressedFile.eof();
}

ObjectHeaderBase * File::read()
{
    /* read object */
    ObjectHeaderBase * ohb = m_readWriteQueue.read();

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

    }

    /* push to queue */
    m_readWriteQueue.write(ohb);

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
    } else

    /* write */
    if (m_openMode & std::ios_base::out) {
        m_readWriteQueue.setTotalObjectCount(m_readWriteQueue.tellp()); // eof

        /* wait till readWriteQueue is empty */
        m_readWriteQueue.close();

        /* finalize uncompression thread */
        m_uncompressedFileThreadWakeup.notify_all();
        if (m_uncompressedFileThread.joinable()) {
            m_uncompressedFileThread.join();
        }
        if (m_readWriteQueue.size() > 0) {
            throw Exception("File::close(): readWriteQueue not empty");
        }
        if (m_uncompressedFileThreadRunning) {
            throw Exception("File::close(): uncompressedFileThread still running");
        }

        /* finalize compression thread */
        m_compressedFileThreadWakeup.notify_all();
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
        // @todo fileStatistics.objectsRead = 0;

        /* write file statistics */
        m_compressedFile.seekp(0);
        fileStatistics.write(m_compressedFile);
    }

    /* close file */
    m_compressedFile.close();
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

    /* read object */
    ObjectHeaderBase * obj = createObject(ohb.objectType);
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

    /* write into uncompressedFile */
    ohb->write(m_uncompressedFile);
//    std::cout << "File::readWriteQueue2UncompressedFile(): wrote object into uncompressedFile." <<
//                 " type=0x" << std::hex << static_cast<uint16_t>(ohb->objectType) <<
//                 " size=0x" << ohb->objectSize << std::endl;

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
    LogContainer logContainer;
    logContainer.read(m_compressedFile);
    if (m_compressedFile.eof()) {
        return;
    }

    /* statistics */
    currentUncompressedFileSize +=
        logContainer.internalHeaderSize() +
        logContainer.uncompressedFileSize;

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
        uLong uncompressedBufferSize = static_cast<uLong>(logContainer.uncompressedFileSize);
        std::vector<char> uncompressedBuffer;
        uncompressedBuffer.resize(uncompressedBufferSize);

        /* inflate */
        int retVal = uncompress(
             reinterpret_cast<Byte *>(uncompressedBuffer.data()),
             &uncompressedBufferSize,
             reinterpret_cast<Byte *>(logContainer.compressedFile.data()),
             static_cast<uLong>(logContainer.compressedFileSize));
        if (retVal != Z_OK) {
            throw Exception("File::compressedFile2UncompressedFile(): uncompress error");
        }

        /* copy into uncompressedFile */
#ifdef DEBUG_WRITE_UNCOMPRESSED_FILE
        std::ostringstream oss;
        oss << "read_uncompressedFile_0x" << std::hex << m_uncompressedFile.tellp();
        std::ofstream ofs;
        ofs.open(oss.str());
#endif
        m_uncompressedFile.write(uncompressedBuffer.data(), static_cast<std::streamsize>(uncompressedBufferSize));
#ifdef DEBUG_WRITE_UNCOMPRESSED_FILE
        ofs.write(uncompressedBuffer.data(), static_cast<std::streamsize>(uncompressedBufferSize));
        ofs.close();
#endif
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

        /* copy data into buffer */
        std::vector<char> uncompressedBuffer;
        uncompressedBuffer.resize(defaultLogContainerSize); // extend
        m_uncompressedFile.read(uncompressedBuffer.data(), defaultLogContainerSize);
        logContainer.uncompressedFileSize = static_cast<DWORD>(m_uncompressedFile.gcount());
        uncompressedBuffer.resize(logContainer.uncompressedFileSize); // shrink

#ifdef DEBUG_WRITE_UNCOMPRESSED_FILE
        std::ostringstream oss;
        oss << "write_uncompressedFile_0x" << std::hex << m_uncompressedFile.tellp();
        std::ofstream ofs;
        ofs.open(oss.str());
        ofs.write(uncompressedBuffer.data(), static_cast<std::streamsize>(uncompressedBuffer.size()));
        ofs.close();
#endif

        /* deflate/compress data */
        uLong compressedBufferSize = compressBound(logContainer.uncompressedFileSize);
        logContainer.compressedFile.resize(compressedBufferSize); // extend
        int retVal = compress2(
            reinterpret_cast<Byte *>(logContainer.compressedFile.data()),
            &compressedBufferSize,
            reinterpret_cast<Byte *>(uncompressedBuffer.data()),
            logContainer.uncompressedFileSize,
            compressionLevel);
        if (retVal != Z_OK) {
            throw Exception("File::uncompressedFile2CompressedFile(): compress2 error");
        }
        logContainer.compressedFileSize = static_cast<DWORD>(compressedBufferSize);
        logContainer.compressedFile.resize(logContainer.compressedFileSize); // shrink
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
    while(file->m_uncompressedFileThreadRunning) {
        /* wait until readWriteQueue has free space */
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_uncompressedFileThreadWakeup.wait(lock, [file]{
            return
                !file->m_uncompressedFileThreadRunning ||
                file->m_uncompressedFile.atEof() ||
                (file->m_readWriteQueue.size() < 10);
        });

        /* process */
        file->uncompressedFile2ReadWriteQueue();

        /* check for eof */
        if (file->m_uncompressedFile.eof()) {
            file->m_readWriteQueue.setTotalObjectCount(file->m_readWriteQueue.tellp()); // eof
            file->m_uncompressedFileThreadRunning = false;
        }

        /* notify about free space in uncompressedFile */
        file->m_compressedFileThreadWakeup.notify_all();
    }
}

void File::uncompressedFileWriteThread(File * file)
{
    while(file->m_uncompressedFileThreadRunning) {
        /* wait until uncompressedFile has free space */
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_uncompressedFileThreadWakeup.wait(lock, [file]{
            return
                file->m_readWriteQueue.atEof() ||
                file->m_uncompressedFile.size() < 0x20000;
        });

        /* process */
        file->readWriteQueue2UncompressedFile();

        /* check for eof */
        if (file->m_readWriteQueue.eof()) {
            file->m_uncompressedFile.setFileSize(file->m_uncompressedFile.tellp()); // eof
            file->m_uncompressedFileThreadRunning = false;
        }

        /* notify about data in uncompressedFile */
        file->m_compressedFileThreadWakeup.notify_all();
    }
}

void File::compressedFileReadThread(File * file)
{
    while(file->m_compressedFileThreadRunning) {
        /* wait until uncompressedFile has free space */
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_compressedFileThreadWakeup.wait(lock, [file]{
            return
                !file->m_compressedFileThreadRunning ||
                file->m_compressedFile.eof() ||
                (file->m_uncompressedFile.size() < 0x20000);
        });

        /* process */
        file->compressedFile2UncompressedFile();

        /* check for eof */
        if (file->m_compressedFile.eof()) {
            file->m_uncompressedFile.setFileSize(file->m_uncompressedFile.tellp()); // eof
            file->m_compressedFileThreadRunning = false;
        }

        /* notify about data in uncompressedFile */
        file->m_uncompressedFileThreadWakeup.notify_all();
    }
}

void File::compressedFileWriteThread(File * file)
{
    while(file->m_compressedFileThreadRunning) {
        /* wait until compressedFile has enough data */
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_compressedFileThreadWakeup.wait(lock, [file]{
            return
                file->m_uncompressedFile.atEof() ||
                (file->m_uncompressedFile.size() >= file->defaultLogContainerSize);
        });

        /* process */
        file->uncompressedFile2CompressedFile();

        /* check for eof */
        if (file->m_uncompressedFile.eof()) {
            // file->m_compressedFile.setFileSize(file->m_compressedFile.tellp()); // eof
            file->m_compressedFileThreadRunning = false;
        }

        /* notify about free space in uncompressedFile */
        file->m_uncompressedFileThreadWakeup.notify_all();
    }
}

}
}
