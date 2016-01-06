#define BOOST_TEST_MODULE Events
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iterator>
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
    Vector::BLF::AfdxFrame * afdxFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_OVERLOAD = 3 */
BOOST_AUTO_TEST_CASE(CanOverloadFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanOverloadFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanOverloadFrame * canOverloadFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* APP_TRIGGER = 5 */
BOOST_AUTO_TEST_CASE(AppTrigger)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/AppTrigger.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::AppTrigger * appTrigger;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LOG_CONTAINER = 10 */
// LogContainer is indirectly tested

/* LIN_MESSAGE = 11 */
BOOST_AUTO_TEST_CASE(LinMessage)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinMessage * linMessage;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_CRC_ERROR = 12 */
BOOST_AUTO_TEST_CASE(LinCrcError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinCrcError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinCrcError * linCrcError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    BOOST_CHECK(linDlcInfo->channel = 1);
    BOOST_CHECK(linDlcInfo->id = 20);
    BOOST_CHECK(linDlcInfo->dlc = 4);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_RCV_ERROR = 14 */
BOOST_AUTO_TEST_CASE(LinReceiveError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinReceiveError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinReceiveError * linReceiveError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SND_ERROR = 15 */
BOOST_AUTO_TEST_CASE(LinSendError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSendError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSendError * linSendError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SYN_ERROR = 18 */
BOOST_AUTO_TEST_CASE(LinSyncError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSyncError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSyncError * linSyncError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_WAKEUP = 21 */
BOOST_AUTO_TEST_CASE(LinWakeupEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinWakeupEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinWakeupEvent * linWakeupEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* reserved_1 = 26 */
/* reserved_2 = 27 */
/* reserved_3 = 28 */

/* FLEXRAY_DATA = 29 */
BOOST_AUTO_TEST_CASE(FlexRayData)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayData.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayData * flexRayData;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* FLEXRAY_SYNC = 30 */
BOOST_AUTO_TEST_CASE(FlexRaySync)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRaySync.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRaySync * flexRaySync;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST_PKT = 32 */
BOOST_AUTO_TEST_CASE(MostPkt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostPkt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostPkt * mostPkt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* FLEXRAY_CYCLE = 40 */
BOOST_AUTO_TEST_CASE(FlexRayV6StartCycleEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayV6StartCycleEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayV6StartCycleEvent * flexRayV6StartCycleEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* FLEXRAY_MESSAGE = 41 */
BOOST_AUTO_TEST_CASE(FlexRayV6Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayV6Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayV6Message * flexRayV6Message;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    BOOST_CHECK(linChecksumInfo->channel == 1);
    BOOST_CHECK(linChecksumInfo->id == 22);
    BOOST_CHECK(linChecksumInfo->checksumModel == 0); // classic
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_SPIKE_EVENT = 43 */
BOOST_AUTO_TEST_CASE(LinSpikeEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSpikeEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSpikeEvent * linSpikeEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_DRIVER_SYNC = 44 */
BOOST_AUTO_TEST_CASE(CanDriverHwSync)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanDriverHwSync.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanDriverHwSync * canDriverHwSync;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* FLEXRAY_STATUS = 45 */
BOOST_AUTO_TEST_CASE(FlexRayStatusEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayStatusEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayStatusEvent * flexRayStatusEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* FR_ERROR = 47 */
BOOST_AUTO_TEST_CASE(FlexRayVFrError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayVFrError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrError * flexRayVFrError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* FR_STATUS = 48 */
BOOST_AUTO_TEST_CASE(FlexRayVFrStatus)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayVFrStatus.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrStatus * flexRayVFrStatus;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
BOOST_AUTO_TEST_CASE(FlexRayVFrReceiveMsg)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayVFrReceiveMsg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrReceiveMsg * flexRayVFrReceiveMsg;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* REALTIMECLOCK = 51 */
BOOST_AUTO_TEST_CASE(RealtimeClock)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/RealtimeClock.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::RealtimeClock * realtimeClock;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* J1708_MESSAGE = 55 */
/* J1708_VIRTUAL_MSG = 56 */
BOOST_AUTO_TEST_CASE(J1708Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/J1708Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::J1708Message * j1708Message;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    BOOST_CHECK(linSendError2->sof == 416054000); // ns
    BOOST_CHECK(linSendError2->eventBaudrate == 19230);
    BOOST_CHECK(linSendError2->channel == 1);
    // reserved
    BOOST_CHECK(linSendError2->synchBreakLength == 937187);
    BOOST_CHECK(linSendError2->synchDelLength == 113250);
    BOOST_CHECK(linSendError2->supplierId == 0);
    BOOST_CHECK(linSendError2->messageId == 0);
    BOOST_CHECK(linSendError2->nad == 0);
    BOOST_CHECK(linSendError2->id == 0x21); // 33
    BOOST_CHECK(linSendError2->dlc == 4);
    BOOST_CHECK(linSendError2->checksumModel == 1); // enhanced
    BOOST_CHECK(isEqual(linSendError2->eoh, 0.418122));
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_CRC_ERROR2 = 60 */
BOOST_AUTO_TEST_CASE(LinCrcError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinCrcError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinCrcError2 * linCrcError2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN_LONG_DOM_SIG = 64 */
BOOST_AUTO_TEST_CASE(LinLongDomSignalEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinLongDomSignalEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinLongDomSignalEvent * linLongDomSignalEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* APP_TEXT = 65 */
BOOST_AUTO_TEST_CASE(AppText)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/AppText.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::AppText * appText;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channel == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->version == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channelMask = 1); // FlexRay Channel A
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dir == 0); // Rx
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clientIndex == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clusterNo == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameId == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc1 == 0x0097); // 151
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc2 == 0x0097); // 151
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
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x00] == 0x15); // 21
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x01] == 0x57); // 87
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x02] == 0x16); // 22
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x03] == 0x94); // 148
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_DRIVER_ERROR_EXT = 74 */
BOOST_AUTO_TEST_CASE(CanDriverErrorExt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanDriverErrorExt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanDriverErrorExt * canDriverErrorExt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    BOOST_CHECK(mostEthernetPkt->channel == 1);
    BOOST_CHECK(mostEthernetPkt->dir == 1); // Tx
    // reserved
    BOOST_CHECK(mostEthernetPkt->sourceMacAdr == 0x010203040506);
    BOOST_CHECK(mostEthernetPkt->destMacAdr == 0x112233445566);
    BOOST_CHECK(mostEthernetPkt->transferType == 1); // Node
    BOOST_CHECK(mostEthernetPkt->state == 1); // bus active
    BOOST_CHECK(mostEthernetPkt->ackNack == 1); // Valid
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
BOOST_AUTO_TEST_CASE(CanMessage2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanMessage2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanMessage2 * canMessage2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    BOOST_CHECK(linUnexpectedWakeup->sof == 891843000); // ns
    BOOST_CHECK(linUnexpectedWakeup->eventBaudrate == 19230);
    BOOST_CHECK(linUnexpectedWakeup->channel == 1);
    // reserved
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    BOOST_CHECK(serialEvent->flags == (uint32_t) (Vector::BLF::SerialEvent::Flags::KLineEvent) |
                                      (uint32_t) (Vector::BLF::SerialEvent::Flags::CompactByte));
    BOOST_CHECK(serialEvent->port == 2);
    BOOST_CHECK(serialEvent->baudrate == 10400);
    // reserved
    BOOST_CHECK(serialEvent->data.compact.compactLength == 7);
    BOOST_CHECK(serialEvent->data.compact.compactData[0] == 0x83);
    BOOST_CHECK(serialEvent->data.compact.compactData[1] == 0x11);
    BOOST_CHECK(serialEvent->data.compact.compactData[2] == 0x61);
    BOOST_CHECK(serialEvent->data.compact.compactData[3] == 0x7F);
    BOOST_CHECK(serialEvent->data.compact.compactData[4] == 0x1A);
    BOOST_CHECK(serialEvent->data.compact.compactData[5] == 0x78);
    BOOST_CHECK(serialEvent->data.compact.compactData[6] == 0x06);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* OVERRUN_ERROR = 91 */
BOOST_AUTO_TEST_CASE(DriverOverrun)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/DriverOverrun.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::DriverOverrun * driverOverrun;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* WLAN_FRAME = 93 */
BOOST_AUTO_TEST_CASE(WlanFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/WlanFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::WlanFrame * wlanFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* WLAN_STATISTIC = 94 */
BOOST_AUTO_TEST_CASE(WlanStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/WlanStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::WlanStatistic * wlanStatistic;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
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
    BOOST_CHECK(globalMarker->commentedEventType == 0);
    BOOST_CHECK(globalMarker->foregroundColor == 0);
    BOOST_CHECK(globalMarker->backgroundColor == 16777215);
    BOOST_CHECK(globalMarker->isRelocatable == 1);
    // reserved
    BOOST_CHECK(globalMarker->groupNameLength == 0x83);
    BOOST_CHECK(globalMarker->markerNameLength == 0x83);
    BOOST_CHECK(globalMarker->descriptionLength == 0x105);
    // groupName
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
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* KLINE_STATUSEVENT = 99 */
BOOST_AUTO_TEST_CASE(KLineStatusEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/KLineStatusEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::KLineStatusEvent * kLineStatusEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_FD_MESSAGE = 100 */
BOOST_AUTO_TEST_CASE(CanFdMessage)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanFdMessage * canFdMessage;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_FD_MESSAGE_64 = 101 */
BOOST_AUTO_TEST_CASE(CanFdMessage64)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdMessage64.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanFdMessage64 * canFdMessage64;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* ETHERNET_RX_ERROR = 102 */
BOOST_AUTO_TEST_CASE(EthernetRxError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetRxError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EthernetRxError * ethernetRxError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* ETHERNET_STATUS = 103 */
BOOST_AUTO_TEST_CASE(EthernetStatus)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetStatus.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EthernetStatus * ethernetStatus;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN_FD_ERROR_64 = 104 */
BOOST_AUTO_TEST_CASE(CanFdErrorFrame64)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdErrorFrame64.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanFdErrorFrame64 * canFdErrorFrame64;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    //BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    //afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    // BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
