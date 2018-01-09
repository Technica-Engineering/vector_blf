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
    openMode(),
    fileStatistics(),
    currentUncompressedFileSize(0),
    currentObjectCount(0),
    compressionLevel(6),
    defaultLogContainerSize(0x20000),
    writeUnknown115(true),
    m_readWriteQueue(),
    m_readWriteQueueMutex(),
    m_readWriteQueueChanged(),
    m_uncompressedFile(),
    m_uncompressedFileMutex(),
    m_uncompressedFileChanged(),
    m_compressedFile(),
    m_uncompressedFileThread(),
    m_uncompressedFileThreadRunning(),
    m_compressedFileThread(),
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
    openMode = mode;

    if (mode & std::ios_base::in) {
        /* open file for reading */
        m_compressedFile.open(filename, std::ios_base::in | std::ios_base::binary);
        if (!is_open()) {
            return;
        }

        /* read file statistics */
        fileStatistics.read(m_compressedFile);

        /* fileStatistics done */
        currentUncompressedFileSize += fileStatistics.statisticsSize;

        /* create read threads */
        m_uncompressedFileThread = std::thread(thread1ReadMethod, this);
        m_compressedFileThread = std::thread(thread2ReadMethod, this);
    }

    if (mode & std::ios_base::out) {
        /* open file for writing */
        m_compressedFile.open(filename, std::ios_base::out | std::ios_base::binary);
        if (!is_open()) {
            return;
        }

        /* write file statistics */
        fileStatistics.write(m_compressedFile);

        /* fileStatistics done */
        currentUncompressedFileSize += fileStatistics.statisticsSize;

        /* create write threads */
        m_uncompressedFileThread = std::thread(thread1WriteMethod, this);
        m_compressedFileThread = std::thread(thread2WriteMethod, this);
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

    return m_readWriteQueue.eof();
}

ObjectHeaderBase * File::read()
{
    ObjectHeaderBase * ohb = nullptr;
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_readWriteQueueMutex);

        /* read from readWriteQueue (blocks when waiting for new data) */
        std::cout << "File::read(): wait" << std::endl;
        ohb = m_readWriteQueue.front();
        m_readWriteQueue.pop();
        if (m_readWriteQueue.eof()) {
            std::cout << "File::read(): eof" << std::endl;
        }
    }

    /* notify thread */
    m_readWriteQueueChanged.notify_all();

    return ohb;
}

void File::write(ObjectHeaderBase * ohb)
{
    {
        /* mutex lock */
        std::unique_lock<std::mutex> lock(m_readWriteQueueMutex);

        /* wait until readWrite has space free */
        m_readWriteQueueChanged.wait(lock, [this]{
            return (m_readWriteQueue.size() < 100);
        });

        /* push to queue */
        m_readWriteQueue.push(ohb);
    }

    /* notify thread */
    m_readWriteQueueChanged.notify_all();
}

void File::close()
{
    /* check if file is open */
    if (!is_open()) {
        return;
    }

    if (openMode & std::ios_base::in) {
        /* finalize compression thread */
        m_compressedFileThreadRunning = false;
        m_uncompressedFileChanged.notify_all();
        m_compressedFileThread.join();

        /* finalize read/write thread */
        m_uncompressedFileThreadRunning = false;
        m_readWriteQueueChanged.notify_all();
        m_uncompressedFileThread.join();

        /* close files */
        m_compressedFile.close();
        m_uncompressedFile.close();
        m_readWriteQueue.close();
    }

    if (openMode & std::ios_base::out) {
        // @todo check this
        /* if data left, compress and write it */
        if (m_uncompressedFile.tellp() > m_uncompressedFile.tellg()) {
            /* finalize read/write thread */
            m_uncompressedFileThreadRunning = false;
            m_uncompressedFileThread.join();

            /* finalize compression thread */
            m_compressedFileThreadRunning = false;
            m_compressedFileThread.join();
        }

        /* write final LogContainer+Unknown115 */
        if (writeUnknown115) {
            fileStatistics.fileSizeWithoutUnknown115 = currentFileSize();

            /* write end of file message */
            Unknown115 eofMessage;
            eofMessage.write(m_uncompressedFile);

            /* trigger thread */
            uncompressedFile2CompressedFile();
        }

        /* set file statistics */
        fileStatistics.fileSize = currentFileSize();
        fileStatistics.uncompressedFileSize = currentUncompressedFileSize;
        fileStatistics.objectCount = currentObjectCount;
        //fileStatistics.objectsRead = 0;

        /* write file statistics */
        m_compressedFile.seekp(0);
        fileStatistics.write(m_compressedFile);
    }
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
    /* check end-of-file */
    if (m_uncompressedFile.eof()) {
        throw Exception("File::uncompressedFile2readWriteQueue(): eof");
    }

    /* identify type */
    ObjectHeaderBase ohb;
    std::cout << "File::uncompressedFile2readWriteQueue(): read head" << std::endl;
    ohb.read(m_uncompressedFile);
    if (m_uncompressedFile.eof()) {
        /* push end-of-file */
        std::cout << "File::uncompressedFile2readWriteQueue(): push eof" << std::endl;
        m_readWriteQueue.push(nullptr); // eof marker
        m_readWriteQueueChanged.notify_all();
        return;
    }
    m_uncompressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);

    /* read object */
    ObjectHeaderBase * obj = createObject(ohb.objectType);
    std::cout << "File::uncompressedFile2readWriteQueue(): read full" << std::endl;
    obj->read(m_uncompressedFile);
    if (m_uncompressedFile.eof()) {
        delete obj;

        /* push end-of-file */
        std::cout << "File::uncompressedFile2readWriteQueue(): push eof" << std::endl;
        m_readWriteQueue.push(nullptr); // eof marker
        m_readWriteQueueChanged.notify_all();
        return;
    }

    /* push data into readWriteQueue */
    m_readWriteQueue.push(obj);
    m_readWriteQueueChanged.notify_all();

    /* statistics */
    currentObjectCount++;

    /* drop old data */
    m_uncompressedFile.dropOldData(static_cast<std::streamsize>(defaultLogContainerSize));
}

void File::readWriteQueue2UncompressedFile()
{
    /* get from readWriteQueue */
    ObjectHeaderBase * ohb = m_readWriteQueue.front();
    m_readWriteQueue.pop();

    /* process data */
    if (ohb == nullptr) {
        m_uncompressedFile.setFileSize(m_uncompressedFile.tellp()); // set eof
    } else {
        /* write into uncompressedFile */
        ohb->write(m_uncompressedFile);
        delete ohb;

        /* statistics */
        currentObjectCount++;
    }
}

void File::compressedFile2UncompressedFile()
{
    /* check for end-of-file */
    if (m_compressedFile.eof()) {
        throw Exception("File::compressedFile2UncompressedFile(): eof");
    }

    /* identify type */
    ObjectHeaderBase ohb;
    ohb.read(m_compressedFile);
    if (m_compressedFile.eof()) {
        std::cout << "File::compressedFile2UncompressedFile(): eof when reading header" << std::endl;
        m_uncompressedFile.setFileSize(m_uncompressedFile.tellp()); // set eof
        m_uncompressedFileChanged.notify_all();
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
        std::cout << "File::compressedFile2UncompressedFile(): eof when reading LogContainer" << std::endl;
        m_uncompressedFile.setFileSize(m_uncompressedFile.tellp()); // set eof
        m_uncompressedFileChanged.notify_all();
        return;
    }

    /* statistics */
    currentUncompressedFileSize +=
        logContainer.internalHeaderSize() +
        logContainer.uncompressedFileSize;

    std::cout << "File::compressedFile2UncompressedFile(): uncompress" << std::endl;

    /* no compression */
    switch(logContainer.compressionMethod) {
    case 0: /* no compression */
    {
        m_uncompressedFile.write(
            reinterpret_cast<const char *>(logContainer.compressedFile.data()),
            static_cast<std::streamsize>(logContainer.compressedFileSize));
        m_uncompressedFileChanged.notify_all();
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
        m_uncompressedFileChanged.notify_all();
    }
        break;

    default:
        throw Exception("File::compressedFile2UncompressedFile(): unknown compression");
    }
}

void File::uncompressedFile2CompressedFile()
{
    /* check how much data is available for compression */
    DWORD uncompressedFileSize = static_cast<DWORD>(m_uncompressedFile.tellp() - m_uncompressedFile.tellg());
    if (uncompressedFileSize == 0) {
        return;
    }

    /* calculate size of data to compress */
    if (uncompressedFileSize > defaultLogContainerSize) {
        uncompressedFileSize = static_cast<DWORD>(defaultLogContainerSize);
    }

    /* setup new log container */
    LogContainer logContainer;
    logContainer.uncompressedFileSize = static_cast<DWORD>(uncompressedFileSize);
    if (compressionLevel == Z_NO_COMPRESSION) {
        logContainer.compressionMethod = 0;
        logContainer.compressedFileSize = logContainer.uncompressedFileSize;
        logContainer.compressedFile.resize(logContainer.compressedFileSize);

        /* copy data into LogContainer */
        m_uncompressedFile.read(
                    reinterpret_cast<char *>(logContainer.compressedFile.data()),
                    static_cast<std::streamsize>(uncompressedFileSize));
        if (m_uncompressedFile.gcount() < static_cast<std::streamsize>(uncompressedFileSize)) {
            throw Exception("File::uncompressedFile2CompressedFile(): Unable to (completely) read block for compression");
        }
    } else {
        logContainer.compressionMethod = 2;

        /* create buffer */
        std::vector<char> bufferIn;
        bufferIn.resize(uncompressedFileSize);

        /* copy data into buffer */
        m_uncompressedFile.read(bufferIn.data(), static_cast<std::streamsize>(uncompressedFileSize));
        if (m_uncompressedFile.gcount() < static_cast<std::streamsize>(uncompressedFileSize)) {
            throw Exception("File::uncompressedFile2CompressedFile(): Unable to (completely) read block for compression");
        }

        /* deflate/compress data */
        uLong bufferSizeOut = compressBound(uncompressedFileSize);
        logContainer.compressedFile.resize(bufferSizeOut); // extend
        int retVal = compress2(
            reinterpret_cast<Byte *>(logContainer.compressedFile.data()),
            &bufferSizeOut,
            reinterpret_cast<Byte *>(bufferIn.data()),
            uncompressedFileSize,
            compressionLevel);
        if (retVal != Z_OK) {
            throw Exception("File::uncompressedFile2CompressedFile(): compress2 error");
        }
        if (bufferSizeOut > logContainer.compressedFile.size()) {
            throw Exception("File::uncompressedFile2CompressedFile(): Compressed data exceeds buffer size");
        }
        logContainer.compressedFile.resize(bufferSizeOut); // shrink
    }

    /* write log container */
    logContainer.write(m_compressedFile);

    /* statistics */
    currentUncompressedFileSize +=
        logContainer.internalHeaderSize() +
        logContainer.uncompressedFileSize;

    /* drop old data */
    m_uncompressedFile.dropOldData(static_cast<std::streamsize>(uncompressedFileSize));
}

void File::thread1ReadMethod(File * file)
{
    file->m_uncompressedFileThreadRunning = true;

    std::cout << "File::thread1ReadMethod(): started" << std::endl;
    while(file->m_uncompressedFileThreadRunning) {
        /* wait until readWriteQueue has space free */
        std::cout << "File::thread1ReadMethod(): wait for readWriteQueue to empty" << std::endl;
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_readWriteQueueChanged.wait(lock, [file]{
            return (file->m_readWriteQueue.size() < 10) || file->m_uncompressedFile.eof();
        });

        /* check for eof */
        if (file->m_uncompressedFile.eof()) {
            file->m_uncompressedFileThreadRunning = false;
            file->m_readWriteQueue.push(nullptr); // eof
            file->m_readWriteQueueChanged.notify_all();
            break;
        }

        /* process */
        std::cout << "File::thread1ReadMethod(): loop" << std::endl;
        file->uncompressedFile2ReadWriteQueue();
    }
    std::cout << "File::thread1ReadMethod(): stopped" << std::endl;
}

void File::thread1WriteMethod(File * file)
{
    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    file->m_uncompressedFileThreadRunning = true;

    std::cout << "File::thread1WriteMethod(): started" << std::endl;
    while(file->m_uncompressedFileThreadRunning) {
        {
            /* wait until readWriteQueue is filled */
            while (file->m_readWriteQueue.empty()) {
                file->m_readWriteQueueChanged.wait(lock);
            }
            std::cout << "File::thread1WriteMethod(): loop" << std::endl;

            /* process */
            file->readWriteQueue2UncompressedFile();
        }

        /* notify */
        file->m_uncompressedFileChanged.notify_all();
    }
    std::cout << "File::thread1WriteMethod(): stopped" << std::endl;
}

void File::thread2ReadMethod(File * file)
{
    file->m_compressedFileThreadRunning = true;

    std::cout << "File::thread2ReadMethod(): started" << std::endl;
    while(file->m_compressedFileThreadRunning) {
        /* wait until uncompressedFile has space free */
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        file->m_uncompressedFileChanged.wait(lock, [file]{
            return (file->m_uncompressedFile.size() < 0x20000) || file->m_compressedFile.eof();
        });

        /* check for eof */
        if (file->m_compressedFile.eof()) {
            file->m_compressedFileThreadRunning = false;
            file->m_uncompressedFile.setFileSize(file->m_uncompressedFile.tellp());
            file->m_uncompressedFileChanged.notify_all();
            break;
        }

        /* process */
        std::cout << "File::thread2ReadMethod(): loop" << std::endl;
        file->compressedFile2UncompressedFile();
    }
    std::cout << "File::thread2ReadMethod(): stopped" << std::endl;
}

void File::thread2WriteMethod(File * file)
{
    file->m_compressedFileThreadRunning = true;

    std::cout << "File::thread2WriteMethod(): started" << std::endl;
    while(file->m_compressedFileThreadRunning) {
        /* wait until uncompressedFile has sufficient size for a new logContainer */
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        while(file->m_uncompressedFile.size() < file->defaultLogContainerSize) {
            file->m_uncompressedFileChanged.wait(lock);
        }
        std::cout << "File::thread2WriteMethod(): loop" << std::endl;

        /* process */
        file->uncompressedFile2CompressedFile();
        file->m_uncompressedFileChanged.notify_all();
    }
    std::cout << "File::thread2WriteMethod(): stopped" << std::endl;
}

}
}
