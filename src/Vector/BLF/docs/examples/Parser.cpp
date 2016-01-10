#include <iostream>
#include <fstream>

#include "Vector/BLF.h"

void showFileStatistics(Vector::BLF::FileStatistics * fileStatistics)
{
    std::cout << "statisticsSize: 0x" << std::hex << fileStatistics->statisticsSize << std::endl;
    std::cout << "applicationId: " << std::dec << (unsigned short) fileStatistics->applicationId << std::endl;
    std::cout << "applicationVersion: "
              << (unsigned short) fileStatistics->applicationMajor << "."
              << (unsigned short) fileStatistics->applicationMinor << "."
              << (unsigned short) fileStatistics->applicationBuild << std::endl;
    std::cout << "apiVersion: "
              << (unsigned short) fileStatistics->apiMajor << "."
              << (unsigned short) fileStatistics->apiMinor << "."
              << (unsigned short) fileStatistics->apiBuild << "."
              << (unsigned short) fileStatistics->apiPatch << std::endl;
    std::cout << "fileSize: " << fileStatistics->fileSize << std::endl;
    std::cout << "uncompressedFileSize: " << fileStatistics->uncompressedFileSize <<
                 " (hex: 0x" << std::hex << fileStatistics->uncompressedFileSize << ")" << std::dec << std::endl;
    std::cout << "objectCount: " << fileStatistics->objectCount << std::endl;
    std::cout << "objectsRead: " << fileStatistics->objectsRead << std::endl;
    std::cout << "measurementStartTime: "
              << fileStatistics->measurementStartTime.year << "-"
              << fileStatistics->measurementStartTime.month << "-"
              << fileStatistics->measurementStartTime.day << " "
              << fileStatistics->measurementStartTime.dayOfWeek << " "
              << fileStatistics->measurementStartTime.hour << ":"
              << fileStatistics->measurementStartTime.minute << ":"
              << fileStatistics->measurementStartTime.second << "."
              << fileStatistics->measurementStartTime.milliseconds
              << std::endl;
    std::cout << "lastObjectTime: "
              << fileStatistics->lastObjectTime.year << "-"
              << fileStatistics->lastObjectTime.month << "-"
              << fileStatistics->lastObjectTime.day << " "
              << fileStatistics->lastObjectTime.dayOfWeek << " "
              << fileStatistics->lastObjectTime.hour << ":"
              << fileStatistics->lastObjectTime.minute << ":"
              << fileStatistics->lastObjectTime.second << "."
              << fileStatistics->lastObjectTime.milliseconds
              << std::endl;
    std::cout << std::endl;
}

// UNKNOWN = 0

// CAN_MESSAGE = 1
void showCanMessage(Vector::BLF::CanMessage * canMessage)
{
    std::cout << "CanMessage:"
              << " ch=" << canMessage->channel
              << " flags=" << (unsigned short) canMessage->flags
              << " dlc=" << (unsigned short) canMessage->dlc
              << " id=0x" << std::hex << canMessage->id
              << " data=";
    for (int i = 0; (i < canMessage->dlc) && (i < 8); ++i) {
        std::cout << std::hex;
        if (canMessage->data[i] <= 0xf)
            std::cout << '0';
        std::cout << ((unsigned short) canMessage->data[i]);
        std::cout << " ";
    }
    std::cout << std::endl;
}

// CAN_ERROR = 2
void showCanErrorFrame(Vector::BLF::CanErrorFrame * canErrorFrame)
{
     std::cout << "CanErrorFrame:";
     std::cout << " ch=" << std::dec << canErrorFrame->channel;
     std::cout << " len=" << std::dec << canErrorFrame->length;
     std::cout << std::endl;
}

// CAN_OVERLOAD = 3

// CAN_STATISTIC = 4
void showCanDriverStatistic(Vector::BLF::CanDriverStatistic * canDriverStatistic)
{
    std::cout << "CanDriverStatistic:";
    std::cout << " ch=" << std::dec << canDriverStatistic->channel;
    std::cout << " busLoad=" << std::dec << canDriverStatistic->busLoad;
    std::cout << " stdDtFrm=" << std::dec << canDriverStatistic->standardDataFrames;
    std::cout << " extDtFrm=" << std::dec << canDriverStatistic->extendedDataFrames;
    std::cout << " stdRmtFrm=" << std::dec << canDriverStatistic->standardRemoteFrames;
    std::cout << " extRmtFrm=" << std::dec << canDriverStatistic->extendedRemoteFrames;
    std::cout << " errFrm=" << std::dec << canDriverStatistic->errorFrames;
    std::cout << " ovrldFrm=" << std::dec << canDriverStatistic->overloadFrames;
    std::cout << std::endl;
}

// APP_TRIGGER = 5

// ENV_INTEGER = 6
// ENV_DOUBLE = 7
// ENV_STRING = 8
// ENV_DATA = 9
void showEnvironmentVariable(Vector::BLF::EnvironmentVariable * environmentVariable)
{
    std::cout << "EnvironmentVariable:";
    std::cout << " name=" << environmentVariable->name;
    switch(environmentVariable->objectType) {
    case Vector::BLF::ObjectType::ENV_INTEGER:
        std::cout << " value=" << std::dec << (int) *environmentVariable->data.data();
        std::cout << " type=Integer";
        break;
    case Vector::BLF::ObjectType::ENV_DOUBLE:
        std::cout << " value=" << std::fixed << (double) *environmentVariable->data.data();
        std::cout << " type=Double";
        break;
    case Vector::BLF::ObjectType::ENV_STRING:
        std::cout << " type=String";
        // todo
        break;
    case Vector::BLF::ObjectType::ENV_DATA:
        std::cout << " type=Data";
        // todo
        break;
    }
    std::cout << std::endl;
}

// LOG_CONTAINER = 10
void showLogContainer(Vector::BLF::LogContainer * logContainer)
{
    std::cout << "signature: 0x" << std::hex << logContainer->signature << std::endl;
    std::cout << "headerSize: 0x" << std::hex << logContainer->headerSize << std::endl;
    std::cout << "headerVersion: 0x" << std::hex << logContainer->headerVersion << std::endl;
    std::cout << "objectSize: 0x" << std::hex << logContainer->objectSize << std::endl;
    std::cout << "objectType: " << std::dec << (int) logContainer->objectType << std::endl;

    std::cout << "objectFlags: 0x" << std::hex << logContainer->objectFlags << std::endl;
    std::cout << "objectVersion: 0x" << std::hex << logContainer->objectVersion << std::endl;
    std::cout << "uncompressedFileSize: " << std::dec << logContainer->uncompressedFileSize << std::endl;
    std::cout << std::endl;
}

// LIN_MESSAGE = 11

// LIN_CRC_ERROR = 12

// LIN_DLC_INFO = 13

// LIN_RCV_ERROR =  14

// LIN_SND_ERROR = 15

// LIN_SLV_TIMEOUT = 16

// LIN_SCHED_MODCH = 17
void showLinSchedulerModeChange(Vector::BLF::LinSchedulerModeChange * linSchedulerModeChange)
{
    std::cout << "LinSchedulerModeChange:";
    std::cout << " ch=" << std::dec << linSchedulerModeChange->channel;
    std::cout << " old=" << std::dec << (unsigned short) linSchedulerModeChange->oldMode;
    std::cout << " new=" << std::dec << (unsigned short) linSchedulerModeChange->newMode;
    std::cout << std::endl;
}

// LIN_SYN_ERROR = 18

// LIN_BAUDRATE = 19

// LIN_SLEEP = 20
void showLinSleepModeEvent(Vector::BLF::LinSleepModeEvent * linSleepModeEvent)
{
    std::cout << "LinSleepModeEvent:";
    std::cout << " ch=" << std::dec << linSleepModeEvent->channel;
    std::cout << " rsn=" << std::dec << (unsigned short) linSleepModeEvent->reason;
    std::cout << " flags=0x" << std::hex << (unsigned short) linSleepModeEvent->flags;
    std::cout << std::endl;
}

// LIN_WAKEUP = 21

// MOST_SPY = 22
void showMostSpy(Vector::BLF::MostSpy * mostSpy)
{
    std::cout << "MostSpy:";
    std::cout << " ch=" << std::dec << mostSpy->channel;
    std::cout << " dir=" << std::dec << (unsigned short) mostSpy->dir;
    std::cout << " sourceAdr=" << std::dec << mostSpy->sourceAdr;
    std::cout << " destAdr=" << std::dec << mostSpy->destAdr;
    std::cout << " msg=" << std::hex;
    for (int i = 0; i < 17; ++i) {
        if (mostSpy->msg[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << (unsigned short) mostSpy->msg[i];
    }
    std::cout << " rTyp=0x" << std::hex << mostSpy->rTyp;
    std::cout << " rTypAdr=0x" << std::hex << (unsigned short) mostSpy->rTypAdr;
    std::cout << " state=0x" << std::hex << (unsigned short) mostSpy->state;
    std::cout << " ackNack=0x" << std::hex << (unsigned short) mostSpy->ackNack;
    std::cout << " crc=0x" << std::hex << mostSpy->crc;
    std::cout << std::endl;
}

// MOST_CTRL = 23
void showMostCtrl(Vector::BLF::MostCtrl * mostCtrl)
{
    std::cout << "MostCtrl:";
    std::cout << " ch=" << std::dec << mostCtrl->channel;
    std::cout << " dir=" << std::dec << (unsigned short) mostCtrl->dir;
    std::cout << " sourceAdr=" << std::dec << mostCtrl->sourceAdr;
    std::cout << " destAdr=" << std::dec << mostCtrl->destAdr;
    std::cout << " msg=" << std::hex;
    for (int i = 0; i < 17; ++i) {
        if (mostCtrl->msg[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << (unsigned short) mostCtrl->msg[i];
    }
    std::cout << " rTyp=0x" << std::hex << mostCtrl->rTyp;
    std::cout << " rTypAdr=0x" << std::hex << (unsigned short) mostCtrl->rTypAdr;
    std::cout << " state=0x" << std::hex << (unsigned short) mostCtrl->state;
    std::cout << " ackNack=0x" << std::hex << (unsigned short) mostCtrl->ackNack;
    std::cout << std::endl;
}

// MOST_LIGHTLOCK = 24
void showMostLightLock(Vector::BLF::MostLightLock * mostLightLock)
{
    std::cout << "MostLightLock:";
    std::cout << " ch=" << std::dec << mostLightLock->channel;
    std::cout << " state=0x" << std::hex << mostLightLock->state;
    std::cout << std::endl;
}

// MOST_STATISTIC = 25
void showMostStatistic(Vector::BLF::MostStatistic * mostStatistic)
{
    std::cout << "MostStatistic:";
    std::cout << " ch=" << std::dec << mostStatistic->channel;
    std::cout << " pktCnt=" << std::dec << mostStatistic->pktCnt;
    std::cout << " frmCnt=" << std::dec << mostStatistic->frmCnt;
    std::cout << " lightCnt=" << std::dec << mostStatistic->lightCnt;
    std::cout << " bufferLevel=" << std::dec << mostStatistic->bufferLevel;
    std::cout << std::endl;
}

// reserved_1 = 26
// reserved_2 = 27
// reserved_3 = 28

// FLEXRAY_DATA = 29

// FLEXRAY_SYNC = 30

// CAN_DRIVER_ERROR = 31
void showCanDriverError(Vector::BLF::CanDriverError * canDriverError)
{
    std::cout << "CanDriverError:";
    std::cout << " ch=" << std::dec << canDriverError->channel;
    std::cout << " txErr=" << std::dec << (unsigned short) canDriverError->txErrors;
    std::cout << " rxErr=" << std::dec << (unsigned short) canDriverError->rxErrors;
    std::cout << " errCode=" << std::dec << canDriverError->errorCode;
    std::cout << std::endl;
}

// MOST_PKT = 32
void showMostPkt(Vector::BLF::MostPkt * mostPkt)
{
    std::cout << "MostPkt:";
    std::cout << " ch=" << std::dec << mostPkt->channel;
    std::cout << " dir=" << std::dec << (unsigned short) mostPkt->dir;
    std::cout << " sa=" << std::dec << mostPkt->sourceAdr;
    std::cout << " da=" << std::dec << mostPkt->destAdr;
    std::cout << " arb=" << std::dec << (unsigned short) mostPkt->arbitration;
    std::cout << " tr=" << std::dec << (unsigned short) mostPkt->timeRes;
    std::cout << " qtf=" << std::dec << (unsigned short) mostPkt->quadsToFollow;
    std::cout << " crc=" << std::dec << mostPkt->crc;
    std::cout << " prio=" << std::dec << (unsigned short) mostPkt->priority;
    std::cout << " tt=" << std::dec << (unsigned short) mostPkt->transferType;
    std::cout << " st=0x" << std::hex << (unsigned short) mostPkt->state;
    std::cout << " len=" << std::dec << mostPkt->pktDataLength;
    std::cout << " data=" << std::hex;
    for (int i = 0; i < mostPkt->pktDataLength; ++i) {
        if (mostPkt->pktData[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << (unsigned short) mostPkt->pktData[i];
    }
    std::cout << std::endl;
}

// MOST_PKT2 = 33
void showMostPkt2(Vector::BLF::MostPkt2 * mostPkt2)
{
    std::cout << "MostPkt2:";
    std::cout << " ch=" << std::dec << mostPkt2->channel;
    std::cout << " dir=" << std::dec << (unsigned short) mostPkt2->dir;
    std::cout << " sa=" << std::dec << mostPkt2->sourceAdr;
    std::cout << " da=" << std::dec << mostPkt2->destAdr;
    std::cout << " arb=" << std::dec << (unsigned short) mostPkt2->arbitration;
    std::cout << " tr=" << std::dec << (unsigned short) mostPkt2->timeRes;
    std::cout << " qtf=" << std::dec << (unsigned short) mostPkt2->quadsToFollow;
    std::cout << " crc=" << std::dec << mostPkt2->crc;
    std::cout << " prio=" << std::dec << (unsigned short) mostPkt2->priority;
    std::cout << " tt=" << std::dec << (unsigned short) mostPkt2->transferType;
    std::cout << " st=0x" << std::hex << (unsigned short) mostPkt2->state;
    std::cout << " len=" << std::dec << mostPkt2->pktDataLength;
    std::cout << " data=" << std::hex;
    for (int i = 0; i < mostPkt2->pktDataLength; ++i) {
        if (mostPkt2->pktData[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << (unsigned short) mostPkt2->pktData[i];
    }
    std::cout << std::endl;
}

// MOST_HWMODE = 34
void showMostHwMode(Vector::BLF::MostHwMode * mostHwMode)
{
    std::cout << "MostHwMode:";
    std::cout << " ch=" << std::dec << mostHwMode->channel;
    std::cout << " hwMode=0x" << std::hex << mostHwMode->hwMode;
    std::cout << " hwModeMask=0x" << std::hex << mostHwMode->hwModeMask;
    std::cout << std::endl;
}

// MOST_REG = 35
void showMostReg(Vector::BLF::MostReg * mostReg)
{
    std::cout << "MostReg:";
    std::cout << " ch=" << std::dec << mostReg->channel;
    std::cout << " subType=" << std::dec << (unsigned short) mostReg->subType;
    std::cout << " handle=" << std::dec << mostReg->handle;
    std::cout << " offset=" << std::dec << mostReg->offset;
    std::cout << " chip=" << std::dec << mostReg->chip;
    std::cout << " regDataLen=" << std::dec << mostReg->regDataLen;
    std::cout << " regData=0x" << std::hex;
    for (int i = 0; i < mostReg->regDataLen; ++i) {
        if (mostReg->regData[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << (unsigned short) mostReg->regData[i];
    }
    std::cout << std::endl;
}

// MOST_GENREG = 36
void showMostGenReg(Vector::BLF::MostGenReg * mostGenReg)
{
    std::cout << "MostGenReg:";
    std::cout << " ch=" << std::dec << mostGenReg->channel;
    std::cout << " subType=" << std::dec << (unsigned short) mostGenReg->subType;
    std::cout << " handle=" << std::dec << mostGenReg->handle;
    std::cout << " regId=0x" << std::hex << mostGenReg->regId;
    std::cout << " regVal=0x" << std::hex << mostGenReg->regValue;
    std::cout << std::endl;
}

// MOST_NETSTATE = 37
void showMostNetState(Vector::BLF::MostNetState * mostNetState)
{
    std::cout << "MostNetState:";
    std::cout << " ch=" << std::dec << mostNetState->channel;
    std::cout << " stNew=" << std::dec << mostNetState->stateNew;
    std::cout << " stOld=" << std::dec << mostNetState->stateOld;
    std::cout << std::endl;
}

// MOST_DATALOST = 38
void showMostDataLost(Vector::BLF::MostDataLost * mostDataLost)
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
void showMostTrigger(Vector::BLF::MostTrigger * mostTrigger)
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

// FLEXRAY_MESSAGE = 41

// LIN_CHECKSUM_INFO = 42

// LIN_SPIKE_EVENT = 43

// CAN_DRIVER_SYNC = 44

// FLEXRAY_STATUS = 45

// GPS_EVENT = 46
void showGpsEvent(Vector::BLF::GpsEvent * gpsEvent)
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

// FR_STATUS = 48

// FR_STARTCYCLE = 49

// FR_RCVMESSAGE = 50

// REALTIMECLOCK = 51

// AVAILABLE2 = 52
// AVAILABLE3 = 53

// LIN_STATISTIC = 54
void showLinStatisticEvent(Vector::BLF::LinStatisticEvent * linStatisticEvent)
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

// LIN_MESSAGE2 = 57
void showLinMessage2(Vector::BLF::LinMessage2 * linMessage2)
{
    std::cout << "LinMessage2:";
    std::cout << " data=0x";
    for (int i = 0; i < linMessage2->dlc; ++i) {
        if (linMessage2->data[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << std::hex << (unsigned short) linMessage2->data[i];
    }
    std::cout << " crc=0x" << std::hex << linMessage2->crc;
    std::cout << " dir=" << std::dec << (unsigned short) linMessage2->dir;
    std::cout << " sim=" << std::dec << (unsigned short) linMessage2->simulated;
    std::cout << " etf=" << std::dec << (unsigned short) linMessage2->isEtf;
    std::cout << " etfAI=" << std::dec << (unsigned short) linMessage2->etfAssocIndex;
    std::cout << " etfAEI=" << std::dec << (unsigned short) linMessage2->etfAssocEtfId;
    std::cout << " fsmId=" << std::dec << (unsigned short) linMessage2->fsmId;
    std::cout << " fsmState=" << std::dec << (unsigned short) linMessage2->fsmState;
    std::cout << " respBaudrate=" << std::dec << linMessage2->respBaudrate;
    std::cout << " exactHeaderBaudrate=" << std::dec << linMessage2->exactHeaderBaudrate;
    std::cout << " earlyStopbitOffset=" << std::dec << linMessage2->earlyStopbitOffset;
    std::cout << " earlyStopbitOffsetResponse=" << std::dec << linMessage2->earlyStopbitOffsetResponse;
    std::cout << std::endl;
}

// LIN_SND_ERROR2 = 58

// LIN_SYN_ERROR2 = 59

// LIN_CRC_ERROR2 = 60

// LIN_RCV_ERROR2 = 61

// LIN_WAKEUP2 = 62
void showLinWakeupEvent2(Vector::BLF::LinWakeupEvent2 * linWakeupEvent2)
{
    std::cout << "LinWakeupEvent2:";
    std::cout << " len=" << std::dec << (unsigned short) linWakeupEvent2->lengthInfo;
    std::cout << " sig=" << std::dec << (unsigned short) linWakeupEvent2->signal;
    std::cout << " ext=" << std::dec << (unsigned short) linWakeupEvent2->external;
    std::cout << std::endl;
}

// LIN_SPIKE_EVENT2 = 63

// LIN_LONG_DOM_SIG = 64

// APP_TEXT = 65

// FR_RCVMESSAGE_EX = 66

// MOST_STATISTICEX = 67

// MOST_TXLIGHT = 68

// MOST_ALLOCTAB = 69
void showMostAllocTab(Vector::BLF::MostAllocTab * mostAllocTab)
{
    std::cout << "MostAllocTab:";
    std::cout << " ch=" << std::dec << mostAllocTab->channel;
    std::cout << " len=0x" << std::hex << mostAllocTab->length;
    std::cout << " allocTab=0x" << std::hex;
    for (int i = 0; i < mostAllocTab->length; ++i) {
        if (mostAllocTab->tableData[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << (unsigned short) mostAllocTab->tableData[i];
    }
    std::cout << std::endl;
}

// MOST_STRESS = 70

// ETHERNET_FRAME = 71

// SYS_VARIABLE = 72
void showSystemVariable(Vector::BLF::SystemVariable * systemVariable)
{
    std::cout << "SystemVariable:";
    std::cout << " name=" << systemVariable->name;
    switch(systemVariable->type) {
    case Vector::BLF::SystemVariable::Type::Double:
        std::cout << " value=" << std::fixed << (double) *systemVariable->data.data();
        std::cout << " type=Double";
        break;
    case Vector::BLF::SystemVariable::Type::Long:
        std::cout << " value=" << std::dec << (long) *systemVariable->data.data();
        std::cout << " type=Long";
        break;
    case Vector::BLF::SystemVariable::Type::String:
        std::cout << " type=String";
        // todo
        break;
    case Vector::BLF::SystemVariable::Type::DoubleArray:
        std::cout << " type=DoubleArray";
        // todo
        break;
    case Vector::BLF::SystemVariable::Type::LongArray:
        std::cout << " type=LongArray";
        // todo
        break;
    case Vector::BLF::SystemVariable::Type::LongLong:
        std::cout << " type=LongLong";
        // todo
        break;
    case Vector::BLF::SystemVariable::Type::ByteArray:
        std::cout << " type=ByteArray";
        // todo
        break;
    }
    std::cout << std::endl;
}

// CAN_ERROR_EXT = 73
void showCanErrorFrameExt(Vector::BLF::CanErrorFrameExt * canErrorFrameExt)
{
    std::cout << "CanErrorFrameExt:";
    std::cout << " ch=" << std::dec << canErrorFrameExt->channel;
    std::cout << " len=" << std::dec << canErrorFrameExt->length;
    std::cout << " flags=0x" << std::hex << canErrorFrameExt->flags;
    std::cout << " ecc=0x" << std::hex << (unsigned short) canErrorFrameExt->ecc;
    std::cout << " pos=" << std::dec << (unsigned short) canErrorFrameExt->position;
    std::cout << " dlc=" << std::dec << (unsigned short) canErrorFrameExt->dlc;
    std::cout << " ns=" << std::dec << canErrorFrameExt->frameLengthInNs;
    std::cout << " id=0x" << std::hex << canErrorFrameExt->id;
    std::cout << " flagsExt=0x" << std::hex << canErrorFrameExt->flagsExt;
    std::cout << " msg=" << std::hex;
    for (int i = 0; i < canErrorFrameExt->dlc; ++i) {
        if (canErrorFrameExt->data[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << (unsigned short) canErrorFrameExt->data[i];
    }
    std::cout << std::endl;
}

// CAN_DRIVER_ERROR_EXT = 74

// LIN_LONG_DOM_SIG2 = 75

// MOST_150_MESSAGE = 76

// MOST_150_PKT = 77

// MOST_ETHERNET_PKT = 78

// MOST_150_MESSAGE_FRAGMENT = 79

// MOST_150_PKT_FRAGMENT = 80

// MOST_ETHERNET_PKT_FRAGMENT = 81

// MOST_SYSTEM_EVENT = 82

// MOST_150_ALLOCTAB = 83

// MOST_50_MESSAGE = 84

// MOST_50_PKT = 85

// CAN_MESSAGE2 = 86

// LIN_UNEXPECTED_WAKEUP = 87

// LIN_SHORT_OR_SLOW_RESPONSE = 88

// LIN_DISTURBANCE_EVENT = 89

// SERIAL_EVENT = 90

// OVERRUN_ERROR = 91

// EVENT_COMMENT = 92
void showEventComment(Vector::BLF::EventComment * eventComment)
{
    std::cout << "EventComment:";
    std::cout << " type=" << std::dec << eventComment->commentedEventType;
    std::cout << " text=" << eventComment->text;
    std::cout << std::endl;
}

// WLAN_FRAME = 93

// WLAN_STATISTIC = 94

// MOST_ECL = 95

// GLOBAL_MARKER = 96
void showGlobalMarker(Vector::BLF::GlobalMarker * globalMarker)
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
void showAfdxFrame(Vector::BLF::AfdxFrame * afdxFrame)
{
    std::cout << "AfdxFrame:";
    std::cout << " SA=";
    for (int i = 0; i < 6; ++i) {
        if (afdxFrame->sourceAddress[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << std::hex << (unsigned short) afdxFrame->sourceAddress[i];
        if (i < 5) {
            std::cout << ":";
        }
    }
    std::cout << " ch=" << std::dec << afdxFrame->channel;
    std::cout << " DA=";
    for (int i = 0; i < 6; ++i) {
        if (afdxFrame->destinationAddress[i] < 0x10) {
            std::cout << "0";
        }
        std::cout << std::hex << (unsigned short) afdxFrame->destinationAddress[i];
        if (i < 5) {
            std::cout << ":";
        }
    }
    std::cout << " dir=" << std::dec << (unsigned short) afdxFrame->dir;
    std::cout << " type=0x" << std::hex << afdxFrame->type;
    std::cout << " tpid=" << std::dec << afdxFrame->tpid;
    std::cout << " tci=" << std::dec << afdxFrame->tci;
    std::cout << " ethChan=" << std::dec << (unsigned short) afdxFrame->ethChannel;
    std::cout << " flags=0x" << std::hex << afdxFrame->afdxFlags;
    std::cout << " bagUsec=" << std::dec << afdxFrame->bagUsec;
    std::cout << " len=0x" << std::hex << afdxFrame->payLoadLength;
    // payLoad
    std::cout << std::endl;
}

// AFDX_STATISTIC = 98
void showAfdxStatistic(Vector::BLF::AfdxStatistic * afdxStatistic)
{
    std::cout << "AfdxStatistic:";
    std::cout << " ch=" << std::dec << afdxStatistic->channel;
    std::cout << " flags=0x" << std::hex << (unsigned short) afdxStatistic->flags;
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

// CAN_FD_MESSAGE = 100

// CAN_FD_MESSAGE_64 = 101

// ETHERNET_RX_ERROR = 102

// ETHERNET_STATUS = 103

// CAN_FD_ERROR_64 = 104

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Parser <filename.blf>" << std::endl;
        return -1;
    }

    Vector::BLF::File file;
    file.open(argv[1]);

    showFileStatistics(&file.fileStatistics);

    while(!file.eof()) {
        Vector::BLF::ObjectHeaderBase * obj = file.read();
        if (obj == nullptr)
            continue;

        switch(obj->objectType) {
        case Vector::BLF::ObjectType::CAN_MESSAGE:
            showCanMessage(reinterpret_cast<Vector::BLF::CanMessage *>(obj));
            break;

        case Vector::BLF::ObjectType::CAN_ERROR:
            showCanErrorFrame(reinterpret_cast<Vector::BLF::CanErrorFrame *>(obj));
            break;

        case Vector::BLF::ObjectType::CAN_OVERLOAD:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::CAN_STATISTIC:
            showCanDriverStatistic(reinterpret_cast<Vector::BLF::CanDriverStatistic *>(obj));
            break;

        case Vector::BLF::ObjectType::APP_TRIGGER:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::ENV_INTEGER:
        case Vector::BLF::ObjectType::ENV_DOUBLE:
        case Vector::BLF::ObjectType::ENV_STRING:
        case Vector::BLF::ObjectType::ENV_DATA:
            showEnvironmentVariable(reinterpret_cast<Vector::BLF::EnvironmentVariable *>(obj));
            break;

        case Vector::BLF::ObjectType::LOG_CONTAINER:
            showLogContainer(reinterpret_cast<Vector::BLF::LogContainer *>(obj));
            break;

        case Vector::BLF::ObjectType::LIN_MESSAGE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_CRC_ERROR:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_DLC_INFO:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_RCV_ERROR:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_SND_ERROR:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_SLV_TIMEOUT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_SCHED_MODCH:
            showLinSchedulerModeChange(reinterpret_cast<Vector::BLF::LinSchedulerModeChange *>(obj));
            break;

        case Vector::BLF::ObjectType::LIN_SYN_ERROR:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_BAUDRATE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_SLEEP:
            showLinSleepModeEvent(reinterpret_cast<Vector::BLF::LinSleepModeEvent *>(obj));
            break;

        case Vector::BLF::ObjectType::LIN_WAKEUP:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_SPY:
            showMostSpy(reinterpret_cast<Vector::BLF::MostSpy *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_CTRL:
            showMostCtrl(reinterpret_cast<Vector::BLF::MostCtrl *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_LIGHTLOCK:
            showMostLightLock(reinterpret_cast<Vector::BLF::MostLightLock *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_STATISTIC:
            showMostStatistic(reinterpret_cast<Vector::BLF::MostStatistic *>(obj));
            break;

        case Vector::BLF::ObjectType::FLEXRAY_DATA:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::FLEXRAY_SYNC:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::CAN_DRIVER_ERROR:
            showCanDriverError(reinterpret_cast<Vector::BLF::CanDriverError *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_PKT:
            showMostPkt(reinterpret_cast<Vector::BLF::MostPkt *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_PKT2:
            showMostPkt2(reinterpret_cast<Vector::BLF::MostPkt2 *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_HWMODE:
            showMostHwMode(reinterpret_cast<Vector::BLF::MostHwMode *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_REG:
            showMostReg(reinterpret_cast<Vector::BLF::MostReg *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_GENREG:
            showMostGenReg(reinterpret_cast<Vector::BLF::MostGenReg *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_NETSTATE:
            showMostNetState(reinterpret_cast<Vector::BLF::MostNetState *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_DATALOST:
            showMostDataLost(reinterpret_cast<Vector::BLF::MostDataLost *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_TRIGGER:
            showMostTrigger(reinterpret_cast<Vector::BLF::MostTrigger *>(obj));
            break;

        case Vector::BLF::ObjectType::FLEXRAY_CYCLE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::FLEXRAY_MESSAGE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_CHECKSUM_INFO:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_SPIKE_EVENT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::CAN_DRIVER_SYNC:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::FLEXRAY_STATUS:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::GPS_EVENT:
            showGpsEvent(reinterpret_cast<Vector::BLF::GpsEvent *>(obj));
            break;

        case Vector::BLF::ObjectType::FR_ERROR:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::FR_STATUS:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::FR_STARTCYCLE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::FR_RCVMESSAGE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::REALTIMECLOCK:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_STATISTIC:
            showLinStatisticEvent(reinterpret_cast<Vector::BLF::LinStatisticEvent *>(obj));
            break;

        case Vector::BLF::ObjectType::J1708_MESSAGE:
        case Vector::BLF::ObjectType::J1708_VIRTUAL_MSG:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_MESSAGE2:
            showLinMessage2(reinterpret_cast<Vector::BLF::LinMessage2 *>(obj));
            break;

        case Vector::BLF::ObjectType::LIN_SND_ERROR2:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_SYN_ERROR2:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_CRC_ERROR2:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_RCV_ERROR2:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_WAKEUP2:
            showLinWakeupEvent2(reinterpret_cast<Vector::BLF::LinWakeupEvent2 *>(obj));
            break;

        case Vector::BLF::ObjectType::LIN_SPIKE_EVENT2:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_LONG_DOM_SIG:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::APP_TEXT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::FR_RCVMESSAGE_EX:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_STATISTICEX:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_TXLIGHT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_ALLOCTAB:
            showMostAllocTab(reinterpret_cast<Vector::BLF::MostAllocTab *>(obj));
            break;

        case Vector::BLF::ObjectType::MOST_STRESS:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::ETHERNET_FRAME:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::SYS_VARIABLE:
            showSystemVariable(reinterpret_cast<Vector::BLF::SystemVariable *>(obj));
            break;

        case Vector::BLF::ObjectType::CAN_ERROR_EXT:
            showCanErrorFrameExt(reinterpret_cast<Vector::BLF::CanErrorFrameExt *>(obj));
            break;

        case Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_150_MESSAGE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_150_PKT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_ETHERNET_PKT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_150_MESSAGE_FRAGMENT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_150_PKT_FRAGMENT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_SYSTEM_EVENT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_150_ALLOCTAB:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_50_MESSAGE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_50_PKT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::CAN_MESSAGE2:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_UNEXPECTED_WAKEUP:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::LIN_DISTURBANCE_EVENT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::SERIAL_EVENT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::OVERRUN_ERROR:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::EVENT_COMMENT:
            showEventComment(reinterpret_cast<Vector::BLF::EventComment *>(obj));
            break;

        case Vector::BLF::ObjectType::WLAN_FRAME:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::WLAN_STATISTIC:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::MOST_ECL:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::GLOBAL_MARKER:
            showGlobalMarker(reinterpret_cast<Vector::BLF::GlobalMarker *>(obj));
            break;

        case Vector::BLF::ObjectType::AFDX_FRAME:
            showAfdxFrame(reinterpret_cast<Vector::BLF::AfdxFrame *>(obj));
            break;

        case Vector::BLF::ObjectType::AFDX_STATISTIC:
            showAfdxStatistic(reinterpret_cast<Vector::BLF::AfdxStatistic *>(obj));
            break;

        case Vector::BLF::ObjectType::KLINE_STATUSEVENT:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::CAN_FD_MESSAGE:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::CAN_FD_MESSAGE_64:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::ETHERNET_RX_ERROR:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::ETHERNET_STATUS:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        case Vector::BLF::ObjectType::CAN_FD_ERROR_64:
            std::cout << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
            break;

        default:
            std::cout << "Unexpected ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
        }

        /* check objectSize */
        if (obj->objectSize != obj->calculateObjectSize()) {
            std::cout << "ObjectSize=" << obj->objectSize << " doesn't match calculatedObjectSize()=" << obj->calculateObjectSize() << std::endl;
        }

        /* delete object */
        delete obj;
    }

    std::cout << "End of file." << std::endl;
    std::cout << "objectCount: " << std::dec << file.currentObjectCount << std::endl;
    std::cout << "uncompressedFileSize: " << std::dec << file.currentUncompressedFileSize << std::endl;

    file.close();

    return 0;
}
