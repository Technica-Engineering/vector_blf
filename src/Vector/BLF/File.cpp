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
#include <iostream>

namespace Vector {
namespace BLF {

static void hexDump(char * data, size_t size)
{
    std::cerr << "hexdump size: 0x" << size << std::endl;
    for (size_t n = 0; n < size; ++n) {
        unsigned short value = (unsigned char) *data;
        if (value < 0x10)
            std::cerr << "0";
        std::cerr << std::hex << value << " ";
        data++;
        if (n % 4 == 3)
            std::cerr << " ";
        if (n % 16 == 15)
            std::cerr << std::endl;
    }
    std::cerr << std::endl;
}

File::File() :
    openMode(OpenMode::Read),
    compressionLevel(Z_DEFAULT_COMPRESSION),
    fileStatistics(),
    currentUncompressedFileSize(0),
    currentObjectCount(0),
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

    if (this->openMode == OpenMode::Read) {
        compressedFile.open(filename, std::ios_base::in | std::ios_base::binary);
        if (!is_open())
            return;

        /* do file statistics */
        fileStatistics.read(compressedFile);
        currentUncompressedFileSize += 0x90;
    } else {
        compressedFile.open(filename, std::ios_base::out | std::ios_base::binary);
        if (!is_open())
            return;

        /* do file statistics */
        fileStatistics.write(compressedFile);
    }
}

void File::open(const std::string & filename, OpenMode openMode)
{
    open(filename.c_str(), openMode);
}

bool File::is_open() const
{
    return compressedFile.is_open();
}

void File::close()
{
    if (openMode == OpenMode::Write) {
        compressedFile.seekg(0);
        fileStatistics.write(compressedFile);
    }

    compressedFile.close();
}

bool File::eof()
{
    bool compressedFileEmpty = (compressedFile.tellg() >= fileStatistics.fileSize) || compressedFile.eof();
    bool uncompressedFileEmpty = (uncompressedFile.size() <= 0);
    return compressedFileEmpty && uncompressedFileEmpty;
}

ObjectHeaderBase * File::readObjectFromCompressedFile()
{
    /* read and parse object header base */
    char * ohbBuffer = new char[0x10];
    if (ohbBuffer == nullptr) {
        std::cerr << "out of memory" << std::endl;
        return nullptr;
    }
    compressedFile.read(ohbBuffer, 0x10);
    if (!compressedFile) {
        std::cerr << "compressed data exhausted!" << std::endl;
        delete[] ohbBuffer;
        return nullptr;
    }
    ObjectHeaderBase ohb;
    ohb.parse(ohbBuffer);

    /* read full object */
    char * objBuffer = nullptr;
    if ((ohb.objectSize - 0x10) > 0) {
        objBuffer = new char[ohb.objectSize];
        if (objBuffer == nullptr) {
            std::cerr << "out of memory" << std::endl;
            delete[] ohbBuffer;
            return nullptr;
        }

        /* copy object header base */
        memcpy(objBuffer, ohbBuffer, 0x10);
        delete[] ohbBuffer;

        /* read rest of object */
        compressedFile.read(objBuffer + 0x10, ohb.objectSize - 0x10);
        if (!compressedFile) {
            std::cerr << "compressed data exhausted!" << std::endl;
            delete[] objBuffer;
            return nullptr;
        }
    }

    /* create object */
    ObjectHeaderBase * obj = createObject(ohb.objectType);
    if (obj == nullptr) {
        std::cerr << "createObject returned nullptr" << std::endl;
        if (objBuffer != nullptr)
            delete[] objBuffer;
        return nullptr;
    }

    /* parse object data or skip */
    char * ptr = obj->parse(objBuffer);

    /* handle if there is size remaining */
    size_t remainingSize = obj->objectSize - (ptr - objBuffer);
    if (remainingSize != 0) {
        std::cerr << "objectType: " << std::dec << (unsigned short) ohb.objectType << std::endl;
        std::cerr << "remainingSize: 0x" << std::hex << remainingSize << std::endl;
        hexDump(objBuffer, ohb.objectSize);
    }

    /* delete buffers */
    if (objBuffer != nullptr)
        delete[] objBuffer;

    /* skip padding */
    compressedFile.seekg(ohb.objectSize % 4, std::iostream::cur);

    return obj;
}

ObjectHeaderBase * File::readObjectFromUncompressedFile()
{
    /* read and parse object header base */
    ObjectHeaderBase ohb;
    char * ohbBuffer = nullptr;
    if (readFromUncompressedFile(&ohbBuffer, 0x10) == 0)
        return nullptr;
    ohb.parse(ohbBuffer);

    /* read full object */
    char * objBuffer = nullptr;
    if ((ohb.objectSize - 0x10) > 0) {
        objBuffer = new char[ohb.objectSize];
        if (objBuffer == nullptr) {
            std::cerr << "out of memory" << std::endl;
            delete[] ohbBuffer;
            return nullptr;
        }

        /* copy object header base */
        memcpy(objBuffer, ohbBuffer, 0x10);
        delete[] ohbBuffer;

        /* read rest of object */
        char * objBuffer2 = nullptr;
        if (readFromUncompressedFile(&objBuffer2, ohb.objectSize - 0x10) == 0) {
            std::cerr << "readFromUncompressedFile returned nullptr" << std::endl;
        } else {
            memcpy(objBuffer + 0x10, objBuffer2, ohb.objectSize - 0x10);
            delete[] objBuffer2;
        }
    }

    /* create object */
    ObjectHeaderBase * obj = createObject(ohb.objectType);
    if (obj == nullptr) {
        std::cerr << "createObject returned nullptr" << std::endl;
        if (objBuffer != nullptr)
            delete[] objBuffer;
        return nullptr;
    }

    /* parse object data or skip */
    char * ptr = obj->parse(objBuffer);

    /* handle if there is size remaining */
    size_t remainingSize = obj->objectSize - (ptr - objBuffer);
    if (remainingSize != 0) {
        std::cerr << "objectType: " << std::dec << (unsigned short) ohb.objectType << std::endl;
        std::cerr << "remainingSize: 0x" << std::hex << remainingSize << std::endl;
        hexDump(objBuffer, ohb.objectSize);
    }

    /* delete buffers */
    if (objBuffer != nullptr)
        delete[] objBuffer;

    /* skip padding */
    uncompressedFile.skipg(ohb.objectSize % 4);

    currentObjectCount++;
    return obj;
}

void File::inflateLogContainer(LogContainer * logContainer)
{
    /* safety check */
    if (logContainer == nullptr) {
        std::cerr << "inflateLogContainer called with no logContainer" << std::endl;
        return;
    }

    /* create buffer */
    size_t bufferSize = logContainer->uncompressedFileSize;
    char * buffer = new char[bufferSize];
    if (buffer == nullptr) {
        std::cerr << "out of memory" << std::endl;
        return;
    }

    /* inflate */
    uLongf bufferSize2 = bufferSize;
    uncompress(reinterpret_cast<Bytef *>(buffer),
               &bufferSize2,
               reinterpret_cast<Bytef *>(logContainer->compressedFile),
               logContainer->compressedFileSize);

    /* copy into stringstream */
    uncompressedFile.write(buffer, bufferSize);

    /* delete buffer */
    delete[] buffer;
}

size_t File::readFromUncompressedFile(char ** buffer, size_t size)
{
    /* safety check */
    if (buffer == nullptr) {
        std::cerr << "readFromUncompressedFile with nullptr argument" << std::endl;
        return 0;
    }

    /* first read some more compressed data and inflate it */
    while (uncompressedFile.size() < size) {
        ObjectHeaderBase * obj = readObjectFromCompressedFile();
        if (obj == nullptr) {
            std::cerr << "readObjectFromCompressedFile returned nullptr" << std::endl;
            return 0;
        }
        if (obj->objectType == ObjectType::LOG_CONTAINER) {
            LogContainer * logContainer = reinterpret_cast<LogContainer *>(obj);
            currentUncompressedFileSize += 0x20; // ObjectHeaderBase + ObjectHeader
            currentUncompressedFileSize += logContainer->uncompressedFileSize;

            /* inflate the log container */
            inflateLogContainer(logContainer);
            delete logContainer;
        } else {
            std::cerr << "unexpected object in compressed file" << std::endl;
            return 0;
        }
    }

    /* read back */
    *buffer = new char[size];
    if (*buffer == nullptr) {
        std::cerr << "out of memory" << std::endl;
        return 0;
    }
    uncompressedFile.read(*buffer, size);
    if (uncompressedFile.gcount < size) {
        std::cerr << "uncompressed data exhausted" << std::endl;
        delete[] *buffer;
        *buffer = nullptr;
        return 0;
    }
    return size;
}

ObjectHeaderBase * File::read()
{
    if (openMode == OpenMode::Write)
        return nullptr;

    return readObjectFromUncompressedFile();
}

bool File::write(ObjectHeaderBase * objectHeaderBase)
{
    if (openMode == OpenMode::Read)
        return false;

    /* get size of object */
    size_t remainingSize = objectHeaderBase->calculateObjectSize();

    /* copy as many data as possible in existing uncompressed file */
    if (uncompressedFile.size() < remainaingSize) {

    }

    /* if data remaining, compress data and extend uncompressed file */
    if (remainingSize > 0) {

    }

    return true;
}

}
}
