#define BOOST_TEST_MODULE Events
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iterator>
#include <sstream>
#include <string>

#include "Vector/BLF.h"

static bool isEqual(double a, double b)
{
    return ((a-b) < 0.000001) && ((b-a) < 0.000001);
}

/* UNKNOWN = 0 */

/* CAN_MESSAGE = 1 */
BOOST_AUTO_TEST_CASE(CanMessage)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanMessage * canMessage;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    canMessage = static_cast<Vector::BLF::CanMessage *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canMessage->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canMessage->headerSize == canMessage->calculateHeaderSize());
    BOOST_CHECK(canMessage->headerVersion == 1);
    BOOST_CHECK(canMessage->objectSize == canMessage->calculateObjectSize());
    BOOST_CHECK(canMessage->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    /* ObjectHeader */
    BOOST_CHECK(canMessage->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canMessage->objectVersion == 0);
    BOOST_CHECK(canMessage->objectTimeStamp == 4876870000); // ns
    /* CanMessage */
    BOOST_CHECK(canMessage->channel == 1);
    BOOST_CHECK(canMessage->flags == 1); // TX
    BOOST_CHECK(canMessage->dlc == 8);
    BOOST_CHECK(canMessage->id == 0x854c5638); // 54C5638x
    BOOST_CHECK(canMessage->data[0] == 0);
    BOOST_CHECK(canMessage->data[1] == 0);
    BOOST_CHECK(canMessage->data[2] == 0);
    BOOST_CHECK(canMessage->data[3] == 0);
    BOOST_CHECK(canMessage->data[4] == 0);
    BOOST_CHECK(canMessage->data[5] == 0);
    BOOST_CHECK(canMessage->data[6] == 0);
    BOOST_CHECK(canMessage->data[7] == 0);
    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    canMessage = static_cast<Vector::BLF::CanMessage *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canMessage->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canMessage->headerSize == canMessage->calculateHeaderSize());
    // reserved
    BOOST_CHECK(canMessage->headerVersion == 1);
    BOOST_CHECK(canMessage->objectSize == canMessage->calculateObjectSize());
    BOOST_CHECK(canMessage->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    /* ObjectHeader */
    BOOST_CHECK(canMessage->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canMessage->objectVersion == 0);
    BOOST_CHECK(canMessage->objectTimeStamp == 2501000000); // ns
    /* CanMessage */
    BOOST_CHECK(canMessage->channel == 2);
    BOOST_CHECK(canMessage->flags == 0); // RX
    BOOST_CHECK(canMessage->dlc == 8);
    BOOST_CHECK(canMessage->id == 0x800000c8); // C8x
    BOOST_CHECK(canMessage->data[0] == 9);
    BOOST_CHECK(canMessage->data[1] == 8);
    BOOST_CHECK(canMessage->data[2] == 7);
    BOOST_CHECK(canMessage->data[3] == 6);
    BOOST_CHECK(canMessage->data[4] == 5);
    BOOST_CHECK(canMessage->data[5] == 4);
    BOOST_CHECK(canMessage->data[6] == 3);
    BOOST_CHECK(canMessage->data[7] == 2);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_ERROR = 2 */
BOOST_AUTO_TEST_CASE(CanErrorFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanErrorFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanErrorFrame * canErrorFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR);
    canErrorFrame = static_cast<Vector::BLF::CanErrorFrame *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canErrorFrame->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canErrorFrame->headerSize == canErrorFrame->calculateHeaderSize());
    BOOST_CHECK(canErrorFrame->headerVersion == 1);
    BOOST_CHECK(canErrorFrame->objectSize == canErrorFrame->calculateObjectSize());
    BOOST_CHECK(canErrorFrame->objectType == Vector::BLF::ObjectType::CAN_ERROR);
    /* ObjectHeader */
    BOOST_CHECK(canErrorFrame->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canErrorFrame->objectVersion == 0);
    BOOST_CHECK(canErrorFrame->objectTimeStamp == 2501000000); // ns
    /* CanErrorFrame */
    BOOST_CHECK(canErrorFrame->channel == 1);
    BOOST_CHECK(canErrorFrame->length == 6);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_OVERLOAD = 3 */
#if 0
BOOST_AUTO_TEST_CASE(CanOverloadFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanOverloadFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanOverloadFrame * canOverloadFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_OVERLOAD);
    canOverloadFrame = static_cast<Vector::BLF::CanOverloadFrame *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* CAN_STATISTIC = 4 */
BOOST_AUTO_TEST_CASE(CanDriverStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanDriverStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanDriverStatistic * canDriverStatistic;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_STATISTIC);
    canDriverStatistic = static_cast<Vector::BLF::CanDriverStatistic *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canDriverStatistic->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canDriverStatistic->headerSize == canDriverStatistic->calculateHeaderSize());
    BOOST_CHECK(canDriverStatistic->headerVersion == 1);
    BOOST_CHECK(canDriverStatistic->objectSize == canDriverStatistic->calculateObjectSize());
    BOOST_CHECK(canDriverStatistic->objectType == Vector::BLF::ObjectType::CAN_STATISTIC);
    /* ObjectHeader */
    BOOST_CHECK(canDriverStatistic->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canDriverStatistic->objectVersion == 0);
    BOOST_CHECK(canDriverStatistic->objectTimeStamp == 1010000000); // ns
    /* CanDriverStatistic */
    BOOST_CHECK(canDriverStatistic->channel == 1);
    BOOST_CHECK(canDriverStatistic->busLoad == 0);
    BOOST_CHECK(canDriverStatistic->standardDataFrames == 1000);
    BOOST_CHECK(canDriverStatistic->extendedDataFrames == 0);
    BOOST_CHECK(canDriverStatistic->standardRemoteFrames == 15);
    BOOST_CHECK(canDriverStatistic->extendedRemoteFrames == 0);
    BOOST_CHECK(canDriverStatistic->errorFrames == 0);
    BOOST_CHECK(canDriverStatistic->overloadFrames == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* APP_TRIGGER = 5 */
#if 0
BOOST_AUTO_TEST_CASE(AppTrigger)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/AppTrigger.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::AppTrigger * appTrigger;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::APP_TRIGGER);
    appTrigger = static_cast<Vector::BLF::AppTrigger *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* ENV_INTEGER = 6 */
/* ENV_DOUBLE = 7 */
/* ENV_STRING = 8 */
/* ENV_DATA = 9 */
BOOST_AUTO_TEST_CASE(EnvironmentVariable)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EnvironmentVariable.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EnvironmentVariable * environmentVariable;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ENV_INTEGER);
    environmentVariable = static_cast<Vector::BLF::EnvironmentVariable *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(environmentVariable->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(environmentVariable->headerSize == environmentVariable->calculateHeaderSize());
    BOOST_CHECK(environmentVariable->headerVersion == 1);
    BOOST_CHECK(environmentVariable->objectSize == environmentVariable->calculateObjectSize());
    BOOST_CHECK(environmentVariable->objectType == Vector::BLF::ObjectType::ENV_INTEGER);
    /* ObjectHeader */
    BOOST_CHECK(environmentVariable->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(environmentVariable->objectVersion == 0);
    BOOST_CHECK(environmentVariable->objectTimeStamp == 30613377); // ns
    /* EnvironmentVariable */
    BOOST_CHECK(environmentVariable->nameLength == 11);
    BOOST_CHECK(environmentVariable->dataLength == 4);
    // reserved
    BOOST_CHECK(environmentVariable->name == "EnvGearDown");
    BOOST_CHECK(environmentVariable->data[0] == 0x01);
    BOOST_CHECK(environmentVariable->data[1] == 0x00);
    BOOST_CHECK(environmentVariable->data[2] == 0x00);
    BOOST_CHECK(environmentVariable->data[3] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LOG_CONTAINER = 10 */
// LogContainer is indirectly tested

/* LIN_MESSAGE = 11 */
#if 0
BOOST_AUTO_TEST_CASE(LinMessage)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinMessage * linMessage;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE);
    linMessage = static_cast<Vector::BLF::LinMessage *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_CRC_ERROR = 12 */
#if 0
BOOST_AUTO_TEST_CASE(LinCrcError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinCrcError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinCrcError * linCrcError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_CRC_ERROR);
    linCrcError = static_cast<Vector::BLF::LinCrcError *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_DLC_INFO = 13 */
BOOST_AUTO_TEST_CASE(LinDlcInfo)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDlcInfo.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinDlcInfo * linDlcInfo;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_DLC_INFO);
    linDlcInfo = static_cast<Vector::BLF::LinDlcInfo *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linDlcInfo->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linDlcInfo->headerSize == linDlcInfo->calculateHeaderSize());
    BOOST_CHECK(linDlcInfo->headerVersion == 1);
    BOOST_CHECK(linDlcInfo->objectSize == linDlcInfo->calculateObjectSize());
    BOOST_CHECK(linDlcInfo->objectType == Vector::BLF::ObjectType::LIN_DLC_INFO);
    /* ObjectHeader */
    BOOST_CHECK(linDlcInfo->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linDlcInfo->objectVersion == 0);
    BOOST_CHECK(linDlcInfo->objectTimeStamp == 12637500000); // ns
    /* LinDlcInfo */
    BOOST_CHECK(linDlcInfo->channel == 1);
    BOOST_CHECK(linDlcInfo->id == 20);
    BOOST_CHECK(linDlcInfo->dlc == 4);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_RCV_ERROR = 14 */
#if 0
BOOST_AUTO_TEST_CASE(LinReceiveError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinReceiveError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinReceiveError * linReceiveError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR);
    linReceiveError = static_cast<Vector::BLF::LinReceiveError *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_SND_ERROR = 15 */
#if 0
BOOST_AUTO_TEST_CASE(LinSendError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSendError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSendError * linSendError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SND_ERROR);
    linSendError = static_cast<Vector::BLF::LinSendError *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_SLV_TIMEOUT = 16 */
BOOST_AUTO_TEST_CASE(LinSlaveTimeout)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSlaveTimeout.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSlaveTimeout * linSlaveTimeout;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SLV_TIMEOUT);
    linSlaveTimeout = static_cast<Vector::BLF::LinSlaveTimeout *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSlaveTimeout->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSlaveTimeout->headerSize == linSlaveTimeout->calculateHeaderSize());
    BOOST_CHECK(linSlaveTimeout->headerVersion == 1);
    BOOST_CHECK(linSlaveTimeout->objectSize == linSlaveTimeout->calculateObjectSize());
    BOOST_CHECK(linSlaveTimeout->objectType == Vector::BLF::ObjectType::LIN_SLV_TIMEOUT);
    /* ObjectHeader */
    BOOST_CHECK(linSlaveTimeout->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linSlaveTimeout->objectVersion == 0);
    BOOST_CHECK(linSlaveTimeout->objectTimeStamp == 1001200000); // ns
    /* LinDlcInfo */
    BOOST_CHECK(linSlaveTimeout->channel == 1);
    BOOST_CHECK(linSlaveTimeout->slaveId == 0);
    BOOST_CHECK(linSlaveTimeout->stateId == 0);
    BOOST_CHECK(linSlaveTimeout->followStateId == 1);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SCHED_MODCH = 17 */
BOOST_AUTO_TEST_CASE(LinSchedulerModeChange)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSchedulerModeChange.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSchedulerModeChange * linSchedulerModeChange;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SCHED_MODCH);
    linSchedulerModeChange = static_cast<Vector::BLF::LinSchedulerModeChange *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSchedulerModeChange->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSchedulerModeChange->headerSize == linSchedulerModeChange->calculateHeaderSize());
    BOOST_CHECK(linSchedulerModeChange->headerVersion == 1);
    BOOST_CHECK(linSchedulerModeChange->objectSize == linSchedulerModeChange->calculateObjectSize());
    BOOST_CHECK(linSchedulerModeChange->objectType == Vector::BLF::ObjectType::LIN_SCHED_MODCH);
    /* ObjectHeader */
    BOOST_CHECK(linSchedulerModeChange->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linSchedulerModeChange->objectVersion == 0);
    BOOST_CHECK(linSchedulerModeChange->objectTimeStamp == 100000000); // ns
    /* LinSchedulerModeChange */
    BOOST_CHECK(linSchedulerModeChange->channel == 1);
    BOOST_CHECK(linSchedulerModeChange->oldMode == 2);
    BOOST_CHECK(linSchedulerModeChange->newMode == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SYN_ERROR = 18 */
#if 0
BOOST_AUTO_TEST_CASE(LinSyncError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSyncError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSyncError * linSyncError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SYN_ERROR);
    linSyncError = static_cast<Vector::BLF::LinSyncError *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_BAUDRATE = 19 */
BOOST_AUTO_TEST_CASE(LinBaudrateEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinBaudrateEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinBaudrateEvent * linBaudrateEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_BAUDRATE);
    linBaudrateEvent = static_cast<Vector::BLF::LinBaudrateEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linBaudrateEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linBaudrateEvent->headerSize == linBaudrateEvent->calculateHeaderSize());
    BOOST_CHECK(linBaudrateEvent->headerVersion == 1);
    BOOST_CHECK(linBaudrateEvent->objectSize == linBaudrateEvent->calculateObjectSize());
    BOOST_CHECK(linBaudrateEvent->objectType == Vector::BLF::ObjectType::LIN_BAUDRATE);
    /* ObjectHeader */
    BOOST_CHECK(linBaudrateEvent->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linBaudrateEvent->objectVersion == 0);
    BOOST_CHECK(linBaudrateEvent->objectTimeStamp == 18800000); // ns
    /* LinBaudrate */
    BOOST_CHECK(linBaudrateEvent->channel == 1);
    // reserved
    BOOST_CHECK(linBaudrateEvent->baudrate == 9615);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SLEEP = 20 */
BOOST_AUTO_TEST_CASE(LinSleepModeEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSleepModeEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSleepModeEvent * linSleepModeEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SLEEP);
    linSleepModeEvent = static_cast<Vector::BLF::LinSleepModeEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSleepModeEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSleepModeEvent->headerSize == linSleepModeEvent->calculateHeaderSize());
    BOOST_CHECK(linSleepModeEvent->headerVersion == 1);
    BOOST_CHECK(linSleepModeEvent->objectSize == linSleepModeEvent->calculateObjectSize());
    BOOST_CHECK(linSleepModeEvent->objectType == Vector::BLF::ObjectType::LIN_SLEEP);
    /* ObjectHeader */
    BOOST_CHECK(linSleepModeEvent->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linSleepModeEvent->objectVersion == 0);
    BOOST_CHECK(linSleepModeEvent->objectTimeStamp == 777200000); // ns
    /* LinSleepModeEvent */
    BOOST_CHECK(linSleepModeEvent->channel == 1);
    BOOST_CHECK(linSleepModeEvent->reason == 1);
    BOOST_CHECK(linSleepModeEvent->flags == (uint8_t) Vector::BLF::LinSleepModeEvent::Flags::WasAwake);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_WAKEUP = 21 */
#if 0
BOOST_AUTO_TEST_CASE(LinWakeupEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinWakeupEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinWakeupEvent * linWakeupEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_WAKEUP);
    linWakeupEvent = static_cast<Vector::BLF::LinWakeupEvent *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* MOST_SPY = 22 */
BOOST_AUTO_TEST_CASE(MostSpy)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostSpy.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostSpy * mostSpy;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_SPY);
    mostSpy = static_cast<Vector::BLF::MostSpy *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostSpy->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostSpy->headerSize == mostSpy->calculateHeaderSize());
    BOOST_CHECK(mostSpy->headerVersion == 1);
    BOOST_CHECK(mostSpy->objectSize == mostSpy->calculateObjectSize());
    BOOST_CHECK(mostSpy->objectType == Vector::BLF::ObjectType::MOST_SPY);
    /* ObjectHeader */
    BOOST_CHECK(mostSpy->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(mostSpy->objectVersion == 0);
    BOOST_CHECK(mostSpy->objectTimeStamp == 113526000); // ns
    /* MostSpy */
    BOOST_CHECK(mostSpy->channel == 1);
    BOOST_CHECK(mostSpy->dir == 0); // Rx
    // reserved
    BOOST_CHECK(mostSpy->sourceAdr == 0xffff);
    BOOST_CHECK(mostSpy->destAdr == 0x0100);
    BOOST_CHECK(mostSpy->msg[ 0] == 0x01);
    BOOST_CHECK(mostSpy->msg[ 1] == 0x01);
    BOOST_CHECK(mostSpy->msg[ 2] == 0x00);
    BOOST_CHECK(mostSpy->msg[ 3] == 0x0C);
    BOOST_CHECK(mostSpy->msg[ 4] == 0x04);
    BOOST_CHECK(mostSpy->msg[ 5] == 0x31);
    BOOST_CHECK(mostSpy->msg[ 6] == 0x01);
    BOOST_CHECK(mostSpy->msg[ 7] == 0x52);
    BOOST_CHECK(mostSpy->msg[ 8] == 0x01);
    BOOST_CHECK(mostSpy->msg[ 9] == 0x00);
    BOOST_CHECK(mostSpy->msg[10] == 0x00);
    BOOST_CHECK(mostSpy->msg[11] == 0x00);
    BOOST_CHECK(mostSpy->msg[12] == 0x00);
    BOOST_CHECK(mostSpy->msg[13] == 0x00);
    BOOST_CHECK(mostSpy->msg[14] == 0x00);
    BOOST_CHECK(mostSpy->msg[15] == 0x00);
    BOOST_CHECK(mostSpy->msg[16] == 0x00);
    // reserved
    BOOST_CHECK(mostSpy->rTyp == 0); // Normal
    BOOST_CHECK(mostSpy->rTypAdr == 0x10); // Node position
    BOOST_CHECK(mostSpy->state == 0x01); // bus active
    // reserved
    BOOST_CHECK(mostSpy->ackNack == 0x12); // Valid | NAck
    BOOST_CHECK(mostSpy->crc == 0xAA33);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_CTRL = 23 */
BOOST_AUTO_TEST_CASE(MostCtrl)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostCtrl.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostCtrl * mostCtrl;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_CTRL);
    mostCtrl = static_cast<Vector::BLF::MostCtrl *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostCtrl->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostCtrl->headerSize == mostCtrl->calculateHeaderSize());
    BOOST_CHECK(mostCtrl->headerVersion == 1);
    BOOST_CHECK(mostCtrl->objectSize == mostCtrl->calculateObjectSize());
    BOOST_CHECK(mostCtrl->objectType == Vector::BLF::ObjectType::MOST_CTRL);
    /* ObjectHeader */
    BOOST_CHECK(mostCtrl->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(mostCtrl->objectVersion == 0);
    BOOST_CHECK(mostCtrl->objectTimeStamp == 111757000); // ns
    /* MostCtrl */
    BOOST_CHECK(mostCtrl->channel == 1);
    BOOST_CHECK(mostCtrl->dir == 1); // Tx
    // reserved
    BOOST_CHECK(mostCtrl->sourceAdr == 0x0100);
    BOOST_CHECK(mostCtrl->destAdr == 0x0401);
    BOOST_CHECK(mostCtrl->msg[ 0] == 0x01);
    BOOST_CHECK(mostCtrl->msg[ 1] == 0x01);
    BOOST_CHECK(mostCtrl->msg[ 2] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 3] == 0x01);
    BOOST_CHECK(mostCtrl->msg[ 4] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 5] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 6] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 7] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 8] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 9] == 0x00);
    BOOST_CHECK(mostCtrl->msg[10] == 0x00);
    BOOST_CHECK(mostCtrl->msg[11] == 0x00);
    BOOST_CHECK(mostCtrl->msg[12] == 0x00);
    BOOST_CHECK(mostCtrl->msg[13] == 0x00);
    BOOST_CHECK(mostCtrl->msg[14] == 0x00);
    BOOST_CHECK(mostCtrl->msg[15] == 0x00);
    BOOST_CHECK(mostCtrl->msg[16] == 0x00);
    // reserved
    BOOST_CHECK(mostCtrl->rTyp == 0); // Normal
    BOOST_CHECK(mostCtrl->rTypAdr == 0); // Device
    BOOST_CHECK(mostCtrl->state == 0x50); // TxF|Ack
    // reserved
    BOOST_CHECK(mostCtrl->ackNack == 0x12); // NoResp|NAck
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_LIGHTLOCK = 24 */
BOOST_AUTO_TEST_CASE(MostLightLock)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostLightLock.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostLightLock * mostLightLock;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);
    mostLightLock = static_cast<Vector::BLF::MostLightLock *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostLightLock->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostLightLock->headerSize == mostLightLock->calculateHeaderSize());
    BOOST_CHECK(mostLightLock->headerVersion == 1);
    BOOST_CHECK(mostLightLock->objectSize == mostLightLock->calculateObjectSize());
    BOOST_CHECK(mostLightLock->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);
    /* ObjectHeader */
    BOOST_CHECK(mostLightLock->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(mostLightLock->objectVersion == 0);
    BOOST_CHECK(mostLightLock->objectTimeStamp == 8638000); // ns
    /* MostLightLock */
    BOOST_CHECK(mostLightLock->channel == 1);
    BOOST_CHECK(mostLightLock->state == 1); // Signal On + Lock
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_STATISTIC = 25 */
BOOST_AUTO_TEST_CASE(MostStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostStatistic * mostStatistic;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_STATISTIC);
    mostStatistic = static_cast<Vector::BLF::MostStatistic *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostStatistic->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostStatistic->headerSize == mostStatistic->calculateHeaderSize());
    BOOST_CHECK(mostStatistic->headerVersion == 1);
    BOOST_CHECK(mostStatistic->objectSize == mostStatistic->calculateObjectSize());
    BOOST_CHECK(mostStatistic->objectType == Vector::BLF::ObjectType::MOST_STATISTIC);
    /* ObjectHeader */
    BOOST_CHECK(mostStatistic->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(mostStatistic->objectVersion == 0);
    BOOST_CHECK(mostStatistic->objectTimeStamp == 2030000000); // ns
    /* MostStatistic */
    BOOST_CHECK(mostStatistic->channel == 1);
    BOOST_CHECK(mostStatistic->pktCnt == 0);
    BOOST_CHECK(mostStatistic->frmCnt == 0);
    BOOST_CHECK(mostStatistic->lightCnt == 4);
    BOOST_CHECK(mostStatistic->bufferLevel == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* reserved_1 = 26 */
/* reserved_2 = 27 */
/* reserved_3 = 28 */

/* FLEXRAY_DATA = 29 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRayData)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayData.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayData * flexRayData;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_DATA);
    flexRayData = static_cast<Vector::BLF::FlexRayData *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* FLEXRAY_SYNC = 30 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRaySync)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRaySync.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRaySync * flexRaySync;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_SYNC);
    flexRaySync = static_cast<Vector::BLF::FlexRaySync *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* CAN_DRIVER_ERROR = 31 */
BOOST_AUTO_TEST_CASE(CanDriverError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanDriverError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanDriverError * canDriverError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR);
    canDriverError = static_cast<Vector::BLF::CanDriverError *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canDriverError->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canDriverError->headerSize == canDriverError->calculateHeaderSize());
    BOOST_CHECK(canDriverError->headerVersion == 1);
    BOOST_CHECK(canDriverError->objectSize == canDriverError->calculateObjectSize());
    BOOST_CHECK(canDriverError->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR);
    /* ObjectHeader */
    BOOST_CHECK(canDriverError->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canDriverError->objectVersion == 0);
    BOOST_CHECK(canDriverError->objectTimeStamp == 15282297); // ns
    /* CanDriverError */
    BOOST_CHECK(canDriverError->channel == 1);
    BOOST_CHECK(canDriverError->txErrors == 0);
    BOOST_CHECK(canDriverError->rxErrors == 0);
    BOOST_CHECK(canDriverError->errorCode == 0x68);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_PKT = 32 */
#if 0
BOOST_AUTO_TEST_CASE(MostPkt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostPkt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostPkt * mostPkt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_PKT);
    mostPkt = static_cast<Vector::BLF::MostPkt *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* MOST_PKT2 = 33 */
BOOST_AUTO_TEST_CASE(MostPkt2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostPkt2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostPkt2 * mostPkt2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_PKT2);
    mostPkt2 = static_cast<Vector::BLF::MostPkt2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostPkt2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostPkt2->headerSize == mostPkt2->calculateHeaderSize());
    BOOST_CHECK(mostPkt2->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostPkt2->objectSize == mostPkt2->calculateObjectSize());
    BOOST_CHECK(mostPkt2->objectType == Vector::BLF::ObjectType::MOST_PKT2);
    /* ObjectHeader2 */
    BOOST_CHECK(mostPkt2->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostPkt2->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostPkt2->objectVersion == 0);
    BOOST_CHECK(mostPkt2->objectTimeStamp == 4445080000); // ns
    BOOST_CHECK(mostPkt2->originalTimeStamp == 0);
    /* MostPkt2 */
    BOOST_CHECK(mostPkt2->channel == 1);
    BOOST_CHECK(mostPkt2->dir == 0); // Rx
    // reserved
    BOOST_CHECK(mostPkt2->sourceAdr == 0x0101);
    BOOST_CHECK(mostPkt2->destAdr == 0x0100);
    BOOST_CHECK(mostPkt2->arbitration == 0x03);
    BOOST_CHECK(mostPkt2->timeRes == 0);
    BOOST_CHECK(mostPkt2->quadsToFollow == 0);
    // reserved
    BOOST_CHECK(mostPkt2->crc == 0x0000);
    BOOST_CHECK(mostPkt2->priority == 0);
    BOOST_CHECK(mostPkt2->transferType == 1); // Node
    BOOST_CHECK(mostPkt2->state == 0); // Rx
    // reserved
    BOOST_CHECK(mostPkt2->pktDataLength == 0x0A);
    // reserved
    BOOST_CHECK(mostPkt2->pktData[0] == 0x52);
    BOOST_CHECK(mostPkt2->pktData[1] == 0x01);
    BOOST_CHECK(mostPkt2->pktData[2] == 0xE0);
    BOOST_CHECK(mostPkt2->pktData[3] == 0x3C);
    BOOST_CHECK(mostPkt2->pktData[4] == 0x90);
    BOOST_CHECK(mostPkt2->pktData[5] == 0x01);
    BOOST_CHECK(mostPkt2->pktData[6] == 0xFD);
    BOOST_CHECK(mostPkt2->pktData[7] == 0x00);
    BOOST_CHECK(mostPkt2->pktData[8] == 0x00);
    BOOST_CHECK(mostPkt2->pktData[9] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_HWMODE = 34 */
BOOST_AUTO_TEST_CASE(MostHwMode)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostHwMode.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostHwMode * mostHwMode;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_HWMODE);
    mostHwMode = static_cast<Vector::BLF::MostHwMode *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostHwMode->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostHwMode->headerSize == mostHwMode->calculateHeaderSize());
    BOOST_CHECK(mostHwMode->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostHwMode->objectSize == mostHwMode->calculateObjectSize());
    BOOST_CHECK(mostHwMode->objectType == Vector::BLF::ObjectType::MOST_HWMODE);
    /* ObjectHeader2 */
    BOOST_CHECK(mostHwMode->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostHwMode->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostHwMode->objectVersion == 0);
    BOOST_CHECK(mostHwMode->objectTimeStamp == 3560000000); // ns
    BOOST_CHECK(mostHwMode->originalTimeStamp == 0);
    /* MostHwMode */
    BOOST_CHECK(mostHwMode->channel == 1);
    // reserved
    BOOST_CHECK(mostHwMode->hwMode == 0x01); // active
    BOOST_CHECK(mostHwMode->hwModeMask == 0x01); // ByPass
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_REG = 35 */
BOOST_AUTO_TEST_CASE(MostReg)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostReg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostReg * mostReg;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_REG);
    mostReg = static_cast<Vector::BLF::MostReg *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostReg->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostReg->headerSize == mostReg->calculateHeaderSize());
    BOOST_CHECK(mostReg->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostReg->objectSize == mostReg->calculateObjectSize());
    BOOST_CHECK(mostReg->objectType == Vector::BLF::ObjectType::MOST_REG);
    /* ObjectHeader2 */
    BOOST_CHECK(mostReg->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostReg->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostReg->objectVersion == 0);
    BOOST_CHECK(mostReg->objectTimeStamp == 9050000000); // ns
    BOOST_CHECK(mostReg->originalTimeStamp == 0);
    /* MostReg */
    BOOST_CHECK(mostReg->channel == 1);
    BOOST_CHECK(mostReg->subType == 0);
    // reserved
    BOOST_CHECK(mostReg->handle == 0);
    BOOST_CHECK(mostReg->offset == 0x0000);
    BOOST_CHECK(mostReg->chip == 1); // OS8104
    BOOST_CHECK(mostReg->regDataLen == 0x10);
    BOOST_CHECK(mostReg->regData[0x00] == 0x00);
    BOOST_CHECK(mostReg->regData[0x01] == 0x01);
    BOOST_CHECK(mostReg->regData[0x02] == 0x02);
    BOOST_CHECK(mostReg->regData[0x03] == 0x03);
    BOOST_CHECK(mostReg->regData[0x04] == 0x04);
    BOOST_CHECK(mostReg->regData[0x05] == 0x05);
    BOOST_CHECK(mostReg->regData[0x06] == 0x06);
    BOOST_CHECK(mostReg->regData[0x07] == 0x07);
    BOOST_CHECK(mostReg->regData[0x08] == 0x08);
    BOOST_CHECK(mostReg->regData[0x09] == 0x09);
    BOOST_CHECK(mostReg->regData[0x0a] == 0x0a);
    BOOST_CHECK(mostReg->regData[0x0b] == 0x0b);
    BOOST_CHECK(mostReg->regData[0x0c] == 0x0c);
    BOOST_CHECK(mostReg->regData[0x0d] == 0x0d);
    BOOST_CHECK(mostReg->regData[0x0e] == 0x0e);
    BOOST_CHECK(mostReg->regData[0x0f] == 0x0f);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_GENREG = 36 */
BOOST_AUTO_TEST_CASE(MostGenReg)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostGenReg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostGenReg * mostGenReg;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_GENREG);
    mostGenReg = static_cast<Vector::BLF::MostGenReg *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostGenReg->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostGenReg->headerSize == mostGenReg->calculateHeaderSize());
    BOOST_CHECK(mostGenReg->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostGenReg->objectSize == mostGenReg->calculateObjectSize());
    BOOST_CHECK(mostGenReg->objectType == Vector::BLF::ObjectType::MOST_GENREG);
    /* ObjectHeader2 */
    BOOST_CHECK(mostGenReg->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostGenReg->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostGenReg->objectVersion == 0);
    BOOST_CHECK(mostGenReg->objectTimeStamp == 1471300000); // ns
    BOOST_CHECK(mostGenReg->originalTimeStamp == 0);
    /* MostGenReg */
    BOOST_CHECK(mostGenReg->channel == 1);
    BOOST_CHECK(mostGenReg->subType == 1);
    // reserved
    BOOST_CHECK(mostGenReg->handle == 0);
    BOOST_CHECK(mostGenReg->regId == 0x8A);
    // reserved
    BOOST_CHECK(mostGenReg->regValue == 0x0172);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_NETSTATE = 37 */
BOOST_AUTO_TEST_CASE(MostNetState)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostNetState.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostNetState * mostNetState;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_NETSTATE);
    mostNetState = static_cast<Vector::BLF::MostNetState *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostNetState->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostNetState->headerSize == mostNetState->calculateHeaderSize());
    BOOST_CHECK(mostNetState->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostNetState->objectSize == mostNetState->calculateObjectSize());
    BOOST_CHECK(mostNetState->objectType == Vector::BLF::ObjectType::MOST_NETSTATE);
    /* ObjectHeader2 */
    BOOST_CHECK(mostNetState->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostNetState->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostNetState->objectVersion == 0);
    BOOST_CHECK(mostNetState->objectTimeStamp == 1027900000); // ns
    BOOST_CHECK(mostNetState->originalTimeStamp == 0);
    /* MostNetState */
    BOOST_CHECK(mostNetState->channel == 1);
    BOOST_CHECK(mostNetState->stateNew == 3); // NetInterfaceInit
    BOOST_CHECK(mostNetState->stateOld == 2); // PowerOff
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_DATALOST = 38 */
BOOST_AUTO_TEST_CASE(MostDataLost)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostDataLost.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostDataLost * mostDataLost;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_DATALOST);
    mostDataLost = static_cast<Vector::BLF::MostDataLost *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostDataLost->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostDataLost->headerSize == mostDataLost->calculateHeaderSize());
    BOOST_CHECK(mostDataLost->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostDataLost->objectSize == mostDataLost->calculateObjectSize());
    BOOST_CHECK(mostDataLost->objectType == Vector::BLF::ObjectType::MOST_DATALOST);
    /* ObjectHeader2 */
    BOOST_CHECK(mostDataLost->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostDataLost->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostDataLost->objectVersion == 0);
    BOOST_CHECK(mostDataLost->objectTimeStamp == 1303700000); // ns
    BOOST_CHECK(mostDataLost->originalTimeStamp == 0);
    /* MostDataLost */
    BOOST_CHECK(mostDataLost->channel == 1);
    // reserved
    BOOST_CHECK(mostDataLost->info == 0x05);
    BOOST_CHECK(mostDataLost->lostMsgsCtrl == 0x003F);
    BOOST_CHECK(mostDataLost->lostMsgsAsync == 0x000D);
    BOOST_CHECK(mostDataLost->lastGoodTimeStampNs == 101303690000); // ns
    BOOST_CHECK(mostDataLost->nextGoodTimeStampNs == 2223525920000); // ns
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_TRIGGER = 39 */
BOOST_AUTO_TEST_CASE(MostTrigger)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostTrigger.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostTrigger * mostTrigger;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_TRIGGER);
    mostTrigger = static_cast<Vector::BLF::MostTrigger *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostTrigger->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostTrigger->headerSize == mostTrigger->calculateHeaderSize());
    BOOST_CHECK(mostTrigger->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostTrigger->objectSize == mostTrigger->calculateObjectSize());
    BOOST_CHECK(mostTrigger->objectType == Vector::BLF::ObjectType::MOST_TRIGGER);
    /* ObjectHeader2 */
    BOOST_CHECK(mostTrigger->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostTrigger->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostTrigger->objectVersion == 0);
    BOOST_CHECK(mostTrigger->objectTimeStamp == 1303700000); // ns
    BOOST_CHECK(mostTrigger->originalTimeStamp == 0);
    /* MostTrigger */
    BOOST_CHECK(mostTrigger->channel == 1);
    // reserved
    BOOST_CHECK(mostTrigger->mode == 2); // synchronization slave
    BOOST_CHECK(mostTrigger->hw == 4); // VN2600/VN2610
    BOOST_CHECK(mostTrigger->previousTriggerValue == 1);
    BOOST_CHECK(mostTrigger->currentTriggerValue == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* FLEXRAY_CYCLE = 40 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRayV6StartCycleEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayV6StartCycleEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayV6StartCycleEvent * flexRayV6StartCycleEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_CYCLE);
    flexRayV6StartCycleEvent = static_cast<Vector::BLF::FlexRayV6StartCycleEvent *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* FLEXRAY_MESSAGE = 41 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRayV6Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayV6Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayV6Message * flexRayV6Message;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_MESSAGE);
    flexRayV6Message = static_cast<Vector::BLF::FlexRayV6Message *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_CHECKSUM_INFO = 42 */
BOOST_AUTO_TEST_CASE(LinChecksumInfo)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinChecksumInfo.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinChecksumInfo * linChecksumInfo;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_CHECKSUM_INFO);
    linChecksumInfo = static_cast<Vector::BLF::LinChecksumInfo *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linChecksumInfo->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linChecksumInfo->headerSize == linChecksumInfo->calculateHeaderSize());
    BOOST_CHECK(linChecksumInfo->headerVersion == 1);
    BOOST_CHECK(linChecksumInfo->objectSize == linChecksumInfo->calculateObjectSize());
    BOOST_CHECK(linChecksumInfo->objectType == Vector::BLF::ObjectType::LIN_CHECKSUM_INFO);
    /* ObjectHeader */
    BOOST_CHECK(linChecksumInfo->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linChecksumInfo->objectVersion == 0);
    BOOST_CHECK(linChecksumInfo->objectTimeStamp == 20100000); // ns
    /* LinChecksumInfo */
    BOOST_CHECK(linChecksumInfo->channel == 1);
    BOOST_CHECK(linChecksumInfo->id == 22);
    BOOST_CHECK(linChecksumInfo->checksumModel == 0); // classic
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SPIKE_EVENT = 43 */
#if 0
BOOST_AUTO_TEST_CASE(LinSpikeEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSpikeEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSpikeEvent * linSpikeEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SPIKE_EVENT);
    linSpikeEvent = static_cast<Vector::BLF::LinSpikeEvent *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* CAN_DRIVER_SYNC = 44 */
#if 0
BOOST_AUTO_TEST_CASE(CanDriverHwSync)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanDriverHwSync.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanDriverHwSync * canDriverHwSync;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_SYNC);
    canDriverHwSync = static_cast<Vector::BLF::CanDriverHwSync *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* FLEXRAY_STATUS = 45 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRayStatusEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayStatusEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayStatusEvent * flexRayStatusEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_STATUS);
    flexRayStatusEvent = static_cast<Vector::BLF::FlexRayStatusEvent *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* GPS_EVENT = 46 */
BOOST_AUTO_TEST_CASE(GpsEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/GpsEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::GpsEvent * gpsEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::GPS_EVENT);
    gpsEvent = static_cast<Vector::BLF::GpsEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(gpsEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(gpsEvent->headerSize == gpsEvent->calculateHeaderSize());
    BOOST_CHECK(gpsEvent->headerVersion == 1);
    BOOST_CHECK(gpsEvent->objectSize == gpsEvent->calculateObjectSize());
    BOOST_CHECK(gpsEvent->objectType == Vector::BLF::ObjectType::GPS_EVENT);
    /* ObjectHeader */
    BOOST_CHECK(gpsEvent->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(gpsEvent->objectVersion == 0);
    BOOST_CHECK(gpsEvent->objectTimeStamp == 2097603000); // ns
    /* GpsEvent */
    BOOST_CHECK(gpsEvent->flags == 0);
    BOOST_CHECK(gpsEvent->channel == 1);
    BOOST_CHECK(isEqual(gpsEvent->latitude, 48.825100));
    BOOST_CHECK(isEqual(gpsEvent->longitude, 9.091267));
    BOOST_CHECK(isEqual(gpsEvent->altitude, 325.399994));
    BOOST_CHECK(isEqual(gpsEvent->speed, 29.686400));
    BOOST_CHECK(isEqual(gpsEvent->course, 87.099998));
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* FR_ERROR = 47 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRayVFrError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayVFrError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrError * flexRayVFrError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_ERROR);
    flexRayVFrError = static_cast<Vector::BLF::FlexRayVFrError *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* FR_STATUS = 48 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRayVFrStatus)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayVFrStatus.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrStatus * flexRayVFrStatus;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_STATUS);
    flexRayVFrStatus = static_cast<Vector::BLF::FlexRayVFrStatus *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* FR_STARTCYCLE = 49 */
BOOST_AUTO_TEST_CASE(FlexRayVFrStartCycle)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayVFrStartCycle.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrStartCycle * flexRayVFrStartCycle;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);
    flexRayVFrStartCycle = static_cast<Vector::BLF::FlexRayVFrStartCycle *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(flexRayVFrStartCycle->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(flexRayVFrStartCycle->headerSize == flexRayVFrStartCycle->calculateHeaderSize());
    BOOST_CHECK(flexRayVFrStartCycle->headerVersion == 1);
    BOOST_CHECK(flexRayVFrStartCycle->objectSize == flexRayVFrStartCycle->calculateObjectSize());
    BOOST_CHECK(flexRayVFrStartCycle->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);
    /* ObjectHeader */
    BOOST_CHECK(flexRayVFrStartCycle->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(flexRayVFrStartCycle->objectVersion == 0);
    BOOST_CHECK(flexRayVFrStartCycle->objectTimeStamp == 41700000); // ns
    /* FlexRayVFrStartCycle */
    BOOST_CHECK(flexRayVFrStartCycle->channel == 0);
    BOOST_CHECK(flexRayVFrStartCycle->version == 2);
    BOOST_CHECK(flexRayVFrStartCycle->channelMask == 0); // reserved/invalid
    BOOST_CHECK(flexRayVFrStartCycle->dir == 0); // Rx
    BOOST_CHECK(flexRayVFrStartCycle->cycle == 0);
    BOOST_CHECK(flexRayVFrStartCycle->clientIndex == 0);
    BOOST_CHECK(flexRayVFrStartCycle->clusterNo == 0xffffffff);
    BOOST_CHECK(flexRayVFrStartCycle->nmSize == 2);
    BOOST_CHECK(flexRayVFrStartCycle->dataBytes[0] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->dataBytes[1] == 0);
    // reserved
    BOOST_CHECK(flexRayVFrStartCycle->tag == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[0] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[1] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[2] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[3] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[4] == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* FR_RCVMESSAGE = 50 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRayVFrReceiveMsg)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayVFrReceiveMsg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrReceiveMsg * flexRayVFrReceiveMsg;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE);
    flexRayVFrReceiveMsg = static_cast<Vector::BLF::FlexRayVFrReceiveMsg *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* REALTIMECLOCK = 51 */
#if 0
BOOST_AUTO_TEST_CASE(RealtimeClock)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/RealtimeClock.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::RealtimeClock * realtimeClock;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::REALTIMECLOCK);
    realtimeClock = static_cast<Vector::BLF::RealtimeClock *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* AVAILABLE2 = 52 */
/* AVAILABLE3 = 53 */

/* LIN_STATISTIC = 54 */
BOOST_AUTO_TEST_CASE(LinStatisticEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinStatisticEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinStatisticEvent * linStatisticEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_STATISTIC);
    linStatisticEvent = static_cast<Vector::BLF::LinStatisticEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linStatisticEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linStatisticEvent->headerSize == linStatisticEvent->calculateHeaderSize());
    BOOST_CHECK(linStatisticEvent->headerVersion == 1);
    BOOST_CHECK(linStatisticEvent->objectSize == linStatisticEvent->calculateObjectSize());
    BOOST_CHECK(linStatisticEvent->objectType == Vector::BLF::ObjectType::LIN_STATISTIC);
    /* ObjectHeader */
    BOOST_CHECK(linStatisticEvent->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linStatisticEvent->objectVersion == 0);
    BOOST_CHECK(linStatisticEvent->objectTimeStamp == 1999580000); // ns
    /* LinStatisticEvent */
    BOOST_CHECK(linStatisticEvent->channel == 1);
    BOOST_CHECK(isEqual(linStatisticEvent->busLoad, 0.903601));
    BOOST_CHECK(linStatisticEvent->burstsOverrun == 0);
    BOOST_CHECK(linStatisticEvent->framesSent == 0);
    BOOST_CHECK(linStatisticEvent->framesReceived == 73);
    BOOST_CHECK(linStatisticEvent->framesUnanswered == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* J1708_MESSAGE = 55 */
/* J1708_VIRTUAL_MSG = 56 */
#if 0
BOOST_AUTO_TEST_CASE(J1708Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/J1708Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::J1708Message * j1708Message;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::J1708_MESSAGE);
    j1708Message = static_cast<Vector::BLF::J1708Message *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_MESSAGE2 = 57 */
BOOST_AUTO_TEST_CASE(LinMessage2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinMessage2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinMessage2 * linMessage2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);
    linMessage2 = static_cast<Vector::BLF::LinMessage2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linMessage2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linMessage2->headerSize == linMessage2->calculateHeaderSize());
    BOOST_CHECK(linMessage2->headerVersion == 1);
    BOOST_CHECK(linMessage2->objectSize == linMessage2->calculateObjectSize());
    BOOST_CHECK(linMessage2->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);
    /* ObjectHeader */
    BOOST_CHECK(linMessage2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linMessage2->objectVersion == 1);
    BOOST_CHECK(linMessage2->objectTimeStamp == 73973000); // ns
    /* LinMessage2 */
    BOOST_CHECK(linMessage2->data[0] == 0x00);
    BOOST_CHECK(linMessage2->data[1] == 0xf0);
    BOOST_CHECK(linMessage2->data[2] == 0xf0);
    BOOST_CHECK(linMessage2->data[3] == 0xff);
    BOOST_CHECK(linMessage2->data[4] == 0xff);
    BOOST_CHECK(linMessage2->data[5] == 0xff);
    BOOST_CHECK(linMessage2->data[6] == 0xff);
    BOOST_CHECK(linMessage2->data[7] == 0xff);
    BOOST_CHECK(linMessage2->crc == 0x70);
    BOOST_CHECK(linMessage2->dir == 1); // Tx
    BOOST_CHECK(linMessage2->simulated == 1);
    BOOST_CHECK(linMessage2->isEtf == 0);
    BOOST_CHECK(linMessage2->etfAssocIndex == 0);
    BOOST_CHECK(linMessage2->etfAssocEtfId == 0xff);
    BOOST_CHECK(linMessage2->fsmId == 0xff);
    BOOST_CHECK(linMessage2->fsmState == 0xff);
    // reserved
    BOOST_CHECK(linMessage2->respBaudrate == 19231);
    BOOST_CHECK(isEqual(linMessage2->exactHeaderBaudrate, 19230.769231));
    BOOST_CHECK(linMessage2->earlyStopbitOffset == 26000);
    BOOST_CHECK(linMessage2->earlyStopbitOffsetResponse == 26000);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SND_ERROR2 = 58 */
BOOST_AUTO_TEST_CASE(LinSendError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSendError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSendError2 * linSendError2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SND_ERROR2);
    linSendError2 = static_cast<Vector::BLF::LinSendError2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSendError2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSendError2->headerSize == linSendError2->calculateHeaderSize());
    BOOST_CHECK(linSendError2->headerVersion == 1);
    BOOST_CHECK(linSendError2->objectSize == linSendError2->calculateObjectSize());
    BOOST_CHECK(linSendError2->objectType == Vector::BLF::ObjectType::LIN_SND_ERROR2);
    /* ObjectHeader */
    BOOST_CHECK(linSendError2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linSendError2->objectVersion == 1);
    BOOST_CHECK(linSendError2->objectTimeStamp == 424674000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linSendError2->sof == 416054000); // ns
    BOOST_CHECK(linSendError2->eventBaudrate == 19230);
    BOOST_CHECK(linSendError2->channel == 1);
    // reserved
    /* LinSynchFieldEvent */
    BOOST_CHECK(linSendError2->synchBreakLength == 937187);
    BOOST_CHECK(linSendError2->synchDelLength == 113250);
    /* LinMessageDescriptor */
    BOOST_CHECK(linSendError2->supplierId == 0);
    BOOST_CHECK(linSendError2->messageId == 0);
    BOOST_CHECK(linSendError2->nad == 0);
    BOOST_CHECK(linSendError2->id == 0x21); // 33
    BOOST_CHECK(linSendError2->dlc == 4);
    BOOST_CHECK(linSendError2->checksumModel == 1); // enhanced
    /* LinSendError2 */
    BOOST_CHECK(linSendError2->eoh == 418122000); // ns
    BOOST_CHECK(linSendError2->isEtf == 0);
    BOOST_CHECK(linSendError2->fsmId == 0xff);
    BOOST_CHECK(linSendError2->fsmState == 0);
    // reserved
    BOOST_CHECK(isEqual(linSendError2->exactHeaderBaudrate, 19230.769231));
    BOOST_CHECK(linSendError2->earlyStopbitOffset == 26000);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SYN_ERROR2 = 59 */
BOOST_AUTO_TEST_CASE(LinSyncError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSyncError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSyncError2 * linSyncError2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SYN_ERROR2);
    linSyncError2 = static_cast<Vector::BLF::LinSyncError2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSyncError2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSyncError2->headerSize == linSyncError2->calculateHeaderSize());
    BOOST_CHECK(linSyncError2->headerVersion == 1);
    BOOST_CHECK(linSyncError2->objectSize == linSyncError2->calculateObjectSize());
    BOOST_CHECK(linSyncError2->objectType == Vector::BLF::ObjectType::LIN_SYN_ERROR2);
    /* ObjectHeader */
    BOOST_CHECK(linSyncError2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linSyncError2->objectVersion == 0);
    BOOST_CHECK(linSyncError2->objectTimeStamp == 2022336000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linSyncError2->sof == 2021077000); // ns
    BOOST_CHECK(linSyncError2->eventBaudrate == 19230);
    BOOST_CHECK(linSyncError2->channel == 2);
    // reserved
    /* LinSynchFieldEvent */
    BOOST_CHECK(linSyncError2->synchBreakLength == 937125);
    BOOST_CHECK(linSyncError2->synchDelLength == 113312);
    /* LinSyncError2 */
    BOOST_CHECK(linSyncError2->timeDiff[0] == 208);
    BOOST_CHECK(linSyncError2->timeDiff[1] == 0);
    BOOST_CHECK(linSyncError2->timeDiff[2] == 0);
    BOOST_CHECK(linSyncError2->timeDiff[3] == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_CRC_ERROR2 = 60 */
#if 0
BOOST_AUTO_TEST_CASE(LinCrcError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinCrcError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinCrcError2 * linCrcError2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_CRC_ERROR2);
    linCrcError2 = static_cast<Vector::BLF::LinCrcError2 *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_RCV_ERROR2 = 61 */
BOOST_AUTO_TEST_CASE(LinReceiveError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinReceiveError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinReceiveError2 * linReceiveError2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR2);
    linReceiveError2 = static_cast<Vector::BLF::LinReceiveError2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linReceiveError2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linReceiveError2->headerSize == linReceiveError2->calculateHeaderSize());
    BOOST_CHECK(linReceiveError2->headerVersion == 1);
    BOOST_CHECK(linReceiveError2->objectSize == linReceiveError2->calculateObjectSize());
    BOOST_CHECK(linReceiveError2->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR2);
    /* ObjectHeader */
    BOOST_CHECK(linReceiveError2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linReceiveError2->objectVersion == 1);
    BOOST_CHECK(linReceiveError2->objectTimeStamp == 554673000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linReceiveError2->sof == 546052000); // ns
    BOOST_CHECK(linReceiveError2->eventBaudrate == 19230);
    BOOST_CHECK(linReceiveError2->channel == 1);
    // reserved
    /* LinSynchFieldEvent */
    BOOST_CHECK(linReceiveError2->synchBreakLength == 937187);
    BOOST_CHECK(linReceiveError2->synchDelLength == 112437);
    /* LinReceiveError2 */
    BOOST_CHECK(linReceiveError2->supplierId == 0);
    BOOST_CHECK(linReceiveError2->messageId == 0);
    BOOST_CHECK(linReceiveError2->nad == 0);
    BOOST_CHECK(linReceiveError2->id == 0x33);
    BOOST_CHECK(linReceiveError2->dlc == 8);
    BOOST_CHECK(linReceiveError2->checksumModel == 0xff);
    BOOST_CHECK(linReceiveError2->databyteTimestamps[0] == 548121000);
    BOOST_CHECK(linReceiveError2->databyteTimestamps[1] == 548644000);
    BOOST_CHECK(linReceiveError2->databyteTimestamps[2] == 549167000);
    BOOST_CHECK(linReceiveError2->databyteTimestamps[3] == 549690000);
    BOOST_CHECK(linReceiveError2->databyteTimestamps[4] == 550213000);
    BOOST_CHECK(linReceiveError2->databyteTimestamps[5] == 550736000);
    BOOST_CHECK(linReceiveError2->databyteTimestamps[6] == 551259000);
    BOOST_CHECK(linReceiveError2->databyteTimestamps[7] == 551782000);
    BOOST_CHECK(linReceiveError2->databyteTimestamps[8] == 552305000);
    BOOST_CHECK(linReceiveError2->data[0] == 0x05);
    BOOST_CHECK(linReceiveError2->data[1] == 0x00);
    BOOST_CHECK(linReceiveError2->data[2] == 0x00);
    BOOST_CHECK(linReceiveError2->data[3] == 0x00);
    BOOST_CHECK(linReceiveError2->data[4] == 0x00);
    BOOST_CHECK(linReceiveError2->data[5] == 0xff);
    BOOST_CHECK(linReceiveError2->data[6] == 0xff);
    BOOST_CHECK(linReceiveError2->data[7] == 0xff);
    BOOST_CHECK(linReceiveError2->fsmId == 0xff);
    BOOST_CHECK(linReceiveError2->fsmState == 0xff);
    BOOST_CHECK(linReceiveError2->stateReason == 12);
    BOOST_CHECK(linReceiveError2->offendingByte == 0);
    BOOST_CHECK(linReceiveError2->shortError == 0);
    BOOST_CHECK(linReceiveError2->timeoutDuringDlcDetection == 0);
    BOOST_CHECK(linReceiveError2->isEtf == 0);
    BOOST_CHECK(linReceiveError2->hasDatabytes == 1);
    BOOST_CHECK(linReceiveError2->respBaudrate == 19231);
    // reserved
    BOOST_CHECK(isEqual(linReceiveError2->exactHeaderBaudrate, 19230.769231));
    BOOST_CHECK(linReceiveError2->earlyStopbitOffset == 26000);
    BOOST_CHECK(linReceiveError2->earlyStopbitOffsetResponse == 26000);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_WAKEUP2 = 62 */
BOOST_AUTO_TEST_CASE(LinWakeupEvent2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinWakeupEvent2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinWakeupEvent2 * linWakeupEvent2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_WAKEUP2);
    linWakeupEvent2 = static_cast<Vector::BLF::LinWakeupEvent2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linWakeupEvent2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linWakeupEvent2->headerSize == linWakeupEvent2->calculateHeaderSize());
    BOOST_CHECK(linWakeupEvent2->headerVersion == 1);
    BOOST_CHECK(linWakeupEvent2->objectSize == linWakeupEvent2->calculateObjectSize());
    BOOST_CHECK(linWakeupEvent2->objectType == Vector::BLF::ObjectType::LIN_WAKEUP2);
    /* ObjectHeader */
    BOOST_CHECK(linWakeupEvent2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linWakeupEvent2->objectVersion == 0);
    BOOST_CHECK(linWakeupEvent2->objectTimeStamp == 2318672000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linWakeupEvent2->sof == 2317671000); // ns
    BOOST_CHECK(linWakeupEvent2->eventBaudrate == 19230);
    BOOST_CHECK(linWakeupEvent2->channel == 1);
    // reserved
    /* LinWakeupEvent2 */
    BOOST_CHECK(linWakeupEvent2->lengthInfo == 0); // OK
    BOOST_CHECK(linWakeupEvent2->signal == 0);
    BOOST_CHECK(linWakeupEvent2->external == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SPIKE_EVENT2 = 63 */
BOOST_AUTO_TEST_CASE(LinSpikeEvent2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSpikeEvent2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSpikeEvent2 * linSpikeEvent2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SPIKE_EVENT2);
    linSpikeEvent2 = static_cast<Vector::BLF::LinSpikeEvent2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSpikeEvent2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSpikeEvent2->headerSize == linSpikeEvent2->calculateHeaderSize());
    BOOST_CHECK(linSpikeEvent2->headerVersion == 1);
    BOOST_CHECK(linSpikeEvent2->objectSize == linSpikeEvent2->calculateObjectSize());
    BOOST_CHECK(linSpikeEvent2->objectType == Vector::BLF::ObjectType::LIN_SPIKE_EVENT2);
    /* ObjectHeader */
    BOOST_CHECK(linSpikeEvent2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linSpikeEvent2->objectVersion == 0);
    BOOST_CHECK(linSpikeEvent2->objectTimeStamp == 5990958000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linSpikeEvent2->sof == 5990902000); // ns
    BOOST_CHECK(linSpikeEvent2->eventBaudrate == 9615);
    BOOST_CHECK(linSpikeEvent2->channel == 2);
    /* LinSpikeEvent2 */
    BOOST_CHECK(linSpikeEvent2->width == 56);
    BOOST_CHECK(linSpikeEvent2->internal == 0); // real event
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_LONG_DOM_SIG = 64 */
#if 0
BOOST_AUTO_TEST_CASE(LinLongDomSignalEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinLongDomSignalEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinLongDomSignalEvent * linLongDomSignalEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG);
    linLongDomSignalEvent = static_cast<Vector::BLF::LinLongDomSignalEvent *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* APP_TEXT = 65 */
#if 0
BOOST_AUTO_TEST_CASE(AppText)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/AppText.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::AppText * appText;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::APP_TEXT);
    appText = static_cast<Vector::BLF::AppText *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* FR_RCVMESSAGE_EX = 66 */
BOOST_AUTO_TEST_CASE(FlexRayVFrReceiveMsgEx)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayVFrReceiveMsgEx.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrReceiveMsgEx * flexRayVFrReceiveMsgEx;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    flexRayVFrReceiveMsgEx = static_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerSize == flexRayVFrReceiveMsgEx->calculateHeaderSize());
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerVersion == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectSize == flexRayVFrReceiveMsgEx->calculateObjectSize());
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    /* ObjectHeader */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectVersion == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectTimeStamp == 42000000); // ns
    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channel == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->version == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channelMask == 1); // FlexRay Channel A
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dir == 0); // Rx
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clientIndex == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clusterNo == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameId == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc1 == 151);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc2 == 151);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->byteCount == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataCount == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->cycle == 25);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->tag == 2);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->data == 0x00d0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameFlags == 0x06);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->appParameter == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameCrc == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameLengthNs == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameId1 == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->pduOffset == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->blfLogMask == 0);
    // reserved
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x00] == 21);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x01] == 87);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x02] == 22);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x03] == 148);
    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    flexRayVFrReceiveMsgEx = static_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerSize == flexRayVFrReceiveMsgEx->calculateHeaderSize());
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerVersion == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectSize == flexRayVFrReceiveMsgEx->calculateObjectSize());
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    /* ObjectHeader */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectVersion == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectTimeStamp == 42600000); // ns
    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channel == 2);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->version == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channelMask == 2); // FlexRay Channel B
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dir == 0); // Rx
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clientIndex == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clusterNo == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameId == 13);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc1 == 620);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc2 == 620);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->byteCount == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataCount == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->cycle == 25);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->tag == 2);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->data == 0x0180);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameFlags == 0x02);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->appParameter == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameCrc == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameLengthNs == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameId1 == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->pduOffset == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->blfLogMask == 0);
    // reserved
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x00] == 2);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x01] == 89);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x02] == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x03] == 13);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_STATISTICEX = 67 */
BOOST_AUTO_TEST_CASE(MostStatisticEx)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStatisticEx.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostStatisticEx * mostStatisticEx;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_STATISTICEX);
    mostStatisticEx = static_cast<Vector::BLF::MostStatisticEx *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostStatisticEx->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostStatisticEx->headerSize == mostStatisticEx->calculateHeaderSize());
    BOOST_CHECK(mostStatisticEx->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostStatisticEx->objectSize == mostStatisticEx->calculateObjectSize());
    BOOST_CHECK(mostStatisticEx->objectType == Vector::BLF::ObjectType::MOST_STATISTICEX);
    /* ObjectHeader2 */
    BOOST_CHECK(mostStatisticEx->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostStatisticEx->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostStatisticEx->objectVersion == 0);
    BOOST_CHECK(mostStatisticEx->objectTimeStamp == 2024742000); // ns
    BOOST_CHECK(mostStatisticEx->originalTimeStamp == 0);
    /* MostStatisticEx */
    BOOST_CHECK(mostStatisticEx->channel == 2);
    // reserved
    BOOST_CHECK(mostStatisticEx->codingErrors == 0x000006);
    BOOST_CHECK(mostStatisticEx->frameCounter == 0x00A395);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_TXLIGHT = 68 */
BOOST_AUTO_TEST_CASE(MostTxLight)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostTxLight.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostTxLight * mostTxLight;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_TXLIGHT);
    mostTxLight = static_cast<Vector::BLF::MostTxLight *>(ohb);
    BOOST_CHECK(mostTxLight->channel == 1);
    BOOST_CHECK(mostTxLight->state == 1); // enable
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_ALLOCTAB = 69 */
BOOST_AUTO_TEST_CASE(MostAllocTab)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostAllocTab.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostAllocTab * mostAllocTab;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ALLOCTAB);
    mostAllocTab = static_cast<Vector::BLF::MostAllocTab *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostAllocTab->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostAllocTab->headerSize == mostAllocTab->calculateHeaderSize());
    BOOST_CHECK(mostAllocTab->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostAllocTab->objectSize == mostAllocTab->calculateObjectSize());
    BOOST_CHECK(mostAllocTab->objectType == Vector::BLF::ObjectType::MOST_ALLOCTAB);
    /* ObjectHeader2 */
    BOOST_CHECK(mostAllocTab->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostAllocTab->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostAllocTab->objectVersion == 0);
    BOOST_CHECK(mostAllocTab->objectTimeStamp == 32775000); // ns
    BOOST_CHECK(mostAllocTab->originalTimeStamp == 0);
    /* MostAllocTab */
    BOOST_CHECK(mostAllocTab->channel == 2);
    BOOST_CHECK(mostAllocTab->length == 0x3C);
    // reserved
    BOOST_CHECK(mostAllocTab->tableData[0x00] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x01] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x02] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x03] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x04] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x05] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x06] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x07] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x08] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x09] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x0a] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x0b] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x0c] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x0d] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x0e] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x0f] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x10] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x11] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x12] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x13] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x14] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x15] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x16] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x17] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x18] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x19] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x1a] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x1b] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x1c] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x1d] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x1e] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x1f] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x20] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x21] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x22] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x23] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x24] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x25] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x26] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x27] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x28] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x29] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x2a] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x2b] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x2c] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x2d] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x2e] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x2f] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x30] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x31] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x32] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x33] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x34] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x35] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x36] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x37] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x38] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x39] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x3a] == 0x70);
    BOOST_CHECK(mostAllocTab->tableData[0x3b] == 0x70);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_STRESS = 70 */
BOOST_AUTO_TEST_CASE(MostStress)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStress.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostStress * mostStress;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_STRESS);
    mostStress = static_cast<Vector::BLF::MostStress *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostStress->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostStress->headerSize == mostStress->calculateHeaderSize());
    BOOST_CHECK(mostStress->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostStress->objectSize == mostStress->calculateObjectSize());
    BOOST_CHECK(mostStress->objectType == Vector::BLF::ObjectType::MOST_STRESS);
    /* ObjectHeader2 */
    BOOST_CHECK(mostStress->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostStress->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostStress->objectVersion == 0);
    BOOST_CHECK(mostStress->objectTimeStamp == 1793083000); // ns
    BOOST_CHECK(mostStress->originalTimeStamp == 0);
    /* MostStress */
    BOOST_CHECK(mostStress->channel == 1);
    BOOST_CHECK(mostStress->state == 1); // started
    BOOST_CHECK(mostStress->mode == 2); // Lock
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* ETHERNET_FRAME = 71 */
BOOST_AUTO_TEST_CASE(EthernetFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EthernetFrame * ethernetFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);
    ethernetFrame = static_cast<Vector::BLF::EthernetFrame *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(ethernetFrame->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(ethernetFrame->headerSize == ethernetFrame->calculateHeaderSize());
    BOOST_CHECK(ethernetFrame->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(ethernetFrame->objectSize == ethernetFrame->calculateObjectSize());
    BOOST_CHECK(ethernetFrame->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);
    /* ObjectHeader */
    BOOST_CHECK(ethernetFrame->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(ethernetFrame->objectVersion == 0);
    BOOST_CHECK(ethernetFrame->objectTimeStamp == 0); // ns
    /* EthernetFrame */
    BOOST_CHECK(ethernetFrame->sourceAddress[0] == 0x40);
    BOOST_CHECK(ethernetFrame->sourceAddress[1] == 0x00);
    BOOST_CHECK(ethernetFrame->sourceAddress[2] == 0x00);
    BOOST_CHECK(ethernetFrame->sourceAddress[3] == 0x00);
    BOOST_CHECK(ethernetFrame->sourceAddress[4] == 0x00);
    BOOST_CHECK(ethernetFrame->sourceAddress[5] == 0x04);
    BOOST_CHECK(ethernetFrame->channel == 2);
    BOOST_CHECK(ethernetFrame->destinationAddress[0] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[1] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[2] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[3] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[4] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[5] == 0xff);
    BOOST_CHECK(ethernetFrame->dir == 1);
    BOOST_CHECK(ethernetFrame->type == 0x0806);
    BOOST_CHECK(ethernetFrame->tpid == 0x0000);
    BOOST_CHECK(ethernetFrame->tci == 0x0000);
    BOOST_CHECK(ethernetFrame->payLoadLength == 0x2e);
    // reserved
    BOOST_CHECK(ethernetFrame->payLoad[0x00] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x01] == 0x01);
    BOOST_CHECK(ethernetFrame->payLoad[0x02] == 0x08);
    BOOST_CHECK(ethernetFrame->payLoad[0x03] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x04] == 0x06);
    BOOST_CHECK(ethernetFrame->payLoad[0x05] == 0x04);
    BOOST_CHECK(ethernetFrame->payLoad[0x06] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x07] == 0x01);
    BOOST_CHECK(ethernetFrame->payLoad[0x08] == 0x40);
    BOOST_CHECK(ethernetFrame->payLoad[0x09] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x0a] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x0b] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x0c] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x0d] == 0x04);
    BOOST_CHECK(ethernetFrame->payLoad[0x0e] == 0xc0);
    BOOST_CHECK(ethernetFrame->payLoad[0x0f] == 0xa8);
    BOOST_CHECK(ethernetFrame->payLoad[0x10] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x11] == 0x01);
    BOOST_CHECK(ethernetFrame->payLoad[0x12] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x13] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x14] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x15] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x16] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x17] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x18] == 0xc0);
    BOOST_CHECK(ethernetFrame->payLoad[0x19] == 0xa8);
    BOOST_CHECK(ethernetFrame->payLoad[0x1a] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x1b] == 0x01);
    BOOST_CHECK(ethernetFrame->payLoad[0x1c] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x1d] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x1e] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x1f] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x20] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x21] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x22] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x23] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x24] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x25] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x26] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x27] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x28] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x29] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x2a] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x2b] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x2c] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x2d] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* SYS_VARIABLE = 72 */
BOOST_AUTO_TEST_CASE(SystemVariable)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/SystemVariable.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::SystemVariable * systemVariable;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    systemVariable = static_cast<Vector::BLF::SystemVariable *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(systemVariable->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(systemVariable->headerSize == systemVariable->calculateHeaderSize());
    BOOST_CHECK(systemVariable->headerVersion == 1);
    BOOST_CHECK(systemVariable->objectSize == systemVariable->calculateObjectSize());
    BOOST_CHECK(systemVariable->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    /* ObjectHeader */
    BOOST_CHECK(systemVariable->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(systemVariable->objectVersion == 0);
    BOOST_CHECK(systemVariable->objectTimeStamp == 20400000000); // ns
    /* SystemVariable */
    BOOST_CHECK(systemVariable->type == Vector::BLF::SystemVariable::Type::Long);
    // reserved
    BOOST_CHECK(systemVariable->nameLength == 21);
    BOOST_CHECK(systemVariable->dataLength == 4);
    // reserved
    BOOST_CHECK(systemVariable->name == "::WiperSystem::Active");
    BOOST_CHECK(systemVariable->data[0] == 0x06);
    BOOST_CHECK(systemVariable->data[1] == 0x00);
    BOOST_CHECK(systemVariable->data[2] == 0x00);
    BOOST_CHECK(systemVariable->data[3] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_ERROR_EXT = 73 */
BOOST_AUTO_TEST_CASE(CanErrorFrameExt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanErrorFrameExt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanErrorFrameExt * canErrorFrameExt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);
    canErrorFrameExt = static_cast<Vector::BLF::CanErrorFrameExt *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canErrorFrameExt->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canErrorFrameExt->headerSize == canErrorFrameExt->calculateHeaderSize());
    BOOST_CHECK(canErrorFrameExt->headerVersion == 1);
    BOOST_CHECK(canErrorFrameExt->objectSize == canErrorFrameExt->calculateObjectSize());
    BOOST_CHECK(canErrorFrameExt->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);
    /* ObjectHeader */
    BOOST_CHECK(canErrorFrameExt->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(canErrorFrameExt->objectVersion == 0);
    BOOST_CHECK(canErrorFrameExt->objectTimeStamp == 1592186000); // ns
    /* CanErrorFrameExt */
    BOOST_CHECK(canErrorFrameExt->channel == 1);
    BOOST_CHECK(canErrorFrameExt->length == 6);
    BOOST_CHECK(canErrorFrameExt->flags == 1); // SJA 1000
    BOOST_CHECK(canErrorFrameExt->ecc == 0xa2);
    BOOST_CHECK(canErrorFrameExt->position == 0);
    BOOST_CHECK(canErrorFrameExt->dlc == 0);
    // reserved
    BOOST_CHECK(canErrorFrameExt->frameLengthInNs == 0);
    BOOST_CHECK(canErrorFrameExt->id == 0xffffffff);
    BOOST_CHECK(canErrorFrameExt->flagsExt == 0x20a2);
    // reserved
    //BOOST_CHECK(canErrorFrameExt->data[0] == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_DRIVER_ERROR_EXT = 74 */
#if 0
BOOST_AUTO_TEST_CASE(CanDriverErrorExt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanDriverErrorExt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanDriverErrorExt * canDriverErrorExt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT);
    canDriverErrorExt = static_cast<Vector::BLF::CanDriverErrorExt *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_LONG_DOM_SIG2 = 75 */
BOOST_AUTO_TEST_CASE(LinLongDomSignalEvent2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinLongDomSignalEvent2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinLongDomSignalEvent2 * linLongDomSignalEvent2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    linLongDomSignalEvent2 = static_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linLongDomSignalEvent2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linLongDomSignalEvent2->headerSize == linLongDomSignalEvent2->calculateHeaderSize());
    BOOST_CHECK(linLongDomSignalEvent2->headerVersion == 1);
    BOOST_CHECK(linLongDomSignalEvent2->objectSize == linLongDomSignalEvent2->calculateObjectSize());
    BOOST_CHECK(linLongDomSignalEvent2->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    /* ObjectHeader */
    BOOST_CHECK(linLongDomSignalEvent2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linLongDomSignalEvent2->objectVersion == 0);
    BOOST_CHECK(linLongDomSignalEvent2->objectTimeStamp == 8976802000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linLongDomSignalEvent2->sof == 8971798000); // ns
    BOOST_CHECK(linLongDomSignalEvent2->eventBaudrate == 9615);
    BOOST_CHECK(linLongDomSignalEvent2->channel == 1);
    // reserved
    /* LinLongDomSignalEvent2 */
    BOOST_CHECK(linLongDomSignalEvent2->type == 0); // Signal just detected
    // reserved
    BOOST_CHECK(linLongDomSignalEvent2->length == 5003000); // us
    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    linLongDomSignalEvent2 = static_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linLongDomSignalEvent2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linLongDomSignalEvent2->headerSize == linLongDomSignalEvent2->calculateHeaderSize());
    BOOST_CHECK(linLongDomSignalEvent2->headerVersion == 1);
    BOOST_CHECK(linLongDomSignalEvent2->objectSize == linLongDomSignalEvent2->calculateObjectSize());
    BOOST_CHECK(linLongDomSignalEvent2->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    /* ObjectHeader */
    BOOST_CHECK(linLongDomSignalEvent2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linLongDomSignalEvent2->objectVersion == 0);
    BOOST_CHECK(linLongDomSignalEvent2->objectTimeStamp == 8977000000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linLongDomSignalEvent2->sof == 8971798000); // ns
    BOOST_CHECK(linLongDomSignalEvent2->eventBaudrate == 9615);
    BOOST_CHECK(linLongDomSignalEvent2->channel == 1);
    // reserved
    /* LinLongDomSignalEvent2 */
    BOOST_CHECK(linLongDomSignalEvent2->type == 2); // Signal continuation
    // reserved
    BOOST_CHECK(linLongDomSignalEvent2->length == 5201000); // us
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_150_MESSAGE = 76 */
BOOST_AUTO_TEST_CASE(Most150Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150Message * most150Message;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE);
    most150Message = static_cast<Vector::BLF::Most150Message *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150Message->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150Message->headerSize == most150Message->calculateHeaderSize());
    BOOST_CHECK(most150Message->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150Message->objectSize == most150Message->calculateObjectSize());
    BOOST_CHECK(most150Message->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE);
    /* ObjectHeader2 */
    BOOST_CHECK(most150Message->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150Message->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150Message->objectVersion == 0);
    BOOST_CHECK(most150Message->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most150Message->originalTimeStamp == 0);
    /* Most150Message */
    BOOST_CHECK(most150Message->channel == 1);
    BOOST_CHECK(most150Message->dir == 1); // Tx
    // reserved
    BOOST_CHECK(most150Message->sourceAdr == 0x0172);
    BOOST_CHECK(most150Message->destAdr == 0x03C8);
    BOOST_CHECK(most150Message->transferType == 1); // Node
    BOOST_CHECK(most150Message->state == 0x02);
    BOOST_CHECK(most150Message->ackNack == 0x11); // Ack
    // reserved
    BOOST_CHECK(most150Message->crc == 0xAABB);
    BOOST_CHECK(most150Message->pAck == 0x22);
    BOOST_CHECK(most150Message->cAck == 0x44);
    BOOST_CHECK(most150Message->priority == 1);
    BOOST_CHECK(most150Message->pIndex == 0x33);
    BOOST_CHECK(most150Message->msgLen == 8);
    // reserved
    BOOST_CHECK(most150Message->msg[0] == 0x11);
    BOOST_CHECK(most150Message->msg[1] == 0x22);
    BOOST_CHECK(most150Message->msg[2] == 0x33);
    BOOST_CHECK(most150Message->msg[3] == 0x34);
    BOOST_CHECK(most150Message->msg[4] == 0x00);
    BOOST_CHECK(most150Message->msg[5] == 0x02);
    BOOST_CHECK(most150Message->msg[6] == 0x11);
    BOOST_CHECK(most150Message->msg[7] == 0x22);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_150_PKT = 77 */
BOOST_AUTO_TEST_CASE(Most150Pkt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150Pkt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150Pkt * most150Pkt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_PKT);
    most150Pkt = static_cast<Vector::BLF::Most150Pkt *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150Pkt->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150Pkt->headerSize == most150Pkt->calculateHeaderSize());
    BOOST_CHECK(most150Pkt->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150Pkt->objectSize == most150Pkt->calculateObjectSize());
    BOOST_CHECK(most150Pkt->objectType == Vector::BLF::ObjectType::MOST_150_PKT);
    /* ObjectHeader2 */
    BOOST_CHECK(most150Pkt->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150Pkt->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150Pkt->objectVersion == 0);
    BOOST_CHECK(most150Pkt->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most150Pkt->originalTimeStamp == 0);
    /* Most150Pkt */
    BOOST_CHECK(most150Pkt->channel == 1);
    BOOST_CHECK(most150Pkt->dir == 1); // Tx
    // reserved
    BOOST_CHECK(most150Pkt->sourceAdr == 0x0172);
    BOOST_CHECK(most150Pkt->destAdr == 0x03C8);
    BOOST_CHECK(most150Pkt->transferType == 1); // Node
    BOOST_CHECK(most150Pkt->state == 0x02);
    BOOST_CHECK(most150Pkt->ackNack == 0x11); // Ack|Valid
    // reserved
    BOOST_CHECK(most150Pkt->crc == 0xAABB);
    BOOST_CHECK(most150Pkt->pAck == 0x00); // No Response
    BOOST_CHECK(most150Pkt->cAck == 0x44); // OK
    BOOST_CHECK(most150Pkt->priority == 0x00);
    BOOST_CHECK(most150Pkt->pIndex == 0x33);
    BOOST_CHECK(most150Pkt->pktDataLength == 8);
    // reserved
    BOOST_CHECK(most150Pkt->pktData[0] == 0x11);
    BOOST_CHECK(most150Pkt->pktData[1] == 0x22);
    BOOST_CHECK(most150Pkt->pktData[2] == 0x33);
    BOOST_CHECK(most150Pkt->pktData[3] == 0x34);
    BOOST_CHECK(most150Pkt->pktData[4] == 0x00);
    BOOST_CHECK(most150Pkt->pktData[5] == 0x02);
    BOOST_CHECK(most150Pkt->pktData[6] == 0x11);
    BOOST_CHECK(most150Pkt->pktData[7] == 0x22);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_ETHERNET_PKT = 78 */
BOOST_AUTO_TEST_CASE(MostEthernetPkt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEthernetPkt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostEthernetPkt * mostEthernetPkt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT);
    mostEthernetPkt = static_cast<Vector::BLF::MostEthernetPkt *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostEthernetPkt->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostEthernetPkt->headerSize == mostEthernetPkt->calculateHeaderSize());
    BOOST_CHECK(mostEthernetPkt->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostEthernetPkt->objectSize == mostEthernetPkt->calculateObjectSize());
    BOOST_CHECK(mostEthernetPkt->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT);
    /* ObjectHeader2 */
    BOOST_CHECK(mostEthernetPkt->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostEthernetPkt->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostEthernetPkt->objectVersion == 0);
    BOOST_CHECK(mostEthernetPkt->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(mostEthernetPkt->originalTimeStamp == 0);
    /* MostEthernetPkt */
    BOOST_CHECK(mostEthernetPkt->channel == 1);
    BOOST_CHECK(mostEthernetPkt->dir == 1); // Tx
    // reserved
    BOOST_CHECK(mostEthernetPkt->sourceMacAdr == 0x010203040506);
    BOOST_CHECK(mostEthernetPkt->destMacAdr == 0x112233445566);
    BOOST_CHECK(mostEthernetPkt->transferType == 1); // Node
    BOOST_CHECK(mostEthernetPkt->state == 0x02); // ???
    BOOST_CHECK(mostEthernetPkt->ackNack == 0x11); // Valid | Ack
    // reserved
    BOOST_CHECK(mostEthernetPkt->crc == 0xAABBCCDD);
    BOOST_CHECK(mostEthernetPkt->pAck == 0x22);
    BOOST_CHECK(mostEthernetPkt->cAck == 0x44);
    // reserved
    BOOST_CHECK(mostEthernetPkt->pktDataLength == 8);
    // reserved
    BOOST_CHECK(mostEthernetPkt->pktData[0] == 0x11);
    BOOST_CHECK(mostEthernetPkt->pktData[1] == 0x22);
    BOOST_CHECK(mostEthernetPkt->pktData[2] == 0x33);
    BOOST_CHECK(mostEthernetPkt->pktData[3] == 0x34);
    BOOST_CHECK(mostEthernetPkt->pktData[4] == 0x00);
    BOOST_CHECK(mostEthernetPkt->pktData[5] == 0x02);
    BOOST_CHECK(mostEthernetPkt->pktData[6] == 0x11);
    BOOST_CHECK(mostEthernetPkt->pktData[7] == 0x22);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_150_MESSAGE_FRAGMENT = 79 */
BOOST_AUTO_TEST_CASE(Most150MessageFragment)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150MessageFragment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150MessageFragment * most150MessageFragment;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE_FRAGMENT);
    most150MessageFragment = static_cast<Vector::BLF::Most150MessageFragment *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150MessageFragment->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150MessageFragment->headerSize == most150MessageFragment->calculateHeaderSize());
    BOOST_CHECK(most150MessageFragment->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150MessageFragment->objectSize == most150MessageFragment->calculateObjectSize());
    BOOST_CHECK(most150MessageFragment->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE_FRAGMENT);
    /* ObjectHeader2 */
    BOOST_CHECK(most150MessageFragment->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150MessageFragment->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150MessageFragment->objectVersion == 0);
    BOOST_CHECK(most150MessageFragment->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most150MessageFragment->originalTimeStamp == 0);
    /* Most150MessageFragment */
    BOOST_CHECK(most150MessageFragment->channel == 1);
    // reserved
    BOOST_CHECK(most150MessageFragment->ackNack == 0x11); // NoResp | NAck
    BOOST_CHECK(most150MessageFragment->validMask == 0x01020304);
    BOOST_CHECK(most150MessageFragment->sourceAdr == 0x0172);
    BOOST_CHECK(most150MessageFragment->destAdr == 0x03C8);
    BOOST_CHECK(most150MessageFragment->pAck == 0x22);
    BOOST_CHECK(most150MessageFragment->cAck == 0x44);
    BOOST_CHECK(most150MessageFragment->priority == 1);
    BOOST_CHECK(most150MessageFragment->pIndex == 0x33);
    BOOST_CHECK(most150MessageFragment->crc == 0xAABB);
    BOOST_CHECK(most150MessageFragment->dataLen == 6);
    BOOST_CHECK(most150MessageFragment->dataLenAnnounced == 0x0210);
    BOOST_CHECK(most150MessageFragment->firstDataLen == 6);
    // reserved
    BOOST_CHECK(most150MessageFragment->firstData[0] == 0x01);
    BOOST_CHECK(most150MessageFragment->firstData[1] == 0x02);
    BOOST_CHECK(most150MessageFragment->firstData[2] == 0x03);
    BOOST_CHECK(most150MessageFragment->firstData[3] == 0x04);
    BOOST_CHECK(most150MessageFragment->firstData[4] == 0x05);
    BOOST_CHECK(most150MessageFragment->firstData[5] == 0x06);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_150_PKT_FRAGMENT = 80 */
BOOST_AUTO_TEST_CASE(Most150PktFragment)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150PktFragment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150PktFragment * most150PktFragment;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_PKT_FRAGMENT);
    most150PktFragment = static_cast<Vector::BLF::Most150PktFragment *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150PktFragment->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150PktFragment->headerSize == most150PktFragment->calculateHeaderSize());
    BOOST_CHECK(most150PktFragment->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150PktFragment->objectSize == most150PktFragment->calculateObjectSize());
    BOOST_CHECK(most150PktFragment->objectType == Vector::BLF::ObjectType::MOST_150_PKT_FRAGMENT);
    /* ObjectHeader2 */
    BOOST_CHECK(most150PktFragment->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150PktFragment->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150PktFragment->objectVersion == 0);
    BOOST_CHECK(most150PktFragment->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most150PktFragment->originalTimeStamp == 0);
    /* Most150PktFragment */
    BOOST_CHECK(most150PktFragment->channel == 1);
    // reserved
    BOOST_CHECK(most150PktFragment->ackNack == 0x11); // NoResp | NAck
    BOOST_CHECK(most150PktFragment->validMask == 0x01020304);
    BOOST_CHECK(most150PktFragment->sourceAdr == 0x0172);
    BOOST_CHECK(most150PktFragment->destAdr == 0x03C8);
    BOOST_CHECK(most150PktFragment->pAck == 0x22);
    BOOST_CHECK(most150PktFragment->cAck == 0x44);
    BOOST_CHECK(most150PktFragment->priority == 1);
    BOOST_CHECK(most150PktFragment->pIndex == 0x33);
    BOOST_CHECK(most150PktFragment->crc == 0xAABB);
    BOOST_CHECK(most150PktFragment->dataLen == 6);
    BOOST_CHECK(most150PktFragment->dataLenAnnounced == 0x0210);
    BOOST_CHECK(most150PktFragment->firstDataLen == 6);
    // reserved
    BOOST_CHECK(most150PktFragment->firstData[0] == 0x01);
    BOOST_CHECK(most150PktFragment->firstData[1] == 0x02);
    BOOST_CHECK(most150PktFragment->firstData[2] == 0x03);
    BOOST_CHECK(most150PktFragment->firstData[3] == 0x04);
    BOOST_CHECK(most150PktFragment->firstData[4] == 0x05);
    BOOST_CHECK(most150PktFragment->firstData[5] == 0x06);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_ETHERNET_PKT_FRAGMENT = 81 */
BOOST_AUTO_TEST_CASE(MostEthernetPktFragment)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEthernetPktFragment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostEthernetPktFragment * mostEthernetPktFragment;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT);
    mostEthernetPktFragment = static_cast<Vector::BLF::MostEthernetPktFragment *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostEthernetPktFragment->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostEthernetPktFragment->headerSize == mostEthernetPktFragment->calculateHeaderSize());
    BOOST_CHECK(mostEthernetPktFragment->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostEthernetPktFragment->objectSize == mostEthernetPktFragment->calculateObjectSize());
    BOOST_CHECK(mostEthernetPktFragment->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT);
    /* ObjectHeader2 */
    BOOST_CHECK(mostEthernetPktFragment->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostEthernetPktFragment->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostEthernetPktFragment->objectVersion == 0);
    BOOST_CHECK(mostEthernetPktFragment->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(mostEthernetPktFragment->originalTimeStamp == 0);
    /* MostEthernetPktFragment */
    BOOST_CHECK(mostEthernetPktFragment->channel == 1);
    // reserved
    BOOST_CHECK(mostEthernetPktFragment->ackNack == 0x11); // Ack|NoResp
    BOOST_CHECK(mostEthernetPktFragment->validMask == 0x01020304);
    BOOST_CHECK(mostEthernetPktFragment->sourceMacAdr == 0x010203040506);
    BOOST_CHECK(mostEthernetPktFragment->destMacAdr == 0x112233445566);
    BOOST_CHECK(mostEthernetPktFragment->pAck == 0x01); // Buffer full
    BOOST_CHECK(mostEthernetPktFragment->cAck == 0x44); // OK
    // reserved
    BOOST_CHECK(mostEthernetPktFragment->crc == 0xAABBCCDD);
    BOOST_CHECK(mostEthernetPktFragment->dataLen == 0x0006);
    BOOST_CHECK(mostEthernetPktFragment->dataLenAnnounced == 0x0210);
    BOOST_CHECK(mostEthernetPktFragment->firstDataLen == 0x0006);
    // reserved
    BOOST_CHECK(mostEthernetPktFragment->firstData[0] == 0x01);
    BOOST_CHECK(mostEthernetPktFragment->firstData[1] == 0x02);
    BOOST_CHECK(mostEthernetPktFragment->firstData[2] == 0x03);
    BOOST_CHECK(mostEthernetPktFragment->firstData[3] == 0x04);
    BOOST_CHECK(mostEthernetPktFragment->firstData[4] == 0x05);
    BOOST_CHECK(mostEthernetPktFragment->firstData[5] == 0x06);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_SYSTEM_EVENT = 82 */
BOOST_AUTO_TEST_CASE(MostSystemEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostSystemEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostSystemEvent * mostSystemEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_SYSTEM_EVENT);
    mostSystemEvent = static_cast<Vector::BLF::MostSystemEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostSystemEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostSystemEvent->headerSize == mostSystemEvent->calculateHeaderSize());
    BOOST_CHECK(mostSystemEvent->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostSystemEvent->objectSize == mostSystemEvent->calculateObjectSize());
    BOOST_CHECK(mostSystemEvent->objectType == Vector::BLF::ObjectType::MOST_SYSTEM_EVENT);
    /* ObjectHeader2 */
    BOOST_CHECK(mostSystemEvent->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostSystemEvent->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostSystemEvent->objectVersion == 0);
    BOOST_CHECK(mostSystemEvent->objectTimeStamp == 1027900000); // ns
    BOOST_CHECK(mostSystemEvent->originalTimeStamp == 0);
    /* MostSystemEvent */
    mostSystemEvent = static_cast<Vector::BLF::MostSystemEvent *>(ohb);
    BOOST_CHECK(mostSystemEvent->channel == 1);
    BOOST_CHECK(mostSystemEvent->id == 1);
    BOOST_CHECK(mostSystemEvent->value == 1);
    BOOST_CHECK(mostSystemEvent->valueOld == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_150_ALLOCTAB = 83 */
BOOST_AUTO_TEST_CASE(Most150AllocTab)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150AllocTab.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150AllocTab * most150AllocTab;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    most150AllocTab = static_cast<Vector::BLF::Most150AllocTab *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150AllocTab->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150AllocTab->headerSize == most150AllocTab->calculateHeaderSize());
    BOOST_CHECK(most150AllocTab->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150AllocTab->objectSize == most150AllocTab->calculateObjectSize());
    BOOST_CHECK(most150AllocTab->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    /* ObjectHeader2 */
    BOOST_CHECK(most150AllocTab->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150AllocTab->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150AllocTab->objectVersion == 0);
    BOOST_CHECK(most150AllocTab->objectTimeStamp == 44814398000); // ns
    BOOST_CHECK(most150AllocTab->originalTimeStamp == 0);
    /* Most150AllocTab */
    BOOST_CHECK(most150AllocTab->channel == 1);
    BOOST_CHECK(most150AllocTab->eventModeFlags == 0);
    BOOST_CHECK(most150AllocTab->freeBytes == 0x2e);
    BOOST_CHECK(most150AllocTab->length == 8);
    BOOST_CHECK(most150AllocTab->tableData[0] == 0xc618);
    BOOST_CHECK(most150AllocTab->tableData[1] == 0x1937);
    BOOST_CHECK(most150AllocTab->tableData[2] == 0x0f98);
    BOOST_CHECK(most150AllocTab->tableData[3] == 0x0052);
    BOOST_CHECK(most150AllocTab->tableData[4] == 0x010b);
    BOOST_CHECK(most150AllocTab->tableData[5] == 0x0004);
    BOOST_CHECK(most150AllocTab->tableData[6] == 0x4151);
    BOOST_CHECK(most150AllocTab->tableData[7] == 0x0046);
    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    most150AllocTab = static_cast<Vector::BLF::Most150AllocTab *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150AllocTab->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150AllocTab->headerSize == most150AllocTab->calculateHeaderSize());
    BOOST_CHECK(most150AllocTab->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150AllocTab->objectSize == most150AllocTab->calculateObjectSize());
    BOOST_CHECK(most150AllocTab->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    /* ObjectHeader2 */
    BOOST_CHECK(most150AllocTab->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150AllocTab->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150AllocTab->objectVersion == 0);
    BOOST_CHECK(most150AllocTab->objectTimeStamp == 50126855000); // ns
    BOOST_CHECK(most150AllocTab->originalTimeStamp == 0);
    /* Most150AllocTab */
    BOOST_CHECK(most150AllocTab->channel == 1);
    BOOST_CHECK(most150AllocTab->eventModeFlags == 0);
    BOOST_CHECK(most150AllocTab->freeBytes == 0x74);
    BOOST_CHECK(most150AllocTab->length == 8);
    BOOST_CHECK(most150AllocTab->tableData[0] == 0xc618);
    BOOST_CHECK(most150AllocTab->tableData[1] == 0x1937);
    BOOST_CHECK(most150AllocTab->tableData[2] == 0x346a);
    BOOST_CHECK(most150AllocTab->tableData[3] == 0x6d0d);
    BOOST_CHECK(most150AllocTab->tableData[4] == 0x010b);
    BOOST_CHECK(most150AllocTab->tableData[5] == 0x0004);
    BOOST_CHECK(most150AllocTab->tableData[6] == 0x8151);
    BOOST_CHECK(most150AllocTab->tableData[7] == 0x0046);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_50_MESSAGE = 84 */
BOOST_AUTO_TEST_CASE(Most50Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most50Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most50Message * most50Message;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);
    most50Message = static_cast<Vector::BLF::Most50Message *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most50Message->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most50Message->headerSize == most50Message->calculateHeaderSize());
    BOOST_CHECK(most50Message->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most50Message->objectSize == most50Message->calculateObjectSize());
    BOOST_CHECK(most50Message->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);
    /* ObjectHeader2 */
    BOOST_CHECK(most50Message->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most50Message->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most50Message->objectVersion == 0);
    BOOST_CHECK(most50Message->objectTimeStamp == 200000000); // ns
    BOOST_CHECK(most50Message->originalTimeStamp == 0);
    /* Most50Message */
    BOOST_CHECK(most50Message->channel == 1);
    BOOST_CHECK(most50Message->dir == 0); // Rx
    // reserved
    BOOST_CHECK(most50Message->sourceAdr == 0xEF00);
    BOOST_CHECK(most50Message->destAdr == 0x0101);
    BOOST_CHECK(most50Message->transferType == 2); // Spy
    BOOST_CHECK(most50Message->state == 0x01); // bus active
    BOOST_CHECK(most50Message->ackNack == 0x00);
    // reserved
    BOOST_CHECK(most50Message->crc == 0x5678);
    // reserved
    BOOST_CHECK(most50Message->priority == 0);
    // reserved
    BOOST_CHECK(most50Message->msgLen == 9);
    // reserved
    BOOST_CHECK(most50Message->msg[0] == 0x11);
    BOOST_CHECK(most50Message->msg[1] == 0x01);
    BOOST_CHECK(most50Message->msg[2] == 0x22);
    BOOST_CHECK(most50Message->msg[3] == 0x23);
    BOOST_CHECK(most50Message->msg[4] == 0x04);
    BOOST_CHECK(most50Message->msg[5] == 0x11);
    BOOST_CHECK(most50Message->msg[6] == 0x22);
    BOOST_CHECK(most50Message->msg[7] == 0x33);
    BOOST_CHECK(most50Message->msg[8] == 0x44);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_50_PKT = 85 */
BOOST_AUTO_TEST_CASE(Most50Pkt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most50Pkt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most50Pkt * most50Pkt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_50_PKT);
    most50Pkt = static_cast<Vector::BLF::Most50Pkt *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most50Pkt->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most50Pkt->headerSize == most50Pkt->calculateHeaderSize());
    BOOST_CHECK(most50Pkt->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most50Pkt->objectSize == most50Pkt->calculateObjectSize());
    BOOST_CHECK(most50Pkt->objectType == Vector::BLF::ObjectType::MOST_50_PKT);
    /* ObjectHeader2 */
    BOOST_CHECK(most50Pkt->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most50Pkt->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most50Pkt->objectVersion == 0);
    BOOST_CHECK(most50Pkt->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most50Pkt->originalTimeStamp == 0);
    /* Most50Pkt */
    BOOST_CHECK(most50Pkt->channel == 1);
    BOOST_CHECK(most50Pkt->dir == 1); // Tx
    // reserved
    BOOST_CHECK(most50Pkt->sourceAdr == 0x0172);
    BOOST_CHECK(most50Pkt->destAdr == 0x03C8);
    BOOST_CHECK(most50Pkt->transferType == 1); // Node
    BOOST_CHECK(most50Pkt->state == 2); // ???
    BOOST_CHECK(most50Pkt->ackNack == 0x11); // Valid | Ack
    // reserved
    BOOST_CHECK(most50Pkt->crc == 0xAABB);
    // reserved
    BOOST_CHECK(most50Pkt->priority == 0);
    BOOST_CHECK(most50Pkt->pktDataLength == 8);
    BOOST_CHECK(most50Pkt->pktData[0] == 0x11);
    BOOST_CHECK(most50Pkt->pktData[1] == 0x22);
    BOOST_CHECK(most50Pkt->pktData[2] == 0x33);
    BOOST_CHECK(most50Pkt->pktData[3] == 0x34);
    BOOST_CHECK(most50Pkt->pktData[4] == 0x00);
    BOOST_CHECK(most50Pkt->pktData[5] == 0x02);
    BOOST_CHECK(most50Pkt->pktData[6] == 0x11);
    BOOST_CHECK(most50Pkt->pktData[7] == 0x22);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_MESSAGE2 = 86 */
#if 0
BOOST_AUTO_TEST_CASE(CanMessage2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanMessage2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanMessage2 * canMessage2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE2);
    canMessage2 = static_cast<Vector::BLF::CanMessage2 *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* LIN_UNEXPECTED_WAKEUP = 87 */
BOOST_AUTO_TEST_CASE(LinUnexpectedWakeup)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinUnexpectedWakeup.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinUnexpectedWakeup * linUnexpectedWakeup;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_UNEXPECTED_WAKEUP);
    linUnexpectedWakeup = static_cast<Vector::BLF::LinUnexpectedWakeup *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linUnexpectedWakeup->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linUnexpectedWakeup->headerSize == linUnexpectedWakeup->calculateHeaderSize());
    BOOST_CHECK(linUnexpectedWakeup->headerVersion == 1);
    BOOST_CHECK(linUnexpectedWakeup->objectSize == linUnexpectedWakeup->calculateObjectSize());
    BOOST_CHECK(linUnexpectedWakeup->objectType == Vector::BLF::ObjectType::LIN_UNEXPECTED_WAKEUP);
    /* ObjectHeader */
    BOOST_CHECK(linUnexpectedWakeup->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linUnexpectedWakeup->objectVersion == 0);
    BOOST_CHECK(linUnexpectedWakeup->objectTimeStamp == 892363000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linUnexpectedWakeup->sof == 891843000); // ns
    BOOST_CHECK(linUnexpectedWakeup->eventBaudrate == 19230);
    BOOST_CHECK(linUnexpectedWakeup->channel == 1);
    // reserved
    /* LinUnexpectedWakeup */
    BOOST_CHECK(linUnexpectedWakeup->width == 260000); // us
    BOOST_CHECK(linUnexpectedWakeup->signal == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SHORT_OR_SLOW_RESPONSE = 88 */
BOOST_AUTO_TEST_CASE(LinShortOrSlowResponse)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinShortOrSlowResponse.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinShortOrSlowResponse * linShortOrSlowResponse;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE);
    linShortOrSlowResponse = static_cast<Vector::BLF::LinShortOrSlowResponse *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linShortOrSlowResponse->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linShortOrSlowResponse->headerSize == linShortOrSlowResponse->calculateHeaderSize());
    BOOST_CHECK(linShortOrSlowResponse->headerVersion == 1);
    BOOST_CHECK(linShortOrSlowResponse->objectSize == linShortOrSlowResponse->calculateObjectSize());
    BOOST_CHECK(linShortOrSlowResponse->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE);
    /* ObjectHeader */
    BOOST_CHECK(linShortOrSlowResponse->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linShortOrSlowResponse->objectVersion == 0);
    BOOST_CHECK(linShortOrSlowResponse->objectTimeStamp == 1298765000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linShortOrSlowResponse->sof == 1279516000); // ns
    BOOST_CHECK(linShortOrSlowResponse->eventBaudrate == 19230);
    BOOST_CHECK(linShortOrSlowResponse->channel == 1);
    // reserved
    /* LinSynchFieldEvent */
    BOOST_CHECK(linShortOrSlowResponse->synchBreakLength == 937250);
    BOOST_CHECK(linShortOrSlowResponse->synchDelLength == 102625);
    /* LinMessageDescriptor */
    BOOST_CHECK(linShortOrSlowResponse->supplierId == 0);
    BOOST_CHECK(linShortOrSlowResponse->messageId == 0);
    BOOST_CHECK(linShortOrSlowResponse->nad == 0);
    BOOST_CHECK(linShortOrSlowResponse->id == 1);
    BOOST_CHECK(linShortOrSlowResponse->dlc == 8);
    BOOST_CHECK(linShortOrSlowResponse->checksumModel == 0xff);
    /* LinDatabyteTimestampEvent */
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[0] == 1281570000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[1] == 1283679000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[2] == 1285759000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[3] == 1287839000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[4] == 1289927000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[5] == 1292007000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[6] == 1294087000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[7] == 1296167000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[8] == 1298244000); // ns
    /* LinShortOrSlowResponse */
    BOOST_CHECK(linShortOrSlowResponse->numberOfRespBytes == 9);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[0] == 0x11);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[1] == 0x12);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[2] == 0x13);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[3] == 0x14);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[4] == 0x15);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[5] == 0x16);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[6] == 0x17);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[7] == 0x18);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[8] == 0x99);
    BOOST_CHECK(linShortOrSlowResponse->slowResponse == 1);
    BOOST_CHECK(linShortOrSlowResponse->interruptedByBreak == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_DISTURBANCE_EVENT = 89 */
BOOST_AUTO_TEST_CASE(LinDisturbanceEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDisturbanceEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinDisturbanceEvent * linDisturbanceEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_DISTURBANCE_EVENT);
    linDisturbanceEvent = static_cast<Vector::BLF::LinDisturbanceEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linDisturbanceEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linDisturbanceEvent->headerSize == linDisturbanceEvent->calculateHeaderSize());
    BOOST_CHECK(linDisturbanceEvent->headerVersion == 1);
    BOOST_CHECK(linDisturbanceEvent->objectSize == linDisturbanceEvent->calculateObjectSize());
    BOOST_CHECK(linDisturbanceEvent->objectType == Vector::BLF::ObjectType::LIN_DISTURBANCE_EVENT);
    /* ObjectHeader */
    BOOST_CHECK(linDisturbanceEvent->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linDisturbanceEvent->objectVersion == 0);
    BOOST_CHECK(linDisturbanceEvent->objectTimeStamp == 1323661000); // ns
    /* LinDisturbanceEvent */
    BOOST_CHECK(linDisturbanceEvent->channel == 1);
    BOOST_CHECK(linDisturbanceEvent->id == 0x2D);
    BOOST_CHECK(linDisturbanceEvent->disturbingFrameId == 0xFF);
    BOOST_CHECK(linDisturbanceEvent->disturbanceType == 0); // dominant disturbance
    BOOST_CHECK(linDisturbanceEvent->byteIndex == 1);
    BOOST_CHECK(linDisturbanceEvent->bitIndex == 6);
    BOOST_CHECK(linDisturbanceEvent->bitOffsetInSixteenthBits == 0);
    BOOST_CHECK(linDisturbanceEvent->disturbanceLengthInSixteenthBits == 16);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* SERIAL_EVENT = 90 */
BOOST_AUTO_TEST_CASE(SerialEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/SerialEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::SerialEvent * serialEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);
    serialEvent = static_cast<Vector::BLF::SerialEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(serialEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(serialEvent->headerSize == serialEvent->calculateHeaderSize());
    BOOST_CHECK(serialEvent->headerVersion == 1);
    BOOST_CHECK(serialEvent->objectSize == serialEvent->calculateObjectSize());
    BOOST_CHECK(serialEvent->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);
    /* ObjectHeader */
    BOOST_CHECK(serialEvent->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(serialEvent->objectVersion == 0);
    BOOST_CHECK(serialEvent->objectTimeStamp == 12315000000); // ns
    /* SerialEvent */
    BOOST_CHECK(serialEvent->flags == (uint32_t) (Vector::BLF::SerialEvent::Flags::KLineEvent) |
                                      (uint32_t) (Vector::BLF::SerialEvent::Flags::CompactByte));
    BOOST_CHECK(serialEvent->port == 2);
    BOOST_CHECK(serialEvent->baudrate == 10400);
    // reserved
    BOOST_CHECK(serialEvent->compact.compactLength == 7);
    BOOST_CHECK(serialEvent->compact.compactData[0] == 0x83);
    BOOST_CHECK(serialEvent->compact.compactData[1] == 0x11);
    BOOST_CHECK(serialEvent->compact.compactData[2] == 0x61);
    BOOST_CHECK(serialEvent->compact.compactData[3] == 0x7F);
    BOOST_CHECK(serialEvent->compact.compactData[4] == 0x1A);
    BOOST_CHECK(serialEvent->compact.compactData[5] == 0x78);
    BOOST_CHECK(serialEvent->compact.compactData[6] == 0x06);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* OVERRUN_ERROR = 91 */
#if 0
BOOST_AUTO_TEST_CASE(DriverOverrun)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/DriverOverrun.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::DriverOverrun * driverOverrun;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::OVERRUN_ERROR);
    driverOverrun = static_cast<Vector::BLF::DriverOverrun *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* EVENT_COMMENT = 92 */
BOOST_AUTO_TEST_CASE(EventComment)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EventComment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EventComment * eventComment;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::EVENT_COMMENT);
    eventComment = static_cast<Vector::BLF::EventComment *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(eventComment->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(eventComment->headerSize == eventComment->calculateHeaderSize());
    BOOST_CHECK(eventComment->headerVersion == 1);
    BOOST_CHECK(eventComment->objectSize == eventComment->calculateObjectSize());
    BOOST_CHECK(eventComment->objectType == Vector::BLF::ObjectType::EVENT_COMMENT);
    /* ObjectHeader */
    BOOST_CHECK(eventComment->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(eventComment->objectVersion == 0);
    BOOST_CHECK(eventComment->objectTimeStamp == 1593770000); // ns
    /* EventComment */
    BOOST_CHECK(eventComment->commentedEventType == 105);
    BOOST_CHECK(eventComment->textLength == 261);
    BOOST_CHECK(eventComment->text == "testComment");
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* WLAN_FRAME = 93 */
#if 0
BOOST_AUTO_TEST_CASE(WlanFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/WlanFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::WlanFrame * wlanFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::WLAN_FRAME);
    wlanFrame = static_cast<Vector::BLF::WlanFrame *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* WLAN_STATISTIC = 94 */
#if 0
BOOST_AUTO_TEST_CASE(WlanStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/WlanStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::WlanStatistic * wlanStatistic;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::WLAN_STATISTIC);
    wlanStatistic = static_cast<Vector::BLF::WlanStatistic *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* MOST_ECL = 95 */
BOOST_AUTO_TEST_CASE(MostEcl)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEcl.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostEcl * mostEcl;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ECL);
    mostEcl = static_cast<Vector::BLF::MostEcl *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostEcl->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostEcl->headerSize == mostEcl->calculateHeaderSize());
    BOOST_CHECK(mostEcl->headerVersion == 1);
    BOOST_CHECK(mostEcl->objectSize == mostEcl->calculateObjectSize());
    BOOST_CHECK(mostEcl->objectType == Vector::BLF::ObjectType::MOST_ECL);
    /* ObjectHeader2 */
    BOOST_CHECK(mostEcl->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostEcl->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostEcl->objectVersion == 0);
    BOOST_CHECK(mostEcl->objectTimeStamp == 9068000); // ns
    BOOST_CHECK(mostEcl->originalTimeStamp == 0);
    /* MostEcl */
    BOOST_CHECK(mostEcl->channel == 1);
    BOOST_CHECK(mostEcl->mode == 0); // discrete
    BOOST_CHECK(mostEcl->eclState == 1); // line high
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* GLOBAL_MARKER = 96 */
BOOST_AUTO_TEST_CASE(GlobalMarker)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/GlobalMarker.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::GlobalMarker * globalMarker;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);
    globalMarker = static_cast<Vector::BLF::GlobalMarker *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(globalMarker->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(globalMarker->headerSize == globalMarker->calculateHeaderSize());
    BOOST_CHECK(globalMarker->headerVersion == 1);
    BOOST_CHECK(globalMarker->objectSize == globalMarker->calculateObjectSize());
    BOOST_CHECK(globalMarker->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);
    /* ObjectHeader */
    BOOST_CHECK(globalMarker->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(globalMarker->objectVersion == 0);
    BOOST_CHECK(globalMarker->objectTimeStamp == 2200804000); // ns
    /* GlobalMarker */
    BOOST_CHECK(globalMarker->commentedEventType == 0);
    BOOST_CHECK(globalMarker->foregroundColor == 0);
    BOOST_CHECK(globalMarker->backgroundColor == 16777215);
    BOOST_CHECK(globalMarker->isRelocatable == 1);
    // reserved
    BOOST_CHECK(globalMarker->groupNameLength == 0x83);
    BOOST_CHECK(globalMarker->markerNameLength == 0x83);
    BOOST_CHECK(globalMarker->descriptionLength == 0x105);
    BOOST_CHECK(globalMarker->groupName == "Marker Group");
    BOOST_CHECK(globalMarker->markerName == "[1]");
    BOOST_CHECK(globalMarker->description == "description");
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* AFDX_FRAME = 97 */
BOOST_AUTO_TEST_CASE(AfdxFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/AfdxFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::AfdxFrame * afdxFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(afdxFrame->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(afdxFrame->headerSize == afdxFrame->calculateHeaderSize());
    BOOST_CHECK(afdxFrame->headerVersion == 1);
    BOOST_CHECK(afdxFrame->objectSize == afdxFrame->calculateObjectSize());
    BOOST_CHECK(afdxFrame->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    /* ObjectHeader */
    BOOST_CHECK(afdxFrame->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(afdxFrame->objectVersion == 0);
    BOOST_CHECK(afdxFrame->objectTimeStamp == 0); // ns
    /* AfdxFrame */
    BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    BOOST_CHECK(afdxFrame->sourceAddress[1] == 0x00);
    BOOST_CHECK(afdxFrame->sourceAddress[2] == 0x00);
    BOOST_CHECK(afdxFrame->sourceAddress[3] == 0x00);
    BOOST_CHECK(afdxFrame->sourceAddress[4] == 0x00);
    BOOST_CHECK(afdxFrame->sourceAddress[5] == 0x04);
    BOOST_CHECK(afdxFrame->channel == 0x0001);
    BOOST_CHECK(afdxFrame->destinationAddress[0] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[1] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[2] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[3] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[4] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[5] == 0xff);
    BOOST_CHECK(afdxFrame->dir == Vector::BLF::AfdxFrame::Dir::Tx);
    BOOST_CHECK(afdxFrame->type == 0x0806);
    BOOST_CHECK(afdxFrame->tpid == 0x0000);
    BOOST_CHECK(afdxFrame->tci == 0x0000);
    BOOST_CHECK(afdxFrame->ethChannel == 0x01);
    // reserved
    BOOST_CHECK(afdxFrame->afdxFlags == 0x0040);
    // reserved
    BOOST_CHECK(afdxFrame->bagUsec == 0);
    BOOST_CHECK(afdxFrame->payLoadLength == 0x002e);
    // reserved
    BOOST_CHECK(afdxFrame->payLoad[0x00] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x01] == 0x01);
    BOOST_CHECK(afdxFrame->payLoad[0x02] == 0x08);
    BOOST_CHECK(afdxFrame->payLoad[0x03] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x04] == 0x06);
    BOOST_CHECK(afdxFrame->payLoad[0x05] == 0x04);
    BOOST_CHECK(afdxFrame->payLoad[0x06] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x07] == 0x01);
    BOOST_CHECK(afdxFrame->payLoad[0x08] == 0x40);
    BOOST_CHECK(afdxFrame->payLoad[0x09] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x0a] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x0b] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x0c] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x0d] == 0x04);
    BOOST_CHECK(afdxFrame->payLoad[0x0e] == 0xc0);
    BOOST_CHECK(afdxFrame->payLoad[0x0f] == 0xa8);
    BOOST_CHECK(afdxFrame->payLoad[0x10] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x11] == 0x01);
    BOOST_CHECK(afdxFrame->payLoad[0x12] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x13] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x14] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x15] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x16] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x17] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x18] == 0xc0);
    BOOST_CHECK(afdxFrame->payLoad[0x19] == 0xa8);
    BOOST_CHECK(afdxFrame->payLoad[0x1a] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x1b] == 0x01);
    BOOST_CHECK(afdxFrame->payLoad[0x1c] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x1d] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x1e] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x1f] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x20] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x21] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x22] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x23] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x24] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x25] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x26] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x27] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x28] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x29] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x2a] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x2b] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x2c] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x2d] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* AFDX_STATISTIC = 98 */
BOOST_AUTO_TEST_CASE(AfdxStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/AfdxStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::AfdxStatistic * afdxStatistic;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_STATISTIC);
    afdxStatistic = static_cast<Vector::BLF::AfdxStatistic *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(afdxStatistic->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(afdxStatistic->headerSize == afdxStatistic->calculateHeaderSize());
    BOOST_CHECK(afdxStatistic->headerVersion == 1);
    BOOST_CHECK(afdxStatistic->objectSize == afdxStatistic->calculateObjectSize());
    BOOST_CHECK(afdxStatistic->objectType == Vector::BLF::ObjectType::AFDX_STATISTIC);
    /* ObjectHeader */
    BOOST_CHECK(afdxStatistic->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(afdxStatistic->objectVersion == 0);
    BOOST_CHECK(afdxStatistic->objectTimeStamp == 1000763955); // ns
    /* AfdxStatistic */
    BOOST_CHECK(afdxStatistic->channel == 1);
    BOOST_CHECK(afdxStatistic->flags == 0xb);
    BOOST_CHECK(afdxStatistic->rxPacketCount == 3);
    BOOST_CHECK(afdxStatistic->rxByteCount == 417);
    BOOST_CHECK(afdxStatistic->txPacketCount == 0);
    BOOST_CHECK(afdxStatistic->txByteCount == 0);
    BOOST_CHECK(afdxStatistic->collisionCount == 0);
    BOOST_CHECK(afdxStatistic->errorCount == 0);
    BOOST_CHECK(afdxStatistic->statDroppedRedundantPacketCount == 0);
    BOOST_CHECK(afdxStatistic->statRedundantErrorPacketCount == 0);
    BOOST_CHECK(afdxStatistic->statIntegrityErrorPacketCount == 0);
    BOOST_CHECK(afdxStatistic->statAvrgPeriodMsec == 0);
    BOOST_CHECK(afdxStatistic->statAvrgJitterMysec == 0);
    BOOST_CHECK(afdxStatistic->vlid == 0);
    BOOST_CHECK(afdxStatistic->statDuration == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* KLINE_STATUSEVENT = 99 */
#if 0
BOOST_AUTO_TEST_CASE(KLineStatusEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/KLineStatusEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::KLineStatusEvent * kLineStatusEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::KLINE_STATUSEVENT);
    kLineStatusEvent = static_cast<Vector::BLF::KLineStatusEvent *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* CAN_FD_MESSAGE = 100 */
#if 0
BOOST_AUTO_TEST_CASE(CanFdMessage)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanFdMessage * canFdMessage;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_MESSAGE);
    canFdMessage = static_cast<Vector::BLF::CanFdMessage *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* CAN_FD_MESSAGE_64 = 101 */
#if 0
BOOST_AUTO_TEST_CASE(CanFdMessage64)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdMessage64.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanFdMessage64 * canFdMessage64;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_MESSAGE_64);
    canFdMessage64 = static_cast<Vector::BLF::CanFdMessage64 *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* ETHERNET_RX_ERROR = 102 */
#if 0
BOOST_AUTO_TEST_CASE(EthernetRxError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetRxError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EthernetRxError * ethernetRxError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ETHERNET_RX_ERROR);
    ethernetRxError = static_cast<Vector::BLF::EthernetRxError *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* ETHERNET_STATUS = 103 */
#if 0
BOOST_AUTO_TEST_CASE(EthernetStatus)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetStatus.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EthernetStatus * ethernetStatus;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ETHERNET_STATUS);
    ethernetStatus = static_cast<Vector::BLF::EthernetStatus *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif

/* CAN_FD_ERROR_64 = 104 */
#if 0
BOOST_AUTO_TEST_CASE(CanFdErrorFrame64)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdErrorFrame64.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanFdErrorFrame64 * canFdErrorFrame64;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_ERROR_64);
    canFdErrorFrame64 = static_cast<Vector::BLF::CanFdErrorFrame64 *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif
