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

#include <Vector/BLF/platform.h>

#include <atomic>
#include <fstream>
#include <thread>

#include <Vector/BLF/CompressedFile.h>
#include <Vector/BLF/FileStatistics.h>
#include <Vector/BLF/ObjectHeaderBase.h>
#include <Vector/BLF/ObjectQueue.h>
#include <Vector/BLF/UncompressedFile.h>
#include <Vector/BLF/VectorTypes.h>

// UNKNOWN = 0
#include <Vector/BLF/CanMessage.h> // CAN_MESSAGE = 1
#include <Vector/BLF/CanErrorFrame.h> // CAN_ERROR = 2
#include <Vector/BLF/CanOverloadFrame.h> // CAN_OVERLOAD = 3
#include <Vector/BLF/CanDriverStatistic.h> // CAN_STATISTIC = 4
#include <Vector/BLF/AppTrigger.h> // APP_TRIGGER = 5
#include <Vector/BLF/EnvironmentVariable.h> // ENV_INTEGER = 6
#include <Vector/BLF/EnvironmentVariable.h> // ENV_DOUBLE = 7
#include <Vector/BLF/EnvironmentVariable.h> // ENV_STRING = 8
#include <Vector/BLF/EnvironmentVariable.h> // ENV_DATA = 9
#include <Vector/BLF/LogContainer.h> // LOG_CONTAINER = 10
#include <Vector/BLF/LinMessage.h> // LIN_MESSAGE = 11
#include <Vector/BLF/LinCrcError.h> // LIN_CRC_ERROR = 12
#include <Vector/BLF/LinDlcInfo.h> // LIN_DLC_INFO = 13
#include <Vector/BLF/LinReceiveError.h> // LIN_RCV_ERROR =  14
#include <Vector/BLF/LinSendError.h> // LIN_SND_ERROR = 15
#include <Vector/BLF/LinSlaveTimeout.h> // LIN_SLV_TIMEOUT = 16
#include <Vector/BLF/LinSchedulerModeChange.h> // LIN_SCHED_MODCH = 17
#include <Vector/BLF/LinSyncError.h> // LIN_SYN_ERROR = 18
#include <Vector/BLF/LinBaudrateEvent.h> // LIN_BAUDRATE = 19
#include <Vector/BLF/LinSleepModeEvent.h> // LIN_SLEEP = 20
#include <Vector/BLF/LinWakeupEvent.h> // LIN_WAKEUP = 21
#include <Vector/BLF/MostSpy.h> // MOST_SPY = 22
#include <Vector/BLF/MostCtrl.h> // MOST_CTRL = 23
#include <Vector/BLF/MostLightLock.h> // MOST_LIGHTLOCK = 24
#include <Vector/BLF/MostStatistic.h> // MOST_STATISTIC = 25
// Reserved26 = 26
// Reserved27 = 27
// Reserved28 = 28
#include <Vector/BLF/FlexRayData.h> // FLEXRAY_DATA = 29
#include <Vector/BLF/FlexRaySync.h> // FLEXRAY_SYNC = 30
#include <Vector/BLF/CanDriverError.h> // CAN_DRIVER_ERROR = 31
#include <Vector/BLF/MostPkt.h> // MOST_PKT  = 32
#include <Vector/BLF/MostPkt2.h> // MOST_PKT2 = 33
#include <Vector/BLF/MostHwMode.h> // MOST_HWMODE = 34
#include <Vector/BLF/MostReg.h> // MOST_REG = 35
#include <Vector/BLF/MostGenReg.h> // MOST_GENREG = 36
#include <Vector/BLF/MostNetState.h> // MOST_NETSTATE = 37
#include <Vector/BLF/MostDataLost.h> // MOST_DATALOST = 38
#include <Vector/BLF/MostTrigger.h> // MOST_TRIGGER = 39
#include <Vector/BLF/FlexRayV6StartCycleEvent.h> // FLEXRAY_CYCLE = 40
#include <Vector/BLF/FlexRayV6Message.h> // FLEXRAY_MESSAGE = 41
#include <Vector/BLF/LinChecksumInfo.h> // LIN_CHECKSUM_INFO = 42
#include <Vector/BLF/LinSpikeEvent.h> // LIN_SPIKE_EVENT = 43
#include <Vector/BLF/CanDriverHwSync.h> // CAN_DRIVER_SYNC = 44
#include <Vector/BLF/FlexRayStatusEvent.h> // FLEXRAY_STATUS = 45
#include <Vector/BLF/GpsEvent.h> // GPS_EVENT = 46
#include <Vector/BLF/FlexRayVFrError.h> // FR_ERROR = 47
#include <Vector/BLF/FlexRayVFrStatus.h> // FR_STATUS = 48
#include <Vector/BLF/FlexRayVFrStartCycle.h> // FR_STARTCYCLE = 49
#include <Vector/BLF/FlexRayVFrReceiveMsg.h> // FR_RCVMESSAGE = 50
#include <Vector/BLF/RealtimeClock.h> // REALTIMECLOCK = 51
// Reserved52 = 52
// Reserved53 = 53
#include <Vector/BLF/LinStatisticEvent.h> // LIN_STATISTIC = 54
#include <Vector/BLF/J1708Message.h> // J1708_MESSAGE = 55
#include <Vector/BLF/J1708Message.h> // J1708_VIRTUAL_MSG = 56
#include <Vector/BLF/LinMessage2.h> // LIN_MESSAGE2 = 57
#include <Vector/BLF/LinSendError2.h> // LIN_SND_ERROR2 = 58
#include <Vector/BLF/LinSyncError2.h> // LIN_SYN_ERROR2 = 59
#include <Vector/BLF/LinCrcError2.h> // LIN_CRC_ERROR2 = 60
#include <Vector/BLF/LinReceiveError2.h> // LIN_RCV_ERROR2 = 61
#include <Vector/BLF/LinWakeupEvent2.h> // LIN_WAKEUP2 = 62
#include <Vector/BLF/LinSpikeEvent2.h> // LIN_SPIKE_EVENT2 = 63
#include <Vector/BLF/LinLongDomSignalEvent.h> // LIN_LONG_DOM_SIG = 64
#include <Vector/BLF/AppText.h> // APP_TEXT = 65
#include <Vector/BLF/FlexRayVFrReceiveMsgEx.h> // FR_RCVMESSAGE_EX = 66
#include <Vector/BLF/MostStatisticEx.h> // MOST_STATISTICEX = 67
#include <Vector/BLF/MostTxLight.h> // MOST_TXLIGHT = 68
#include <Vector/BLF/MostAllocTab.h> // MOST_ALLOCTAB = 69
#include <Vector/BLF/MostStress.h> // MOST_STRESS = 70
#include <Vector/BLF/EthernetFrame.h> // ETHERNET_FRAME = 71
#include <Vector/BLF/SystemVariable.h> // SYS_VARIABLE = 72
#include <Vector/BLF/CanErrorFrameExt.h> // CAN_ERROR_EXT = 73
#include <Vector/BLF/CanDriverErrorExt.h> // CAN_DRIVER_ERROR_EXT = 74
#include <Vector/BLF/LinLongDomSignalEvent2.h> // LIN_LONG_DOM_SIG2 = 75
#include <Vector/BLF/Most150Message.h> // MOST_150_MESSAGE = 76
#include <Vector/BLF/Most150Pkt.h> // MOST_150_PKT = 77
#include <Vector/BLF/MostEthernetPkt.h> // MOST_ETHERNET_PKT = 78
#include <Vector/BLF/Most150MessageFragment.h> // MOST_150_MESSAGE_FRAGMENT = 79
#include <Vector/BLF/Most150PktFragment.h> // MOST_150_PKT_FRAGMENT = 80
#include <Vector/BLF/MostEthernetPktFragment.h> // MOST_ETHERNET_PKT_FRAGMENT = 81
#include <Vector/BLF/MostSystemEvent.h> // MOST_SYSTEM_EVENT = 82
#include <Vector/BLF/Most150AllocTab.h> // MOST_150_ALLOCTAB = 83
#include <Vector/BLF/Most50Message.h> // MOST_50_MESSAGE = 84
#include <Vector/BLF/Most50Pkt.h> // MOST_50_PKT = 85
#include <Vector/BLF/CanMessage2.h> // CAN_MESSAGE2 = 86
#include <Vector/BLF/LinUnexpectedWakeup.h> // LIN_UNEXPECTED_WAKEUP = 87
#include <Vector/BLF/LinShortOrSlowResponse.h> // LIN_SHORT_OR_SLOW_RESPONSE = 88
#include <Vector/BLF/LinDisturbanceEvent.h> // LIN_DISTURBANCE_EVENT = 89
#include <Vector/BLF/SerialEvent.h> // SERIAL_EVENT = 90
#include <Vector/BLF/DriverOverrun.h> // OVERRUN_ERROR = 91
#include <Vector/BLF/EventComment.h> // EVENT_COMMENT = 92
#include <Vector/BLF/WlanFrame.h> // WLAN_FRAME = 93
#include <Vector/BLF/WlanStatistic.h> // WLAN_STATISTIC = 94
#include <Vector/BLF/MostEcl.h> // MOST_ECL = 95
#include <Vector/BLF/GlobalMarker.h> // GLOBAL_MARKER = 96
#include <Vector/BLF/AfdxFrame.h> // AFDX_FRAME = 97
#include <Vector/BLF/AfdxStatistic.h> // AFDX_STATISTIC = 98
#include <Vector/BLF/KLineStatusEvent.h> // KLINE_STATUSEVENT = 99
#include <Vector/BLF/CanFdMessage.h> // CAN_FD_MESSAGE = 100
#include <Vector/BLF/CanFdMessage64.h> // CAN_FD_MESSAGE_64 = 101
#include <Vector/BLF/EthernetRxError.h> // ETHERNET_RX_ERROR = 102
#include <Vector/BLF/EthernetStatus.h> // ETHERNET_STATUS = 103
#include <Vector/BLF/CanFdErrorFrame64.h> // CAN_FD_ERROR_64 = 104
#include <Vector/BLF/LinShortOrSlowResponse2.h> // LIN_SHORT_OR_SLOW_RESPONSE2 = 105
#include <Vector/BLF/AfdxStatus.h> // AFDX_STATUS = 106
#include <Vector/BLF/AfdxBusStatistic.h> // AFDX_BUS_STATISTIC = 107
// Reserved108 = 108
#include <Vector/BLF/AfdxErrorEvent.h> // AFDX_ERROR_EVENT = 109
#include <Vector/BLF/A429Error.h> // A429_ERROR = 110
#include <Vector/BLF/A429Status.h> // A429_STATUS = 111
#include <Vector/BLF/A429BusStatistic.h> // A429_BUS_STATISTIC = 112
#include <Vector/BLF/A429Message.h> // A429_MESSAGE = 113
#include <Vector/BLF/EthernetStatistic.h> // ETHERNET_STATISTIC = 114
#include <Vector/BLF/Unknown115.h> // Unknown115 = 115
// Reserved116 = 116
// Reserved117 = 117
#include <Vector/BLF/TestStructure.h> // TEST_STRUCTURE = 118
#include <Vector/BLF/DiagRequestInterpretation.h> // DIAG_REQUEST_INTERPRETATION = 119
#include <Vector/BLF/EthernetFrameEx.h> // ETHERNET_FRAME_EX = 120
#include <Vector/BLF/EthernetFrameForwarded.h> // ETHERNET_FRAME_FORWARDED = 121
#include <Vector/BLF/EthernetErrorEx.h> // ETHERNET_ERROR_EX = 122
#include <Vector/BLF/EthernetErrorForwarded.h> // ETHERNET_ERROR_FORWARDED = 123

#include <Vector/BLF/vector_blf_export.h>

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
    virtual ~File();

    /**
     * File statistics from file header. contains total counts/sizes
     */
    FileStatistics fileStatistics;

    /**
     * Current file size
     */
    ULONGLONG currentFileSize();

    /**
     * Current uncompressed file size
     *
     * This includes the LogContainer headers, and the uncompressed content.
     */
    ULONGLONG currentUncompressedFileSize;

    /**
     * Current number of objects read
     *
     * Unknown115 is not counted.
     */
    DWORD currentObjectCount;

    /**
     * zlib compression level (0=no compression, 1=best speed, 9=best compression, -1=default compression
     */
    int compressionLevel;

    /**
     * Write Unknown115 message at file close
     */
    bool writeUnknown115;

    /**
     * open file
     *
     * @param[in] filename file name
     * @param[in] mode open mode, either in (read) or out (write)
     */
    virtual void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in);

    /**
     * open file
     *
     * @param[in] filename file name
     * @param[in] mode open mode, either in (read) or out (write)
     */
    virtual void open(const std::string & filename, std::ios_base::openmode mode = std::ios_base::in);

    /**
     * is file open?
     *
     * @return true if file is open
     */
    virtual bool is_open() const;

    /**
     * check for end-of-file
     *
     * @return true if end-of-file reached
     */
    virtual bool eof();

    /**
     * read object from file
     *
     * @return read object or nullptr
     */
    virtual ObjectHeaderBase * read();

    /**
     * write object to file
     *
     * @param[in] ohb write object
     */
    virtual void write(ObjectHeaderBase * ohb);

    /**
     * close file
     */
    virtual void close();

    /**
     * Get default log container size.
     *
     * @return default log container size
     */
    virtual DWORD defaultLogContainerSize() const;

    /**
     * Set default log container size.
     *
     * @param[in] defaultLogContainerSize default log container size
     */
    virtual void setDefaultLogContainerSize(DWORD defaultLogContainerSize);

    /**
     * create object of given type
     *
     * @param type object type
     * @return new object
     */
    static ObjectHeaderBase * createObject(ObjectType type);

private:
    /**
     * Open mode
     */
    std::ios_base::openmode m_openMode;

    /* read/write queue */

    /**
     * read/write queue
     *
     * When the write method is called the object is enqueued here, so that it returns quickly to the calling
     * application. The readWriteThread gets the objects out of the queue and puts them into the compressedFile.
     *
     * When the read method is called the object is taken out of the queue, so that it returns quickly to the calling
     * application. If there are no objects in the queue, the methods waits for the readWriteThread to finish.
     * The readWriteThread reads objects from the compressedfile and puts them into the queue.
     */
    ObjectQueue<ObjectHeaderBase> m_readWriteQueue;

    /* uncompressed file */

    /**
     * uncompressed file
     *
     * This file contains the data, contained in the (compressed) log containers.
     * The readWriteThread transfers data from/to here into the readWriteQueue.
     * The compressionThread transfers data from/to here into the uncompressedFile.
     */
    UncompressedFile m_uncompressedFile;

    /**
     * thread between readWriteQueue and uncompressedFile
     */
    std::thread m_uncompressedFileThread;

    /**
     * thread still running
     */
    std::atomic_bool m_uncompressedFileThreadRunning;

    /* compressed file */

    /**
     * compressed file
     *
     * This file is actually the fstream, so the actual BLF data.
     * It mainly contains the FileStatistics and several LogContainers carrying the different objects.
     * The compressionThread transfers data from/to here into the compressedFile.
     */
    CompressedFile m_compressedFile;

    /**
     * thread between uncompressedFile and compressedFile
     */
    std::thread m_compressedFileThread;

    /**
     * thread still running
     */
    std::atomic_bool m_compressedFileThreadRunning;

    /* internal functions */

    /**
     * Read data from uncompressedFile into readWriteQueue.
     */
    void uncompressedFile2ReadWriteQueue();

    /**
     * Write data from readWriteQueue into uncompressedFile.
     */
    void readWriteQueue2UncompressedFile();

    /**
     * Read/inflate/uncompress data from compressedFile into uncompressedFile.
     */
    void compressedFile2UncompressedFile();

    /**
     * Write/deflate/compress data from uncompressedFile into compressedFile.
     */
    void uncompressedFile2CompressedFile();

    /**
     * transfer data from uncompressedFile to readWriteQueue
     */
    static void uncompressedFileReadThread(File * file);

    /**
     * transfer data from readWriteQueue to uncompressedfile
     */
    static void uncompressedFileWriteThread(File * file);

    /**
     * transfer data from compressedFile to uncompressedFile
     */
    static void compressedFileReadThread(File * file);

    /**
     * transfer data from uncompressedfile to compressedFile
     */
    static void compressedFileWriteThread(File * file);
};

}
}
