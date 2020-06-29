/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/ObjectHeaderBase.h>

#include <Vector/BLF/Exceptions.h>

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
#include <Vector/BLF/FunctionBus.h> // FUNCTION_BUS = 124
#include <Vector/BLF/DataLostBegin.h> // DATA_LOST_BEGIN = 125
#include <Vector/BLF/DataLostEnd.h> // DATA_LOST_END = 126
#include <Vector/BLF/WaterMarkEvent.h> // WATER_MARK_EVENT = 127
#include <Vector/BLF/TriggerCondition.h> // TRIGGER_CONDITION = 128

namespace Vector {
namespace BLF {

ObjectHeaderBase::ObjectHeaderBase(const WORD headerVersion, const ObjectType objectType) :
    headerVersion(headerVersion),
    objectType(objectType) {
}

std::vector<uint8_t>::iterator ObjectHeaderBase::fromData(std::vector<uint8_t>::iterator it) {
    signature =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    if (signature != ObjectSignature)
        throw Exception("ObjectHeaderBase::fromData(): Object signature doesn't match.");
    headerSize =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    headerVersion =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    objectSize =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    objectType = static_cast<ObjectType>(
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24));

    return it;
}

void ObjectHeaderBase::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    headerSize = calculateHeaderSize();
    objectSize = calculateObjectSize();

    data.push_back((signature >>  0) & 0xff);
    data.push_back((signature >>  8) & 0xff);
    data.push_back((signature >> 16) & 0xff);
    data.push_back((signature >> 24) & 0xff);
    data.push_back((headerSize >>  0) & 0xff);
    data.push_back((headerSize >>  8) & 0xff);
    data.push_back((headerVersion >>  0) & 0xff);
    data.push_back((headerVersion >>  8) & 0xff);
    data.push_back((objectSize >>  0) & 0xff);
    data.push_back((objectSize >>  8) & 0xff);
    data.push_back((objectSize >> 16) & 0xff);
    data.push_back((objectSize >> 24) & 0xff);
    data.push_back((static_cast<DWORD>(objectType) >>  0) & 0xff);
    data.push_back((static_cast<DWORD>(objectType) >>  8) & 0xff);
    data.push_back((static_cast<DWORD>(objectType) >> 16) & 0xff);
    data.push_back((static_cast<DWORD>(objectType) >> 24) & 0xff);
}

WORD ObjectHeaderBase::calculateHeaderSize() const {
    return
        sizeof(signature) +
        sizeof(headerSize) +
        sizeof(headerVersion) +
        sizeof(objectSize) +
        sizeof(objectType);
}

DWORD ObjectHeaderBase::calculateObjectSize() const {
    return calculateHeaderSize();
}

ObjectHeaderBase * makeObject(const ObjectType type) {
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

    case ObjectType::FUNCTION_BUS:
        obj = new FunctionBus;
        break;

    case ObjectType::DATA_LOST_BEGIN:
        obj = new DataLostBegin;
        break;

    case ObjectType::DATA_LOST_END:
        obj = new DataLostEnd;
        break;

    case ObjectType::WATER_MARK_EVENT:
        obj = new WaterMarkEvent;
        break;

    case ObjectType::TRIGGER_CONDITION:
        obj = new TriggerCondition;
        break;
    }

    return obj;
}

}
}
