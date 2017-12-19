#include <iostream>
#include <fstream>

#include <Vector/BLF.h>

void show(Vector::BLF::FileStatistics * obj)
{
    std::cout << "statisticsSize: "
              << "0x" << std::hex << obj->statisticsSize << std::endl;
    std::cout << "applicationId: "
              << std::dec << static_cast<uint16_t>(obj->applicationId) << std::endl;
    std::cout << "applicationVersion: "
              << static_cast<uint16_t>(obj->applicationMajor) << "."
              << static_cast<uint16_t>(obj->applicationMinor) << "."
              << static_cast<uint16_t>(obj->applicationBuild) << std::endl;
    std::cout << "apiVersion: "
              << static_cast<uint16_t>(obj->apiMajor) << "."
              << static_cast<uint16_t>(obj->apiMinor) << "."
              << static_cast<uint16_t>(obj->apiBuild) << "."
              << static_cast<uint16_t>(obj->apiPatch) << std::endl;
    std::cout << "fileSize: "
              << obj->fileSize << std::endl;
    std::cout << "uncompressedFileSize: " << obj->uncompressedFileSize <<
              " (hex: 0x" << std::hex << obj->uncompressedFileSize << ")" << std::dec << std::endl;
    std::cout << "objectCount: "
              << obj->objectCount << std::endl;
    std::cout << "objectsRead: "
              << obj->objectsRead << std::endl;
    std::cout << "measurementStartTime: "
              << obj->measurementStartTime.year << "-"
              << obj->measurementStartTime.month << "-"
              << obj->measurementStartTime.day << " "
              << obj->measurementStartTime.dayOfWeek << " "
              << obj->measurementStartTime.hour << ":"
              << obj->measurementStartTime.minute << ":"
              << obj->measurementStartTime.second << "."
              << obj->measurementStartTime.milliseconds
              << std::endl;
    std::cout << "lastObjectTime: "
              << obj->lastObjectTime.year << "-"
              << obj->lastObjectTime.month << "-"
              << obj->lastObjectTime.day << " "
              << obj->lastObjectTime.dayOfWeek << " "
              << obj->lastObjectTime.hour << ":"
              << obj->lastObjectTime.minute << ":"
              << obj->lastObjectTime.second << "."
              << obj->lastObjectTime.milliseconds
              << std::endl;
    std::cout << std::endl;
}

// UNKNOWN = 0

// CAN_MESSAGE = 1
void show(Vector::BLF::CanMessage * obj)
{
    std::cout << "CanMessage:"
              << " ch=" << obj->channel
              << " flags=" << static_cast<uint16_t>(obj->flags)
              << " dlc=" << static_cast<uint16_t>(obj->dlc)
              << " id=0x" << std::hex << obj->id
              << " data=";
    for (uint8_t i = 0; (i < obj->dlc) && (i < 8); ++i) {
        std::cout << std::hex;
        if (obj->data[i] <= 0xf) {
            std::cout << '0';
        }
        std::cout << static_cast<uint16_t>(obj->data[i]);
        std::cout << " ";
    }
    std::cout << std::endl;
}

// CAN_ERROR = 2
void show(Vector::BLF::CanErrorFrame * obj)
{
    std::cout << "CanErrorFrame:";
    std::cout << " ch=" << std::dec << obj->channel;
    std::cout << " len=" << std::dec << obj->length;
    std::cout << std::endl;
}

// CAN_OVERLOAD = 3
void show(Vector::BLF::CanOverloadFrame * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo CanOverloadFrame
}

// CAN_STATISTIC = 4
void show(Vector::BLF::CanDriverStatistic * obj)
{
    std::cout << "CanDriverStatistic:";
    std::cout << " ch=" << std::dec << obj->channel;
    std::cout << " busLoad=" << std::dec << obj->busLoad;
    std::cout << " stdDtFrm=" << std::dec << obj->standardDataFrames;
    std::cout << " extDtFrm=" << std::dec << obj->extendedDataFrames;
    std::cout << " stdRmtFrm=" << std::dec << obj->standardRemoteFrames;
    std::cout << " extRmtFrm=" << std::dec << obj->extendedRemoteFrames;
    std::cout << " errFrm=" << std::dec << obj->errorFrames;
    std::cout << " ovrldFrm=" << std::dec << obj->overloadFrames;
    std::cout << std::endl;
}

// APP_TRIGGER = 5
void show(Vector::BLF::AppTrigger * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo AppTrigger
}

// ENV_INTEGER = 6
// ENV_DOUBLE = 7
// ENV_STRING = 8
// ENV_DATA = 9
void show(Vector::BLF::EnvironmentVariable * environmentVariable)
{
    std::cout << "EnvironmentVariable:";
    std::cout << " name=" << environmentVariable->name;
    switch (environmentVariable->objectType) {
    case Vector::BLF::ObjectType::ENV_INTEGER:
        std::cout << " value=" << std::dec << static_cast<int>(*environmentVariable->data.data());
        std::cout << " type=Integer";
        break;
    case Vector::BLF::ObjectType::ENV_DOUBLE:
        std::cout << " value=" << std::fixed << static_cast<double>(*environmentVariable->data.data());
        std::cout << " type=Double";
        break;
    case Vector::BLF::ObjectType::ENV_STRING:
        std::cout << " type=String";
        // @todo ENV_STRING
        break;
    case Vector::BLF::ObjectType::ENV_DATA:
        std::cout << " type=Data";
        // @todo ENV_DATA
        break;
    default:
        std::cout << " type=Unknown";
        break;
    }
    std::cout << std::endl;
}

// LOG_CONTAINER = 10
void show(Vector::BLF::LogContainer * logContainer)
{
    std::cout << "signature: 0x" << std::hex << logContainer->signature << std::endl;
    std::cout << "headerSize: 0x" << std::hex << logContainer->headerSize << std::endl;
    std::cout << "headerVersion: 0x" << std::hex << logContainer->headerVersion << std::endl;
    std::cout << "objectSize: 0x" << std::hex << logContainer->objectSize << std::endl;
    std::cout << "objectType: " << std::dec << static_cast<int>(logContainer->objectType) << std::endl;

    std::cout << "uncompressedFileSize: " << std::dec << logContainer->uncompressedFileSize << std::endl;
    std::cout << std::endl;
}

// LIN_MESSAGE = 11
void show(Vector::BLF::LinMessage * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinMessage
}

// LIN_CRC_ERROR = 12
void show(Vector::BLF::LinCrcError * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinCrcError
}

// LIN_DLC_INFO = 13
void show(Vector::BLF::LinDlcInfo * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinDlcInfo
}

// LIN_RCV_ERROR =  14
void show(Vector::BLF::LinReceiveError * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinReceiveError
}

// LIN_SND_ERROR = 15
void show(Vector::BLF::LinSendError * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinSendError
}

// LIN_SLV_TIMEOUT = 16
void show(Vector::BLF::LinSlaveTimeout * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinSlaveTimeout
}

// LIN_SCHED_MODCH = 17
void show(Vector::BLF::LinSchedulerModeChange * linSchedulerModeChange)
{
    std::cout << "LinSchedulerModeChange:";
    std::cout << " ch=" << std::dec << linSchedulerModeChange->channel;
    std::cout << " old=" << std::dec << static_cast<uint16_t>(linSchedulerModeChange->oldMode);
    std::cout << " new=" << std::dec << static_cast<uint16_t>(linSchedulerModeChange->newMode);
    std::cout << std::endl;
}

// LIN_SYN_ERROR = 18
void show(Vector::BLF::LinSyncError * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinSyncError
}

// LIN_BAUDRATE = 19
void show(Vector::BLF::LinBaudrateEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinBaudrateEvent
}

// LIN_SLEEP = 20
void show(Vector::BLF::LinSleepModeEvent * linSleepModeEvent)
{
    std::cout << "LinSleepModeEvent:";
    std::cout << " ch=" << std::dec << linSleepModeEvent->channel;
    std::cout << " rsn=" << std::dec << static_cast<uint16_t>(linSleepModeEvent->reason);
    std::cout << " flags=0x" << std::hex << static_cast<uint16_t>(linSleepModeEvent->flags);
    std::cout << std::endl;
}

// LIN_WAKEUP = 21
void show(Vector::BLF::LinWakeupEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinWakeupEvent
}

// MOST_SPY = 22
void show(Vector::BLF::MostSpy * mostSpy)
{
    std::cout << "MostSpy:";
    std::cout << " ch=" << std::dec << mostSpy->channel;
    std::cout << " dir=" << std::dec << static_cast<uint16_t>(mostSpy->dir);
    std::cout << " sourceAdr=" << std::dec << mostSpy->sourceAdr;
    std::cout << " destAdr=" << std::dec << mostSpy->destAdr;
    std::cout << " msg=" << std::hex;
    for (uint8_t i = 0; i < 17; ++i) {
        if (mostSpy->msg[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << static_cast<uint16_t>(mostSpy->msg[i]);
    }
    std::cout << " rTyp=0x" << std::hex << mostSpy->rTyp;
    std::cout << " rTypAdr=0x" << std::hex << static_cast<uint16_t>(mostSpy->rTypAdr);
    std::cout << " state=0x" << std::hex << static_cast<uint16_t>(mostSpy->state);
    std::cout << " ackNack=0x" << std::hex << static_cast<uint16_t>(mostSpy->ackNack);
    std::cout << " crc=0x" << std::hex << mostSpy->crc;
    std::cout << std::endl;
}

// MOST_CTRL = 23
void show(Vector::BLF::MostCtrl * mostCtrl)
{
    std::cout << "MostCtrl:";
    std::cout << " ch=" << std::dec << mostCtrl->channel;
    std::cout << " dir=" << std::dec << static_cast<uint16_t>(mostCtrl->dir);
    std::cout << " sourceAdr=" << std::dec << mostCtrl->sourceAdr;
    std::cout << " destAdr=" << std::dec << mostCtrl->destAdr;
    std::cout << " msg=" << std::hex;
    for (uint8_t i = 0; i < 17; ++i) {
        if (mostCtrl->msg[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << static_cast<uint16_t>(mostCtrl->msg[i]);
    }
    std::cout << " rTyp=0x" << std::hex << mostCtrl->rTyp;
    std::cout << " rTypAdr=0x" << std::hex << static_cast<uint16_t>(mostCtrl->rTypAdr);
    std::cout << " state=0x" << std::hex << static_cast<uint16_t>(mostCtrl->state);
    std::cout << " ackNack=0x" << std::hex << static_cast<uint16_t>(mostCtrl->ackNack);
    std::cout << std::endl;
}

// MOST_LIGHTLOCK = 24
void show(Vector::BLF::MostLightLock * mostLightLock)
{
    std::cout << "MostLightLock:";
    std::cout << " ch=" << std::dec << mostLightLock->channel;
    std::cout << " state=0x" << std::hex << mostLightLock->state;
    std::cout << std::endl;
}

// MOST_STATISTIC = 25
void show(Vector::BLF::MostStatistic * mostStatistic)
{
    std::cout << "MostStatistic:";
    std::cout << " ch=" << std::dec << mostStatistic->channel;
    std::cout << " pktCnt=" << std::dec << mostStatistic->pktCnt;
    std::cout << " frmCnt=" << std::dec << mostStatistic->frmCnt;
    std::cout << " lightCnt=" << std::dec << mostStatistic->lightCnt;
    std::cout << " bufferLevel=" << std::dec << mostStatistic->bufferLevel;
    std::cout << std::endl;
}

// Reserved26 = 26
// Reserved27 = 27
// Reserved28 = 28

// FLEXRAY_DATA = 29
void show(Vector::BLF::FlexRayData * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRayData
}

// FLEXRAY_SYNC = 30
void show(Vector::BLF::FlexRaySync * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRaySync
}

// CAN_DRIVER_ERROR = 31
void show(Vector::BLF::CanDriverError * canDriverError)
{
    std::cout << "CanDriverError:";
    std::cout << " ch=" << std::dec << canDriverError->channel;
    std::cout << " txErr=" << std::dec << static_cast<uint16_t>(canDriverError->txErrors);
    std::cout << " rxErr=" << std::dec << static_cast<uint16_t>(canDriverError->rxErrors);
    std::cout << " errCode=" << std::dec << canDriverError->errorCode;
    std::cout << std::endl;
}

// MOST_PKT = 32
void show(Vector::BLF::MostPkt * mostPkt)
{
    std::cout << "MostPkt:";
    std::cout << " ch=" << std::dec << mostPkt->channel;
    std::cout << " dir=" << std::dec << static_cast<uint16_t>(mostPkt->dir);
    std::cout << " sa=" << std::dec << mostPkt->sourceAdr;
    std::cout << " da=" << std::dec << mostPkt->destAdr;
    std::cout << " arb=" << std::dec << static_cast<uint16_t>(mostPkt->arbitration);
    std::cout << " tr=" << std::dec << static_cast<uint16_t>(mostPkt->timeRes);
    std::cout << " qtf=" << std::dec << static_cast<uint16_t>(mostPkt->quadsToFollow);
    std::cout << " crc=" << std::dec << mostPkt->crc;
    std::cout << " prio=" << std::dec << static_cast<uint16_t>(mostPkt->priority);
    std::cout << " tt=" << std::dec << static_cast<uint16_t>(mostPkt->transferType);
    std::cout << " st=0x" << std::hex << static_cast<uint16_t>(mostPkt->state);
    std::cout << " len=" << std::dec << mostPkt->pktDataLength;
    std::cout << " data=" << std::hex;
    for (uint16_t i = 0; i < mostPkt->pktDataLength; ++i) {
        if (mostPkt->pktData[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << static_cast<uint16_t>(mostPkt->pktData[i]);
    }
    std::cout << std::endl;
}

// MOST_PKT2 = 33
void show(Vector::BLF::MostPkt2 * mostPkt2)
{
    std::cout << "MostPkt2:";
    std::cout << " ch=" << std::dec << mostPkt2->channel;
    std::cout << " dir=" << std::dec << static_cast<uint16_t>(mostPkt2->dir);
    std::cout << " sa=" << std::dec << mostPkt2->sourceAdr;
    std::cout << " da=" << std::dec << mostPkt2->destAdr;
    std::cout << " arb=" << std::dec << static_cast<uint16_t>(mostPkt2->arbitration);
    std::cout << " tr=" << std::dec << static_cast<uint16_t>(mostPkt2->timeRes);
    std::cout << " qtf=" << std::dec << static_cast<uint16_t>(mostPkt2->quadsToFollow);
    std::cout << " crc=" << std::dec << mostPkt2->crc;
    std::cout << " prio=" << std::dec << static_cast<uint16_t>(mostPkt2->priority);
    std::cout << " tt=" << std::dec << static_cast<uint16_t>(mostPkt2->transferType);
    std::cout << " st=0x" << std::hex << static_cast<uint16_t>(mostPkt2->state);
    std::cout << " len=" << std::dec << mostPkt2->pktDataLength;
    std::cout << " data=" << std::hex;
    for (uint16_t i = 0; i < mostPkt2->pktDataLength; ++i) {
        if (mostPkt2->pktData[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << static_cast<uint16_t>(mostPkt2->pktData[i]);
    }
    std::cout << std::endl;
}

// MOST_HWMODE = 34
void show(Vector::BLF::MostHwMode * mostHwMode)
{
    std::cout << "MostHwMode:";
    std::cout << " ch=" << std::dec << mostHwMode->channel;
    std::cout << " hwMode=0x" << std::hex << mostHwMode->hwMode;
    std::cout << " hwModeMask=0x" << std::hex << mostHwMode->hwModeMask;
    std::cout << std::endl;
}

// MOST_REG = 35
void show(Vector::BLF::MostReg * mostReg)
{
    std::cout << "MostReg:";
    std::cout << " ch=" << std::dec << mostReg->channel;
    std::cout << " subType=" << std::dec << static_cast<uint16_t>(mostReg->subType);
    std::cout << " handle=" << std::dec << mostReg->handle;
    std::cout << " offset=" << std::dec << mostReg->offset;
    std::cout << " chip=" << std::dec << mostReg->chip;
    std::cout << " regDataLen=" << std::dec << mostReg->regDataLen;
    std::cout << " regData=0x" << std::hex;
    for (uint16_t i = 0; i < mostReg->regDataLen; ++i) {
        if (mostReg->regData[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << static_cast<uint16_t>(mostReg->regData[i]);
    }
    std::cout << std::endl;
}

// MOST_GENREG = 36
void show(Vector::BLF::MostGenReg * mostGenReg)
{
    std::cout << "MostGenReg:";
    std::cout << " ch=" << std::dec << mostGenReg->channel;
    std::cout << " subType=" << std::dec << static_cast<uint16_t>(mostGenReg->subType);
    std::cout << " handle=" << std::dec << mostGenReg->handle;
    std::cout << " regId=0x" << std::hex << mostGenReg->regId;
    std::cout << " regVal=0x" << std::hex << mostGenReg->regValue;
    std::cout << std::endl;
}

// MOST_NETSTATE = 37
void show(Vector::BLF::MostNetState * mostNetState)
{
    std::cout << "MostNetState:";
    std::cout << " ch=" << std::dec << mostNetState->channel;
    std::cout << " stNew=" << std::dec << mostNetState->stateNew;
    std::cout << " stOld=" << std::dec << mostNetState->stateOld;
    std::cout << std::endl;
}

// MOST_DATALOST = 38
void show(Vector::BLF::MostDataLost * mostDataLost)
{
    std::cout << "MostDataLost:";
    std::cout << " ch=" << std::dec << mostDataLost->channel;
    std::cout << " info=0x" << std::hex << mostDataLost->info;
    std::cout << " lostMsgsCtrl=" << std::dec << mostDataLost->lostMsgsCtrl;
    std::cout << " lostMsgsAsync=" << std::dec << mostDataLost->lostMsgsAsync;
    std::cout << " lastGoodTimeStampNs=" << std::dec << mostDataLost->lastGoodTimeStampNs;
    std::cout << " nextGoodTimeStampNs=" << std::dec << mostDataLost->nextGoodTimeStampNs;
    std::cout << std::endl;
}

// MOST_TRIGGER = 39
void show(Vector::BLF::MostTrigger * mostTrigger)
{
    std::cout << "MostTrigger:";
    std::cout << " ch=" << std::dec << mostTrigger->channel;
    std::cout << " mode=" << std::dec << mostTrigger->mode;
    std::cout << " hw=" << std::dec << mostTrigger->hw;
    std::cout << " previousTriggerValue=" << std::dec << mostTrigger->previousTriggerValue;
    std::cout << " currentTriggerValue=" << std::dec << mostTrigger->currentTriggerValue;
    std::cout << std::endl;
}

// FLEXRAY_CYCLE = 40
void show(Vector::BLF::FlexRayV6StartCycleEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRayV6StartCycleEvent
}

// FLEXRAY_MESSAGE = 41
void show(Vector::BLF::FlexRayV6Message * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRayV6Message
}

// LIN_CHECKSUM_INFO = 42
void show(Vector::BLF::LinChecksumInfo * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinChecksumInfo
}

// LIN_SPIKE_EVENT = 43
void show(Vector::BLF::LinSpikeEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinSpikeEvent
}

// CAN_DRIVER_SYNC = 44
void show(Vector::BLF::CanDriverHwSync * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo CanDriverHwSync
}

// FLEXRAY_STATUS = 45
void show(Vector::BLF::FlexRayStatusEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRayStatusEvent
}

// GPS_EVENT = 46
void show(Vector::BLF::GpsEvent * gpsEvent)
{
    std::cout << "GpsEvent:";
    std::cout << " flags=0x" << std::hex << gpsEvent->flags;
    std::cout << " ch=" << std::dec << gpsEvent->channel;
    std::cout << " lon=" << std::fixed << gpsEvent->longitude;
    std::cout << " lat=" << std::fixed << gpsEvent->latitude;
    std::cout << " alt=" << std::fixed << gpsEvent->altitude;
    std::cout << " spd=" << std::fixed << gpsEvent->speed;
    std::cout << " crs=" << std::fixed << gpsEvent->course;
    std::cout << std::endl;
}

// FR_ERROR = 47
void show(Vector::BLF::FlexRayVFrError * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRayVFrError
}

// FR_STATUS = 48
void show(Vector::BLF::FlexRayVFrStatus * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRayVFrStatus
}

// FR_STARTCYCLE = 49
void show(Vector::BLF::FlexRayVFrStartCycle * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRayVFrStartCycle
}

// FR_RCVMESSAGE = 50
void show(Vector::BLF::FlexRayVFrReceiveMsg * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRayVFrReceiveMsg
}

// REALTIMECLOCK = 51
void show(Vector::BLF::RealtimeClock * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo RealtimeClock
}

// Reserved52 = 52
// Reserved52 = 53

// LIN_STATISTIC = 54
void show(Vector::BLF::LinStatisticEvent * linStatisticEvent)
{
    std::cout << "LinStatisticEvent:";
    std::cout << " ch=" << std::dec << linStatisticEvent->channel;
    std::cout << " busload=" << std::fixed << linStatisticEvent->busLoad;
    std::cout << " burstsTotal=" << std::dec << linStatisticEvent->burstsTotal;
    std::cout << " burstsOverrun=" << std::dec << linStatisticEvent->burstsOverrun;
    std::cout << " framesSent=" << std::dec << linStatisticEvent->framesSent;
    std::cout << " framesRecv=" << std::dec << linStatisticEvent->framesReceived;
    std::cout << " framesUnansw=" << std::dec << linStatisticEvent->framesUnanswered;
    std::cout << std::endl;
}

// J1708_MESSAGE = 55
// J1708_VIRTUAL_MSG = 56
void show(Vector::BLF::J1708Message * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo J1708Message
}

// LIN_MESSAGE2 = 57
void show(Vector::BLF::LinMessage2 * linMessage2)
{
    std::cout << "LinMessage2:";
    std::cout << " data=0x";
    for (uint8_t i = 0; i < linMessage2->dlc; ++i) {
        if (linMessage2->data[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << std::hex << static_cast<uint16_t>(linMessage2->data[i]);
    }
    std::cout << " crc=0x" << std::hex << linMessage2->crc;
    std::cout << " dir=" << std::dec << static_cast<uint16_t>(linMessage2->dir);
    std::cout << " sim=" << std::dec << static_cast<uint16_t>(linMessage2->simulated);
    std::cout << " etf=" << std::dec << static_cast<uint16_t>(linMessage2->isEtf);
    std::cout << " etfAI=" << std::dec << static_cast<uint16_t>(linMessage2->etfAssocIndex);
    std::cout << " etfAEI=" << std::dec << static_cast<uint16_t>(linMessage2->etfAssocEtfId);
    std::cout << " fsmId=" << std::dec << static_cast<uint16_t>(linMessage2->fsmId);
    std::cout << " fsmState=" << std::dec << static_cast<uint16_t>(linMessage2->fsmState);
    std::cout << " respBaudrate=" << std::dec << linMessage2->respBaudrate;
    std::cout << " exactHeaderBaudrate=" << std::dec << linMessage2->exactHeaderBaudrate;
    std::cout << " earlyStopbitOffset=" << std::dec << linMessage2->earlyStopbitOffset;
    std::cout << " earlyStopbitOffsetResponse=" << std::dec << linMessage2->earlyStopbitOffsetResponse;
    std::cout << std::endl;
}

// LIN_SND_ERROR2 = 58
void show(Vector::BLF::LinSendError2 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinSendError2
}

// LIN_SYN_ERROR2 = 59
void show(Vector::BLF::LinSyncError2 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinSyncError2
}

// LIN_CRC_ERROR2 = 60
void show(Vector::BLF::LinCrcError2 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinCrcError2
}

// LIN_RCV_ERROR2 = 61
void show(Vector::BLF::LinReceiveError2 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinReceiveError2
}

// LIN_WAKEUP2 = 62
void show(Vector::BLF::LinWakeupEvent2 * linWakeupEvent2)
{
    std::cout << "LinWakeupEvent2:";
    std::cout << " len=" << std::dec << static_cast<uint16_t>(linWakeupEvent2->lengthInfo);
    std::cout << " sig=" << std::dec << static_cast<uint16_t>(linWakeupEvent2->signal);
    std::cout << " ext=" << std::dec << static_cast<uint16_t>(linWakeupEvent2->external);
    std::cout << std::endl;
}

// LIN_SPIKE_EVENT2 = 63
void show(Vector::BLF::LinSpikeEvent2 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinSpikeEvent2
}

// LIN_LONG_DOM_SIG = 64
void show(Vector::BLF::LinLongDomSignalEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinLongDomSignalEvent
}

// APP_TEXT = 65
void show(Vector::BLF::AppText * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo AppText
}

// FR_RCVMESSAGE_EX = 66
void show(Vector::BLF::FlexRayVFrReceiveMsgEx * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo FlexRayVFrReceiveMsgEx
}

// MOST_STATISTICEX = 67
void show(Vector::BLF::MostStatisticEx * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo MostStatisticEx
}

// MOST_TXLIGHT = 68
void show(Vector::BLF::MostTxLight * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo MostTxLight
}

// MOST_ALLOCTAB = 69
void show(Vector::BLF::MostAllocTab * mostAllocTab)
{
    std::cout << "MostAllocTab:";
    std::cout << " ch=" << std::dec << mostAllocTab->channel;
    std::cout << " len=0x" << std::hex << mostAllocTab->length;
    std::cout << " allocTab=0x" << std::hex;
    for (uint16_t i = 0; i < mostAllocTab->length; ++i) {
        if (mostAllocTab->tableData[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << static_cast<uint16_t>(mostAllocTab->tableData[i]);
    }
    std::cout << std::endl;
}

// MOST_STRESS = 70
void show(Vector::BLF::MostStress * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo MostStress
}

// ETHERNET_FRAME = 71
void show(Vector::BLF::EthernetFrame * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo EthernetFrame
}

// SYS_VARIABLE = 72
void show(Vector::BLF::SystemVariable * systemVariable)
{
    std::cout << "SystemVariable:";
    std::cout << " name=" << systemVariable->name;
    switch (systemVariable->type) {
    case Vector::BLF::SystemVariable::Type::Double:
        std::cout << " value=" << std::fixed << static_cast<double>(*systemVariable->data.data());
        std::cout << " type=Double";
        break;
    case Vector::BLF::SystemVariable::Type::Long:
        std::cout << " value=" << std::dec << static_cast<long>(*systemVariable->data.data());
        std::cout << " type=Long";
        break;
    case Vector::BLF::SystemVariable::Type::String:
        std::cout << " type=String";
        // @todo String
        break;
    case Vector::BLF::SystemVariable::Type::DoubleArray:
        std::cout << " type=DoubleArray";
        // @todo DoubleArray
        break;
    case Vector::BLF::SystemVariable::Type::LongArray:
        std::cout << " type=LongArray";
        // @todo LongArray
        break;
    case Vector::BLF::SystemVariable::Type::LongLong:
        std::cout << " type=LongLong";
        // @todo LongLong
        break;
    case Vector::BLF::SystemVariable::Type::ByteArray:
        std::cout << " type=ByteArray";
        // @todo ByteArray
        break;
    }
    std::cout << std::endl;
}

// CAN_ERROR_EXT = 73
void show(Vector::BLF::CanErrorFrameExt * canErrorFrameExt)
{
    std::cout << "CanErrorFrameExt:";
    std::cout << " ch=" << std::dec << canErrorFrameExt->channel;
    std::cout << " len=" << std::dec << canErrorFrameExt->length;
    std::cout << " flags=0x" << std::hex << canErrorFrameExt->flags;
    std::cout << " ecc=0x" << std::hex << static_cast<uint16_t>(canErrorFrameExt->ecc);
    std::cout << " pos=" << std::dec << static_cast<uint16_t>(canErrorFrameExt->position);
    std::cout << " dlc=" << std::dec << static_cast<uint16_t>(canErrorFrameExt->dlc);
    std::cout << " ns=" << std::dec << canErrorFrameExt->frameLengthInNs;
    std::cout << " id=0x" << std::hex << canErrorFrameExt->id;
    std::cout << " flagsExt=0x" << std::hex << canErrorFrameExt->flagsExt;
    std::cout << " msg=" << std::hex;
    for (uint8_t i = 0; i < canErrorFrameExt->dlc; ++i) {
        if (canErrorFrameExt->data[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << static_cast<uint16_t>(canErrorFrameExt->data[i]);
    }
    std::cout << std::endl;
}

// CAN_DRIVER_ERROR_EXT = 74
void show(Vector::BLF::CanDriverErrorExt * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo CanDriverErrorExt
}

// LIN_LONG_DOM_SIG2 = 75
void show(Vector::BLF::LinLongDomSignalEvent2 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinLongDomSignalEvent2
}

// MOST_150_MESSAGE = 76
void show(Vector::BLF::Most150Message * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo Most150Message
}

// MOST_150_PKT = 77
void show(Vector::BLF::Most150Pkt * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo Most150Pkt
}

// MOST_ETHERNET_PKT = 78
void show(Vector::BLF::MostEthernetPkt * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo MostEthernetPkt
}

// MOST_150_MESSAGE_FRAGMENT = 79
void show(Vector::BLF::Most150MessageFragment * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo Most150MessageFragment
}

// MOST_150_PKT_FRAGMENT = 80
void show(Vector::BLF::Most150PktFragment * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo Most150PktFragment
}

// MOST_ETHERNET_PKT_FRAGMENT = 81
void show(Vector::BLF::MostEthernetPktFragment * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo MostEthernetPktFragment
}

// MOST_SYSTEM_EVENT = 82
void show(Vector::BLF::MostSystemEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo MostSystemEvent
}

// MOST_150_ALLOCTAB = 83
void show(Vector::BLF::Most150AllocTab * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo Most150AllocTab
}

// MOST_50_MESSAGE = 84
void show(Vector::BLF::Most50Message * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo Most50Message
}

// MOST_50_PKT = 85
void show(Vector::BLF::Most50Pkt * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo Most50Pkt
}

// CAN_MESSAGE2 = 86
void show(Vector::BLF::CanMessage2 * obj)
{
    std::cout << "CanMessage2:"
              << " ch=" << obj->channel
              << " flags=" << static_cast<uint16_t>(obj->flags)
              << " dlc=" << static_cast<uint16_t>(obj->dlc)
              << " id=0x" << std::hex << obj->id
              << " frameLength=" << std::dec << obj->frameLength << "ms"
              << " bitCount=" << static_cast<uint16_t>(obj->bitCount)
              << " data=";
    for (uint8_t i = 0; (i < obj->dlc) && (i < 8); ++i) {
        std::cout << std::hex;
        if (obj->data[i] <= 0xf) {
            std::cout << '0';
        }
        std::cout << static_cast<uint16_t>(obj->data[i]);
        std::cout << " ";
    }
    std::cout << std::endl;
}

// LIN_UNEXPECTED_WAKEUP = 87
void show(Vector::BLF::LinUnexpectedWakeup * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinUnexpectedWakeup
}

// LIN_SHORT_OR_SLOW_RESPONSE = 88
void show(Vector::BLF::LinShortOrSlowResponse * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinShortOrSlowResponse
}

// LIN_DISTURBANCE_EVENT = 89
void show(Vector::BLF::LinDisturbanceEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinDisturbanceEvent
}

// SERIAL_EVENT = 90
void show(Vector::BLF::SerialEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo SerialEvent
}

// OVERRUN_ERROR = 91
void show(Vector::BLF::DriverOverrun * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo DriverOverrun
}

// EVENT_COMMENT = 92
void show(Vector::BLF::EventComment * eventComment)
{
    std::cout << "EventComment:";
    std::cout << " type=" << std::dec << eventComment->commentedEventType;
    std::cout << " text=" << eventComment->text;
    std::cout << std::endl;
}

// WLAN_FRAME = 93
void show(Vector::BLF::WlanFrame * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo WlanFrame
}

// WLAN_STATISTIC = 94
void show(Vector::BLF::WlanStatistic * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo WlanStatistic
}

// MOST_ECL = 95
void show(Vector::BLF::MostEcl * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo MostEcl
}

// GLOBAL_MARKER = 96
void show(Vector::BLF::GlobalMarker * globalMarker)
{
    std::cout << "GlobalMarker:";
    std::cout << " type=" << std::dec << globalMarker->commentedEventType;
    std::cout << " fgcol=0x" << std::hex << globalMarker->foregroundColor;
    std::cout << " bgcol=0x" << std::hex << globalMarker->backgroundColor;
    std::cout << " grpNam=" << globalMarker->groupName;
    std::cout << " mrkNam=" << globalMarker->markerName;
    std::cout << " descr=" << globalMarker->description;
    std::cout << std::endl;
}

// AFDX_FRAME = 97
void show(Vector::BLF::AfdxFrame * afdxFrame)
{
    std::cout << "AfdxFrame:";
    std::cout << " SA=";
    for (uint32_t i = 0; i < 6; ++i) {
        if (afdxFrame->sourceAddress[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << std::hex << static_cast<uint16_t>(afdxFrame->sourceAddress[i]);
        if (i < 5) {
            std::cout << ":";
        }
    }
    std::cout << " ch=" << std::dec << afdxFrame->channel;
    std::cout << " DA=";
    for (uint32_t i = 0; i < 6; ++i) {
        if (afdxFrame->destinationAddress[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << std::hex << static_cast<uint16_t>(afdxFrame->destinationAddress[i]);
        if (i < 5) {
            std::cout << ":";
        }
    }
    std::cout << " dir=" << std::dec << static_cast<uint16_t>(afdxFrame->dir);
    std::cout << " type=0x" << std::hex << afdxFrame->type;
    std::cout << " tpid=" << std::dec << afdxFrame->tpid;
    std::cout << " tci=" << std::dec << afdxFrame->tci;
    std::cout << " ethChan=" << std::dec << static_cast<uint16_t>(afdxFrame->ethChannel);
    std::cout << " flags=0x" << std::hex << afdxFrame->afdxFlags;
    std::cout << " bagUsec=" << std::dec << afdxFrame->bagUsec;
    std::cout << " len=0x" << std::hex << afdxFrame->payLoadLength;
    // payLoad
    std::cout << std::endl;
}

// AFDX_STATISTIC = 98
void show(Vector::BLF::AfdxStatistic * afdxStatistic)
{
    std::cout << "AfdxStatistic:";
    std::cout << " ch=" << std::dec << afdxStatistic->channel;
    std::cout << " flags=0x" << std::hex << static_cast<uint16_t>(afdxStatistic->flags);
    std::cout << " rxPktCnt=" << std::dec << afdxStatistic->rxPacketCount;
    std::cout << " rxBytCnt=" << std::dec << afdxStatistic->rxByteCount;
    std::cout << " txPktCnt=" << std::dec << afdxStatistic->txPacketCount;
    std::cout << " txBytCnt=" << std::dec << afdxStatistic->txByteCount;
    std::cout << " colCnt=" << std::dec << afdxStatistic->collisionCount;
    std::cout << " errCnt=" << std::dec << afdxStatistic->errorCount;
    std::cout << " drpRdnPktCnt=" << std::dec << afdxStatistic->statDroppedRedundantPacketCount;
    std::cout << " rdnErrPktCnt=" << std::dec << afdxStatistic->statRedundantErrorPacketCount;
    std::cout << " intErrPktCnt=" << std::dec << afdxStatistic->statIntegrityErrorPacketCount;
    std::cout << " avrfPerMsec=" << std::dec << afdxStatistic->statAvrgPeriodMsec;
    std::cout << " avrfJitMsec=" << std::dec << afdxStatistic->statAvrgJitterMysec;
    std::cout << " vlid=" << std::dec << afdxStatistic->vlid;
    std::cout << " dur=" << std::dec << afdxStatistic->statDuration;
    std::cout << std::endl;
}

// KLINE_STATUSEVENT = 99
void show(Vector::BLF::KLineStatusEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo KLineStatusEvent
}

// CAN_FD_MESSAGE = 100
void show(Vector::BLF::CanFdMessage * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo CanFdMessage
}

// CAN_FD_MESSAGE_64 = 101
void show(Vector::BLF::CanFdMessage64 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo CanFdMessage64
}

// ETHERNET_RX_ERROR = 102
void show(Vector::BLF::EthernetRxError * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo EthernetRxError
}

// ETHERNET_STATUS = 103
void show(Vector::BLF::EthernetStatus * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo EthernetStatus
}

// CAN_FD_ERROR_64 = 104
void show(Vector::BLF::CanFdErrorFrame64 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo CanFdErrorFrame64
}

// LIN_SHORT_OR_SLOW_RESPONSE2 = 105
void show(Vector::BLF::LinShortOrSlowResponse2 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo LinShortOrSlowResponse2
}

// AFDX_STATUS = 106
void show(Vector::BLF::AfdxStatus * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo AfdxStatus
}

// AFDX_BUS_STATISTIC = 107
void show(Vector::BLF::AfdxBusStatistic * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo AfdxBusStatistic
}

// Reserved108 = 108

// AFDX_ERROR_EVENT = 109
void show(Vector::BLF::AfdxErrorEvent * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo AfdxErrorEvent
}

// A429_ERROR = 110
void show(Vector::BLF::A429Error * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo A429Error
}

// A429_STATUS = 111
void show(Vector::BLF::A429Status * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo A429Status
}

// A429_BUS_STATISTIC = 112
void show(Vector::BLF::A429BusStatistic * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo A429BusStatistic
}

// A429_MESSAGE = 113
void show(Vector::BLF::A429Message * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo A429Message
}

// ETHERNET_STATISTIC = 114
void show(Vector::BLF::EthernetStatistic * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo EthernetStatistic
}

// Unknown115 = 115
void show(Vector::BLF::Unknown115 * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo TestStructure
}

// Reserved116 = 116
// Reserved117 = 117

// TEST_STRUCTURE = 118
void show(Vector::BLF::TestStructure * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo TestStructure
}

// DIAG_REQUEST_INTERPRETATION = 119
void show(Vector::BLF::DiagRequestInterpretation * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo DiagRequestInterpretation
}

// ETHERNET_FRAME_EX = 120
void show(Vector::BLF::EthernetFrameEx * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo EthernetFrameEx
}

// ETHERNET_FRAME_FORWARDED = 121
void show(Vector::BLF::EthernetFrameForwarded * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo EthernetFrameForwarded
}

// ETHERNET_ERROR_EX = 122
void show(Vector::BLF::EthernetErrorEx * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo EthernetErrorEx
}

// ETHERNET_ERROR_FORWARDED = 123
void show(Vector::BLF::EthernetErrorForwarded * obj)
{
    std::cout << "No parser support for ObjectType " << std::dec << static_cast<uint16_t>(obj->objectType) << std::endl;
    // @todo EthernetErrorForwarded
}

int main(int argc, char * argv[])
{
    if (argc != 2) {
        std::cout << "Parser <filename.blf>" << std::endl;
        return -1;
    }

    Vector::BLF::File file;
    file.open(argv[1]);

    show(&file.fileStatistics);

    while (!file.eof()) {
        Vector::BLF::ObjectHeaderBase * ohb = file.read();
        if (ohb == nullptr) {
            break;
        }

        /* ObjectHeader */
        Vector::BLF::ObjectHeader * oh = dynamic_cast<Vector::BLF::ObjectHeader *>(ohb);
        if (oh != nullptr) {
            std::cout << std::dec << oh->objectTimeStamp;
            switch (oh->objectFlags) {
            case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
                std::cout << "0 ms: ";
                break;
            case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
                std::cout << " ns: ";
                break;
            }
        }

        /* ObjectHeader2 */
        Vector::BLF::ObjectHeader2 * oh2 = dynamic_cast<Vector::BLF::ObjectHeader2 *>(ohb);
        if (oh2 != nullptr) {
            std::cout << std::dec << oh2->objectTimeStamp;
            switch (oh2->objectFlags) {
            case Vector::BLF::ObjectHeader2::ObjectFlags::TimeTenMics:
                std::cout << "0 ms: ";
                break;
            case Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans:
                std::cout << " ns: ";
                break;
            }
        }

        /* Object */
        switch (ohb->objectType) {
        case Vector::BLF::ObjectType::UNKNOWN:
            /* do nothing */
            break;

        case Vector::BLF::ObjectType::CAN_MESSAGE:
            show(reinterpret_cast<Vector::BLF::CanMessage *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_ERROR:
            show(reinterpret_cast<Vector::BLF::CanErrorFrame *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_OVERLOAD:
            show(reinterpret_cast<Vector::BLF::CanOverloadFrame *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_STATISTIC:
            show(reinterpret_cast<Vector::BLF::CanDriverStatistic *>(ohb));
            break;

        case Vector::BLF::ObjectType::APP_TRIGGER:
            show(reinterpret_cast<Vector::BLF::AppTrigger *>(ohb));
            break;

        case Vector::BLF::ObjectType::ENV_INTEGER:
        case Vector::BLF::ObjectType::ENV_DOUBLE:
        case Vector::BLF::ObjectType::ENV_STRING:
        case Vector::BLF::ObjectType::ENV_DATA:
            show(reinterpret_cast<Vector::BLF::EnvironmentVariable *>(ohb));
            break;

        case Vector::BLF::ObjectType::LOG_CONTAINER:
            show(reinterpret_cast<Vector::BLF::LogContainer *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_MESSAGE:
            show(reinterpret_cast<Vector::BLF::LinMessage *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_CRC_ERROR:
            show(reinterpret_cast<Vector::BLF::LinCrcError *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_DLC_INFO:
            show(reinterpret_cast<Vector::BLF::LinDlcInfo *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_RCV_ERROR:
            show(reinterpret_cast<Vector::BLF::LinReceiveError *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SND_ERROR:
            show(reinterpret_cast<Vector::BLF::LinSendError *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SLV_TIMEOUT:
            show(reinterpret_cast<Vector::BLF::LinSlaveTimeout *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SCHED_MODCH:
            show(reinterpret_cast<Vector::BLF::LinSchedulerModeChange *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SYN_ERROR:
            show(reinterpret_cast<Vector::BLF::LinSyncError *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_BAUDRATE:
            show(reinterpret_cast<Vector::BLF::LinBaudrateEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SLEEP:
            show(reinterpret_cast<Vector::BLF::LinSleepModeEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_WAKEUP:
            show(reinterpret_cast<Vector::BLF::LinWakeupEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_SPY:
            show(reinterpret_cast<Vector::BLF::MostSpy *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_CTRL:
            show(reinterpret_cast<Vector::BLF::MostCtrl *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_LIGHTLOCK:
            show(reinterpret_cast<Vector::BLF::MostLightLock *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_STATISTIC:
            show(reinterpret_cast<Vector::BLF::MostStatistic *>(ohb));
            break;

        case Vector::BLF::ObjectType::Reserved26:
        case Vector::BLF::ObjectType::Reserved27:
        case Vector::BLF::ObjectType::Reserved28:
            /* do nothing */
            break;

        case Vector::BLF::ObjectType::FLEXRAY_DATA:
            show(reinterpret_cast<Vector::BLF::FlexRayData *>(ohb));
            break;

        case Vector::BLF::ObjectType::FLEXRAY_SYNC:
            show(reinterpret_cast<Vector::BLF::FlexRaySync *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_DRIVER_ERROR:
            show(reinterpret_cast<Vector::BLF::CanDriverError *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_PKT:
            show(reinterpret_cast<Vector::BLF::MostPkt *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_PKT2:
            show(reinterpret_cast<Vector::BLF::MostPkt2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_HWMODE:
            show(reinterpret_cast<Vector::BLF::MostHwMode *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_REG:
            show(reinterpret_cast<Vector::BLF::MostReg *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_GENREG:
            show(reinterpret_cast<Vector::BLF::MostGenReg *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_NETSTATE:
            show(reinterpret_cast<Vector::BLF::MostNetState *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_DATALOST:
            show(reinterpret_cast<Vector::BLF::MostDataLost *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_TRIGGER:
            show(reinterpret_cast<Vector::BLF::MostTrigger *>(ohb));
            break;

        case Vector::BLF::ObjectType::FLEXRAY_CYCLE:
            show(reinterpret_cast<Vector::BLF::FlexRayV6StartCycleEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::FLEXRAY_MESSAGE:
            show(reinterpret_cast<Vector::BLF::FlexRayV6Message *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_CHECKSUM_INFO:
            show(reinterpret_cast<Vector::BLF::LinChecksumInfo *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SPIKE_EVENT:
            show(reinterpret_cast<Vector::BLF::LinSpikeEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_DRIVER_SYNC:
            show(reinterpret_cast<Vector::BLF::CanDriverHwSync *>(ohb));
            break;

        case Vector::BLF::ObjectType::FLEXRAY_STATUS:
            show(reinterpret_cast<Vector::BLF::FlexRayStatusEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::GPS_EVENT:
            show(reinterpret_cast<Vector::BLF::GpsEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::FR_ERROR:
            show(reinterpret_cast<Vector::BLF::FlexRayVFrError *>(ohb));
            break;

        case Vector::BLF::ObjectType::FR_STATUS:
            show(reinterpret_cast<Vector::BLF::FlexRayVFrStatus *>(ohb));
            break;

        case Vector::BLF::ObjectType::FR_STARTCYCLE:
            show(reinterpret_cast<Vector::BLF::FlexRayVFrStartCycle *>(ohb));
            break;

        case Vector::BLF::ObjectType::FR_RCVMESSAGE:
            show(reinterpret_cast<Vector::BLF::FlexRayVFrReceiveMsg *>(ohb));
            break;

        case Vector::BLF::ObjectType::REALTIMECLOCK:
            show(reinterpret_cast<Vector::BLF::RealtimeClock *>(ohb));
            break;

        case Vector::BLF::ObjectType::Reserved52:
        case Vector::BLF::ObjectType::Reserved53:
            /* do nothing */
            break;

        case Vector::BLF::ObjectType::LIN_STATISTIC:
            show(reinterpret_cast<Vector::BLF::LinStatisticEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::J1708_MESSAGE:
        case Vector::BLF::ObjectType::J1708_VIRTUAL_MSG:
            show(reinterpret_cast<Vector::BLF::J1708Message *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_MESSAGE2:
            show(reinterpret_cast<Vector::BLF::LinMessage2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SND_ERROR2:
            show(reinterpret_cast<Vector::BLF::LinSendError2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SYN_ERROR2:
            show(reinterpret_cast<Vector::BLF::LinSyncError2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_CRC_ERROR2:
            show(reinterpret_cast<Vector::BLF::LinCrcError2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_RCV_ERROR2:
            show(reinterpret_cast<Vector::BLF::LinReceiveError2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_WAKEUP2:
            show(reinterpret_cast<Vector::BLF::LinWakeupEvent2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SPIKE_EVENT2:
            show(reinterpret_cast<Vector::BLF::LinSpikeEvent2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_LONG_DOM_SIG:
            show(reinterpret_cast<Vector::BLF::LinLongDomSignalEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::APP_TEXT:
            show(reinterpret_cast<Vector::BLF::AppText *>(ohb));
            break;

        case Vector::BLF::ObjectType::FR_RCVMESSAGE_EX:
            show(reinterpret_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_STATISTICEX:
            show(reinterpret_cast<Vector::BLF::MostStatisticEx *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_TXLIGHT:
            show(reinterpret_cast<Vector::BLF::MostTxLight *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_ALLOCTAB:
            show(reinterpret_cast<Vector::BLF::MostAllocTab *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_STRESS:
            show(reinterpret_cast<Vector::BLF::MostStress *>(ohb));
            break;

        case Vector::BLF::ObjectType::ETHERNET_FRAME:
            show(reinterpret_cast<Vector::BLF::EthernetFrame *>(ohb));
            break;

        case Vector::BLF::ObjectType::SYS_VARIABLE:
            show(reinterpret_cast<Vector::BLF::SystemVariable *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_ERROR_EXT:
            show(reinterpret_cast<Vector::BLF::CanErrorFrameExt *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT:
            show(reinterpret_cast<Vector::BLF::CanDriverErrorExt *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2:
            show(reinterpret_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_150_MESSAGE:
            show(reinterpret_cast<Vector::BLF::Most150Message *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_150_PKT:
            show(reinterpret_cast<Vector::BLF::Most150Pkt *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_ETHERNET_PKT:
            show(reinterpret_cast<Vector::BLF::MostEthernetPkt *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_150_MESSAGE_FRAGMENT:
            show(reinterpret_cast<Vector::BLF::Most150MessageFragment *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_150_PKT_FRAGMENT:
            show(reinterpret_cast<Vector::BLF::Most150PktFragment *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT:
            show(reinterpret_cast<Vector::BLF::MostEthernetPktFragment *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_SYSTEM_EVENT:
            show(reinterpret_cast<Vector::BLF::MostSystemEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_150_ALLOCTAB:
            show(reinterpret_cast<Vector::BLF::Most150AllocTab *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_50_MESSAGE:
            show(reinterpret_cast<Vector::BLF::Most50Message *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_50_PKT:
            show(reinterpret_cast<Vector::BLF::Most50Pkt *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_MESSAGE2:
            show(reinterpret_cast<Vector::BLF::CanMessage2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_UNEXPECTED_WAKEUP:
            show(reinterpret_cast<Vector::BLF::LinUnexpectedWakeup *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE:
            show(reinterpret_cast<Vector::BLF::LinShortOrSlowResponse *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_DISTURBANCE_EVENT:
            show(reinterpret_cast<Vector::BLF::LinDisturbanceEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::SERIAL_EVENT:
            show(reinterpret_cast<Vector::BLF::SerialEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::OVERRUN_ERROR:
            show(reinterpret_cast<Vector::BLF::DriverOverrun *>(ohb));
            break;

        case Vector::BLF::ObjectType::EVENT_COMMENT:
            show(reinterpret_cast<Vector::BLF::EventComment *>(ohb));
            break;

        case Vector::BLF::ObjectType::WLAN_FRAME:
            show(reinterpret_cast<Vector::BLF::WlanFrame *>(ohb));
            break;

        case Vector::BLF::ObjectType::WLAN_STATISTIC:
            show(reinterpret_cast<Vector::BLF::WlanStatistic *>(ohb));
            break;

        case Vector::BLF::ObjectType::MOST_ECL:
            show(reinterpret_cast<Vector::BLF::MostEcl *>(ohb));
            break;

        case Vector::BLF::ObjectType::GLOBAL_MARKER:
            show(reinterpret_cast<Vector::BLF::GlobalMarker *>(ohb));
            break;

        case Vector::BLF::ObjectType::AFDX_FRAME:
            show(reinterpret_cast<Vector::BLF::AfdxFrame *>(ohb));
            break;

        case Vector::BLF::ObjectType::AFDX_STATISTIC:
            show(reinterpret_cast<Vector::BLF::AfdxStatistic *>(ohb));
            break;

        case Vector::BLF::ObjectType::KLINE_STATUSEVENT:
            show(reinterpret_cast<Vector::BLF::KLineStatusEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_FD_MESSAGE:
            show(reinterpret_cast<Vector::BLF::CanFdMessage *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_FD_MESSAGE_64:
            show(reinterpret_cast<Vector::BLF::CanFdMessage64 *>(ohb));
            break;

        case Vector::BLF::ObjectType::ETHERNET_RX_ERROR:
            show(reinterpret_cast<Vector::BLF::EthernetRxError *>(ohb));
            break;

        case Vector::BLF::ObjectType::ETHERNET_STATUS:
            show(reinterpret_cast<Vector::BLF::EthernetStatus *>(ohb));
            break;

        case Vector::BLF::ObjectType::CAN_FD_ERROR_64:
            show(reinterpret_cast<Vector::BLF::CanFdErrorFrame64 *>(ohb));
            break;

        case Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE2:
            show(reinterpret_cast<Vector::BLF::LinShortOrSlowResponse2 *>(ohb));
            break;

        case Vector::BLF::ObjectType::AFDX_STATUS:
            show(reinterpret_cast<Vector::BLF::AfdxStatus *>(ohb));
            break;

        case Vector::BLF::ObjectType::AFDX_BUS_STATISTIC:
            show(reinterpret_cast<Vector::BLF::AfdxBusStatistic *>(ohb));
            break;

        case Vector::BLF::ObjectType::Reserved108:
            /* do nothing */
            break;

        case Vector::BLF::ObjectType::AFDX_ERROR_EVENT:
            show(reinterpret_cast<Vector::BLF::AfdxErrorEvent *>(ohb));
            break;

        case Vector::BLF::ObjectType::A429_ERROR:
            show(reinterpret_cast<Vector::BLF::A429Error *>(ohb));
            break;

        case Vector::BLF::ObjectType::A429_STATUS:
            show(reinterpret_cast<Vector::BLF::A429Status *>(ohb));
            break;

        case Vector::BLF::ObjectType::A429_BUS_STATISTIC:
            show(reinterpret_cast<Vector::BLF::A429BusStatistic *>(ohb));
            break;

        case Vector::BLF::ObjectType::A429_MESSAGE:
            show(reinterpret_cast<Vector::BLF::A429Message *>(ohb));
            break;

        case Vector::BLF::ObjectType::ETHERNET_STATISTIC:
            show(reinterpret_cast<Vector::BLF::EthernetStatistic *>(ohb));
            break;

        case Vector::BLF::ObjectType::Unknown115:
            show(reinterpret_cast<Vector::BLF::Unknown115 *>(ohb));
            break;

        case Vector::BLF::ObjectType::Reserved116:
        case Vector::BLF::ObjectType::Reserved117:
            /* do nothing */
            break;

        case Vector::BLF::ObjectType::TEST_STRUCTURE:
            show(reinterpret_cast<Vector::BLF::TestStructure *>(ohb));
            break;

        case Vector::BLF::ObjectType::DIAG_REQUEST_INTERPRETATION:
            show(reinterpret_cast<Vector::BLF::DiagRequestInterpretation *>(ohb));
            break;

        case Vector::BLF::ObjectType::ETHERNET_FRAME_EX:
            show(reinterpret_cast<Vector::BLF::EthernetFrameEx *>(ohb));
            break;

        case Vector::BLF::ObjectType::ETHERNET_FRAME_FORWARDED:
            show(reinterpret_cast<Vector::BLF::EthernetFrameForwarded *>(ohb));
            break;

        case Vector::BLF::ObjectType::ETHERNET_ERROR_EX:
            show(reinterpret_cast<Vector::BLF::EthernetErrorEx *>(ohb));
            break;

        case Vector::BLF::ObjectType::ETHERNET_ERROR_FORWARDED:
            show(reinterpret_cast<Vector::BLF::EthernetErrorForwarded *>(ohb));
            break;
        }

        /* check objectSize */
        if (ohb->objectSize != ohb->calculateObjectSize()) {
            std::cout << "ObjectSize=" << ohb->objectSize << " doesn't match calculatedObjectSize()=" << ohb->calculateObjectSize() << std::endl;
        }

        /* delete object */
        delete ohb;
    }

    std::cout << "End of file." << std::endl;
    std::cout << "objectCount: " << std::dec << file.currentObjectCount << std::endl;
    std::cout << "uncompressedFileSize: " << std::dec << file.currentUncompressedFileSize << std::endl;

    file.close();

    return 0;
}
