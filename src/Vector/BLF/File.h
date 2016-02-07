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

#pragma once

#include "platform.h"

#include <fstream>

#include "CompressedFile.h"
#include "FileStatistics.h"
#include "ObjectHeaderBase.h"
#include "UncompressedFile.h"
#include "VectorTypes.h"

// UNKNOWN = 0
#include "CanMessage.h" // CAN_MESSAGE = 1
#include "CanErrorFrame.h" // CAN_ERROR = 2
#include "CanOverloadFrame.h" // CAN_OVERLOAD = 3
#include "CanDriverStatistic.h" // CAN_STATISTIC = 4
#include "AppTrigger.h" // APP_TRIGGER = 5
#include "EnvironmentVariable.h" // ENV_INTEGER = 6
#include "EnvironmentVariable.h" // ENV_DOUBLE = 7
#include "EnvironmentVariable.h" // ENV_STRING = 8
#include "EnvironmentVariable.h" // ENV_DATA = 9
#include "LogContainer.h" // LOG_CONTAINER = 10
#include "LinMessage.h" // LIN_MESSAGE = 11
#include "LinCrcError.h" // LIN_CRC_ERROR = 12
#include "LinDlcInfo.h" // LIN_DLC_INFO = 13
#include "LinReceiveError.h" // LIN_RCV_ERROR =  14
#include "LinSendError.h" // LIN_SND_ERROR = 15
#include "LinSlaveTimeout.h" // LIN_SLV_TIMEOUT = 16
#include "LinSchedulerModeChange.h" // LIN_SCHED_MODCH = 17
#include "LinSyncError.h" // LIN_SYN_ERROR = 18
#include "LinBaudrateEvent.h" // LIN_BAUDRATE = 19
#include "LinSleepModeEvent.h" // LIN_SLEEP = 20
#include "LinWakeupEvent.h" // LIN_WAKEUP = 21
#include "MostSpy.h" // MOST_SPY = 22
#include "MostCtrl.h" // MOST_CTRL = 23
#include "MostLightLock.h" // MOST_LIGHTLOCK = 24
#include "MostStatistic.h" // MOST_STATISTIC = 25
// reserved_1 = 26
// reserved_2 = 27
// reserved_3 = 28
#include "FlexRayData.h" // FLEXRAY_DATA = 29
#include "FlexRaySync.h" // FLEXRAY_SYNC = 30
#include "CanDriverError.h" // CAN_DRIVER_ERROR = 31
#include "MostPkt.h" // MOST_PKT  = 32
#include "MostPkt2.h" // MOST_PKT2 = 33
#include "MostHwMode.h" // MOST_HWMODE = 34
#include "MostReg.h" // MOST_REG = 35
#include "MostGenReg.h" // MOST_GENREG = 36
#include "MostNetState.h" // MOST_NETSTATE = 37
#include "MostDataLost.h" // MOST_DATALOST = 38
#include "MostTrigger.h" // MOST_TRIGGER = 39
#include "FlexRayV6StartCycleEvent.h" // FLEXRAY_CYCLE = 40
#include "FlexRayV6Message.h" // FLEXRAY_MESSAGE = 41
#include "LinChecksumInfo.h" // LIN_CHECKSUM_INFO = 42
#include "LinSpikeEvent.h" // LIN_SPIKE_EVENT = 43
#include "CanDriverHwSync.h" // CAN_DRIVER_SYNC = 44
#include "FlexRayStatusEvent.h" // FLEXRAY_STATUS = 45
#include "GpsEvent.h" // GPS_EVENT = 46
#include "FlexRayVFrError.h" // FR_ERROR = 47
#include "FlexRayVFrStatus.h" // FR_STATUS = 48
#include "FlexRayVFrStartCycle.h" // FR_STARTCYCLE = 49
#include "FlexRayVFrReceiveMsg.h" // FR_RCVMESSAGE = 50
#include "RealtimeClock.h" // REALTIMECLOCK = 51
// AVAILABLE2 = 52
// AVAILABLE3 = 53
#include "LinStatisticEvent.h" // LIN_STATISTIC = 54
#include "J1708Message.h" // J1708_MESSAGE = 55
#include "J1708Message.h" // J1708_VIRTUAL_MSG = 56
#include "LinMessage2.h" // LIN_MESSAGE2 = 57
#include "LinSendError2.h" // LIN_SND_ERROR2 = 58
#include "LinSyncError2.h" // LIN_SYN_ERROR2 = 59
#include "LinCrcError2.h" // LIN_CRC_ERROR2 = 60
#include "LinReceiveError2.h" // LIN_RCV_ERROR2 = 61
#include "LinWakeupEvent2.h" // LIN_WAKEUP2 = 62
#include "LinSpikeEvent2.h" // LIN_SPIKE_EVENT2 = 63
#include "LinLongDomSignalEvent.h" // LIN_LONG_DOM_SIG = 64
#include "AppText.h" // APP_TEXT = 65
#include "FlexRayVFrReceiveMsgEx.h" // FR_RCVMESSAGE_EX = 66
#include "MostStatisticEx.h" // MOST_STATISTICEX = 67
#include "MostTxLight.h" // MOST_TXLIGHT = 68
#include "MostAllocTab.h" // MOST_ALLOCTAB = 69
#include "MostStress.h" // MOST_STRESS = 70
#include "EthernetFrame.h" // ETHERNET_FRAME = 71
#include "SystemVariable.h" // SYS_VARIABLE = 72
#include "CanErrorFrameExt.h" // CAN_ERROR_EXT = 73
#include "CanDriverErrorExt.h" // CAN_DRIVER_ERROR_EXT = 74
#include "LinLongDomSignalEvent2.h" // LIN_LONG_DOM_SIG2 = 75
#include "Most150Message.h" // MOST_150_MESSAGE = 76
#include "Most150Pkt.h" // MOST_150_PKT = 77
#include "MostEthernetPkt.h" // MOST_ETHERNET_PKT = 78
#include "Most150MessageFragment.h" // MOST_150_MESSAGE_FRAGMENT = 79
#include "Most150PktFragment.h" // MOST_150_PKT_FRAGMENT = 80
#include "MostEthernetPktFragment.h" // MOST_ETHERNET_PKT_FRAGMENT = 81
#include "MostSystemEvent.h" // MOST_SYSTEM_EVENT = 82
#include "Most150AllocTab.h" // MOST_150_ALLOCTAB = 83
#include "Most50Message.h" // MOST_50_MESSAGE = 84
#include "Most50Pkt.h" // MOST_50_PKT = 85
#include "CanMessage2.h" // CAN_MESSAGE2 = 86
#include "LinUnexpectedWakeup.h" // LIN_UNEXPECTED_WAKEUP = 87
#include "LinShortOrSlowResponse.h" // LIN_SHORT_OR_SLOW_RESPONSE = 88
#include "LinDisturbanceEvent.h" // LIN_DISTURBANCE_EVENT = 89
#include "SerialEvent.h" // SERIAL_EVENT = 90
#include "DriverOverrun.h" // OVERRUN_ERROR = 91
#include "EventComment.h" // EVENT_COMMENT = 92
#include "WlanFrame.h" // WLAN_FRAME = 93
#include "WlanStatistic.h" // WLAN_STATISTIC = 94
#include "MostEcl.h" // MOST_ECL = 95
#include "GlobalMarker.h" // GLOBAL_MARKER = 96
#include "AfdxFrame.h" // AFDX_FRAME = 97
#include "AfdxStatistic.h" // AFDX_STATISTIC = 98
#include "KLineStatusEvent.h" // KLINE_STATUSEVENT = 99
#include "CanFdMessage.h" // CAN_FD_MESSAGE = 100
#include "CanFdMessage64.h" // CAN_FD_MESSAGE_64 = 101
#include "EthernetRxError.h" // ETHERNET_RX_ERROR = 102
#include "EthernetStatus.h" // ETHERNET_STATUS = 103
#include "CanFdErrorFrame64.h" // CAN_FD_ERROR_64 = 104

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * File
 *
 * This is similar to std::fstream for BLFs
 */
class VECTOR_BLF_EXPORT File
{
public:
    File();

    /** enumeration for openMode */
    enum class OpenMode {
        /** Read */
        Read = 0,

        /** Write */
        Write = 1
    };

    /** open mode */
    OpenMode openMode;

    /** file statistics from file header. contains total counts/sizes */
    FileStatistics fileStatistics;

    /** current uncompressed file size */
    unsigned long currentUncompressedFileSize;

    /** current number of objects read */
    unsigned long currentObjectCount;

    /** zlib compression level (0=no compression, 1=best speed, 9=best compression, -1=default compression */
    int compressionLevel;

    /** default log container size */
    size_t defaultLogContainerSize;

    /**
     * open file
     *
     * @param filename file name
     * @param openMode open in read or write mode
     */
    void open(const char * filename, OpenMode openMode = OpenMode::Read);

    /**
     * open file
     *
     * @param filename file name
     * @param openMode open in read or write mode
     */
    void open(const std::string & filename, OpenMode openMode = OpenMode::Read);

    /**
     * is file open?
     *
     * @return true if file is open
     */
    bool is_open() const;

    /**
     * check for end-of-file
     *
     * @return true if end-of-file reached
     */
    bool eof();

    /**
     * read object from file
     *
     * @return read object or nullptr
     */
    ObjectHeaderBase * read();

    /**
     * write object to file
     *
     * @param objectHeaderBase write object
     */
    void write(ObjectHeaderBase * objectHeaderBase);

    /** close file */
    void close();

private:
    /** compressed file */
    CompressedFile compressedFile;

    /** uncompressed file */
    UncompressedFile uncompressedFile;

    /**
     * create object of given type
     *
     * @param type object type
     * @return new object
     */
    ObjectHeaderBase * createObject(ObjectType type);

    /**
     * read object from compressed file
     *
     * @return object from compressed file or nullptr
     */
    ObjectHeaderBase * readObjectFromCompressedFile();

    /**
     * read object from uncompressed file
     *
     * @return object from uncompressed file or nullptr
     */
    ObjectHeaderBase * readObjectFromUncompressedFile();

    /**
     * inflate/uncompress date from compressed file into uncompressed file
     */
    void inflate();

    /**
     * deflate/compress data from uncompressed file into compressed file
     */
    void deflate();
};

}
}
