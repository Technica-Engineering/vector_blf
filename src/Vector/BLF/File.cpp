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

#include "File.h"

#include <cstring>
#include <zlib.h>

namespace Vector {
namespace BLF {

File::File() :
    openMode(OpenMode::Read),
    fileStatistics(),
    currentUncompressedFileSize(0),
    currentObjectCount(0),
    compressionLevel(6),
    defaultLogContainerSize(0x20000),
    compressedFile(),
    uncompressedFile()
{
}

ObjectHeaderBase * File::createObject(ObjectType type)
{
    ObjectHeaderBase * obj = nullptr;

    switch(type) {
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

    case ObjectType::reserved_1:
    case ObjectType::reserved_2:
    case ObjectType::reserved_3:
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

    case ObjectType::AVAILABLE2:
    case ObjectType::AVAILABLE3:
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

    default:
        break;
    }

    return obj;
}

void File::open(const char * filename, OpenMode openMode)
{
    this->openMode = openMode;

    switch(this->openMode) {
    case OpenMode::Read:
        /* open file for reading */
        compressedFile.open(filename, std::ios_base::in | std::ios_base::binary);
        if (!is_open())
            return;

        /* read file statistics */
        fileStatistics.read(compressedFile);
        break;

    case OpenMode::Write:
        /* open file for writing */
        compressedFile.open(filename, std::ios_base::out | std::ios_base::binary);
        if (!is_open())
            return;

        /* write file statistics */
        fileStatistics.write(compressedFile);
        break;
    }

    /* fileStatistics done */
    currentUncompressedFileSize += fileStatistics.statisticsSize;
}

void File::open(const std::string & filename, OpenMode openMode)
{
    open(filename.c_str(), openMode);
}

bool File::is_open() const
{
    return compressedFile.is_open();
}

bool File::eof()
{
    bool compressedFileEmpty = (compressedFile.tellg() >= (signed) fileStatistics.fileSize) || compressedFile.eof();
    bool uncompressedFileEmpty = (uncompressedFile.tellp() <= uncompressedFile.tellg());
    return compressedFileEmpty && uncompressedFileEmpty;
}

ObjectHeaderBase * File::readObjectFromCompressedFile()
{
    /* identify type */
    ObjectHeaderBase ohb;
    ohb.read(compressedFile);
    compressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);

    /* create object */
    ObjectHeaderBase * obj = createObject(ohb.objectType);
    if (obj == nullptr) {
        return nullptr;
    }

    /* read object */
    obj->read(compressedFile);

    /* skip padding */
    compressedFile.seekg(ohb.objectSize % 4, std::ios_base::cur);

    return obj;
}

ObjectHeaderBase * File::readObjectFromUncompressedFile()
{
    /* first read some more compressed data and inflate it */
    while ((uncompressedFile.tellp() - uncompressedFile.tellg()) < 0x10) // sizeof(ObjectHeaderBase)
        inflate();

    /* identify type */
    ObjectHeaderBase ohb;
    ohb.read(uncompressedFile);
    uncompressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);

    /* ensure sufficient date is available */
    while ((uncompressedFile.tellp() - uncompressedFile.tellg()) < ohb.objectSize)
        inflate();

    /* create object */
    ObjectHeaderBase * obj = createObject(ohb.objectType);
    if (obj == nullptr) {
        return nullptr;
    }

    /* read object */
    obj->read(uncompressedFile);

    /* skip padding */
    uncompressedFile.seekg(ohb.objectSize % 4, std::ios_base::cur);

    /* drop old data */
    uncompressedFile.dropOldData(defaultLogContainerSize, 0x10); // sizeof(ObjectHeaderBase)

    currentObjectCount++;
    return obj;
}

void File::inflate()
{
    /* read LogContainer */
    ObjectHeaderBase * obj = readObjectFromCompressedFile();
    if (obj == nullptr) {
        return;
    }
    if (obj->objectType != ObjectType::LOG_CONTAINER) {
        return;
    }
    LogContainer * logContainer = reinterpret_cast<LogContainer *>(obj);

    /* statistics */
    currentUncompressedFileSize +=
            logContainer->internalHeaderSize() +
            logContainer->uncompressedFileSize;

    /* create buffer */
    size_t bufferSize = logContainer->uncompressedFileSize;
    char * buffer = new char[bufferSize];
    if (buffer == nullptr) {
        delete logContainer;
        return;
    }

    /* inflate */
    uncompress(reinterpret_cast<Bytef *>(buffer),
               reinterpret_cast<uLongf *>(&bufferSize),
               reinterpret_cast<Bytef *>(logContainer->compressedFile.data()),
               logContainer->compressedFileSize);

    /* copy into uncompressedFile */
    uncompressedFile.write(buffer, bufferSize);

    /* delete buffer */
    delete logContainer;
    delete[] buffer;
}

ObjectHeaderBase * File::read()
{
    return readObjectFromUncompressedFile();
}

void File::deflate()
{
    /* calculate size of data to compress */
    size_t bufferSizeIn = uncompressedFile.tellp() - uncompressedFile.tellg();
    if (bufferSizeIn > defaultLogContainerSize)
        bufferSizeIn = defaultLogContainerSize;

    /* create buffer */
    char * bufferIn = new char[bufferSizeIn];
    if (bufferIn == nullptr) {
        return;
    }

    /* copy data into buffer */
    uncompressedFile.read(bufferIn, bufferSizeIn);

    /* deflate/compress it */
    size_t bufferSizeOut = compressBound(bufferSizeIn);
    char * bufferOut = new char[bufferSizeOut];
    if (bufferOut == nullptr) {
        delete[] bufferIn;
        return;
    }
    compress(reinterpret_cast<Bytef *>(bufferOut),
             reinterpret_cast<uLongf *>(&bufferSizeOut),
             reinterpret_cast<Bytef *>(bufferIn),
             bufferSizeIn);
    delete[] bufferIn;

    /* drop old data */
    uncompressedFile.dropOldData(bufferSizeIn, 0);

    /* setup new log container */
    LogContainer logContainer;
    logContainer.uncompressedFileSize = bufferSizeIn;
    logContainer.compressedFile.resize(bufferSizeOut);
    memcpy(logContainer.compressedFile.data(), bufferOut, bufferSizeOut);
    logContainer.compressedFileSize = bufferSizeOut;
    logContainer.objectSize = logContainer.calculateObjectSize();
    delete[] bufferOut;

    /* statistics */
    currentUncompressedFileSize +=
            logContainer.internalHeaderSize() +
            logContainer.uncompressedFileSize;

    /* write log container */
    logContainer.write(compressedFile);

    /* skip padding */
    char buffer[] = {0,0,0,0};
    compressedFile.write(buffer, logContainer.objectSize % 4);
}

void File::write(ObjectHeaderBase * objectHeaderBase)
{
    /* compressionLevel 0 doesn't use LogContainers */
    if (compressionLevel == 0) {
        /* write into compressedFile */
        objectHeaderBase->write(compressedFile);

        /* skip padding */
        char buffer[] = {0,0,0,0};
        compressedFile.write(buffer, objectHeaderBase->objectSize % 4);
    } else {
        /* write into uncompressedFile */
        objectHeaderBase->write(uncompressedFile);

        /* skip padding */
        char buffer[] = {0,0,0,0};
        uncompressedFile.write(buffer, objectHeaderBase->objectSize % 4);

        /* if data exceeds defined logContainerSize, compress and write it into compressedFile */
        if ((uncompressedFile.tellp() - uncompressedFile.tellg()) >= (signed) defaultLogContainerSize)
            deflate();
    }

    /* statistics */
    currentObjectCount++;
}

void File::close()
{
    if (openMode == OpenMode::Write) {
        /* if data left, compress and write it */
        if (uncompressedFile.tellp() > uncompressedFile.tellg())
            deflate();

        /* write statistics */
        fileStatistics.fileSize = ((ULONGLONG) compressedFile.tellp());
        fileStatistics.uncompressedFileSize = currentUncompressedFileSize;
        fileStatistics.objectCount = currentObjectCount;
        //fileStatistics.objectsRead = 0; // @todo what is objectsRead?
        compressedFile.seekp(0);
        fileStatistics.write(compressedFile);
    }

    compressedFile.close();
}

}
}
