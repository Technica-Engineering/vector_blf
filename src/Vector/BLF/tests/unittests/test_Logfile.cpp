#define BOOST_TEST_MODULE Logfile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "Vector/BLF/File.h"

#define SUCCEEDED(code) ((int)(code) >= 0)
#define WARNED(code) ((int)(code) & 0x40000000)
#define FAILED(code) ((int)(code) < 0)

Vector::BLF::File file;

BOOST_AUTO_TEST_CASE(OpenLogfile)
{
    /* open log file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/data/logfile.blf");
    BOOST_REQUIRE(file.is_open());

    /* check file statistics */
    BOOST_REQUIRE(file.fileStatistics.signature == Vector::BLF::FileSignature);
#ifdef SHOW_FILE_STATISTICS
    /* show file statistics */
    std::cout << "signature: 0x" << std::hex << file.fileStatistics.signature << std::endl;
    std::cout << "applicationName: " << file.fileStatistics.applicationName() << std::endl;
    std::cout << "applicationNumber: " << std::dec << (unsigned short) file.fileStatistics.applicationMajor << "." << (unsigned short) file.fileStatistics.applicationMinor << "." << (unsigned short) file.fileStatistics.applicationBuild << std::endl;
    std::cout << "apiNumber: " << std::dec << (unsigned short) file.fileStatistics.apiMajor << "." << (unsigned short) file.fileStatistics.apiMinor << "." << (unsigned short) file.fileStatistics.apiBuild << "." << (unsigned short) file.fileStatistics.apiPatch << std::endl;
    std::cout << "fileSize: " << std::dec << file.fileStatistics.fileSize << " = 0x" << std::hex << file.fileStatistics.fileSize << std::endl;
    std::cout << "uncompressedFileSize: " << std::dec << file.fileStatistics.uncompressedFileSize << " = 0x" << std::hex << file.fileStatistics.uncompressedFileSize << std::endl;
    std::cout << "objectCount: " << std::dec << file.fileStatistics.objectCount << std::endl;
    std::cout << "objectsRead: " << std::dec << file.fileStatistics.objectsRead << std::endl;
    std::cout << "measurementStartTime: " << std::dec
              << file.fileStatistics.measurementStartTime.year << "-" << file.fileStatistics.measurementStartTime.month << "-" << file.fileStatistics.measurementStartTime.day << " (" << file.fileStatistics.measurementStartTime.dayOfWeek << ") "
              << file.fileStatistics.measurementStartTime.hour << ":" << file.fileStatistics.measurementStartTime.minute << ":" << file.fileStatistics.measurementStartTime.second << "+" << file.fileStatistics.measurementStartTime.milliseconds << "ms" << std::endl;
    std::cout << "lastObjectTime: " << std::dec
              << file.fileStatistics.lastObjectTime.year << "-" << file.fileStatistics.lastObjectTime.month << "-" << file.fileStatistics.lastObjectTime.day << " (" << file.fileStatistics.lastObjectTime.dayOfWeek << ") "
              << file.fileStatistics.lastObjectTime.hour << ":" << file.fileStatistics.lastObjectTime.minute << ":" << file.fileStatistics.lastObjectTime.second << "+" << file.fileStatistics.lastObjectTime.milliseconds << "ms" << std::endl;
#endif
}

/* 1 = CAN_MESSAGE = "CAN message object" */
BOOST_AUTO_TEST_CASE(ObjectTypes_001)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);

    /* ObjectHeader */
    Vector::BLF::CanMessage * obj = (Vector::BLF::CanMessage *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (1.000000 * timeFactor));

    /* CanMessage */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->flags == 0x01); // TX
    BOOST_CHECK(obj->dlc == 8);
    BOOST_CHECK(obj->id == 0x64);
    BOOST_CHECK(obj->data[0] == 0x01);
    BOOST_CHECK(obj->data[1] == 0x02);
    BOOST_CHECK(obj->data[2] == 0x03);
    BOOST_CHECK(obj->data[3] == 0x04);
    BOOST_CHECK(obj->data[4] == 0x05);
    BOOST_CHECK(obj->data[5] == 0x06);
    BOOST_CHECK(obj->data[6] == 0x07);
    BOOST_CHECK(obj->data[7] == 0x08);

    delete ohb;
}

/* 4 = CAN_STATISTIC = "CAN driver statistics object" */
BOOST_AUTO_TEST_CASE(ObjectTypes_004)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_STATISTIC);

    /* ObjectHeader */
    Vector::BLF::CanDriverStatistic * obj = (Vector::BLF::CanDriverStatistic *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (4.000000 * timeFactor));

    /* CanDriverStatistic */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->busLoad == (12.34 * 100));
    BOOST_CHECK(obj->standardDataFrames == 1);
    BOOST_CHECK(obj->extendedDataFrames == 3);
    BOOST_CHECK(obj->standardRemoteFrames == 2);
    BOOST_CHECK(obj->extendedRemoteFrames == 4);
    BOOST_CHECK(obj->errorFrames == 5);
    BOOST_CHECK(obj->overloadFrames == 6);
    // reserved

    delete ohb;
}

/* 17 = LIN_SCHED_MODCH = "LIN scheduler mode change object" */
BOOST_AUTO_TEST_CASE(ObjectTypes_017)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SCHED_MODCH);

    /* ObjectHeader */
    Vector::BLF::LinSchedulerModeChange * obj = (Vector::BLF::LinSchedulerModeChange *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (17.000000 * timeFactor));

    /* LinSchedulerModeChange */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->oldMode == 2);
    BOOST_CHECK(obj->newMode == 3);
    // reserved

    delete ohb;
}

/* 20 = LIN_SLEEP = "LIN sleep mode event object" */
BOOST_AUTO_TEST_CASE(ObjectTypes_020)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SLEEP);

    /* ObjectHeader */
    Vector::BLF::LinSleepModeEvent * obj = (Vector::BLF::LinSleepModeEvent *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (20.000000 * timeFactor));

    /* LinSleepModeEvent */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->reason == 0);
    BOOST_CHECK(obj->flags == (uint8_t) Vector::BLF::LinSleepModeEvent::Flags::IsAwake);
    // reserved

    delete ohb;
}

/* 22 = MOST_SPY = "MOST spy message object" */
BOOST_AUTO_TEST_CASE(ObjectTypes_022)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_SPY);

    /* ObjectHeader */
    Vector::BLF::MostSpy * obj = (Vector::BLF::MostSpy *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (22.000000 * timeFactor));

    /* MostSpy */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->dir == 0);
    // reserved1
    BOOST_CHECK(obj->sourceAdr == 0x1122);
    BOOST_CHECK(obj->destAdr == 0x3344);
    BOOST_CHECK(obj->msg[ 0] == 0x01);
    BOOST_CHECK(obj->msg[ 1] == 0x02);
    BOOST_CHECK(obj->msg[ 2] == 0x03);
    BOOST_CHECK(obj->msg[ 3] == 0x04);
    BOOST_CHECK(obj->msg[ 4] == 0x05);
    BOOST_CHECK(obj->msg[ 5] == 0x06);
    BOOST_CHECK(obj->msg[ 6] == 0x07);
    BOOST_CHECK(obj->msg[ 7] == 0x08);
    BOOST_CHECK(obj->msg[ 8] == 0x09);
    BOOST_CHECK(obj->msg[ 9] == 0x0a);
    BOOST_CHECK(obj->msg[10] == 0x0b);
    BOOST_CHECK(obj->msg[11] == 0x0c);
    BOOST_CHECK(obj->msg[12] == 0x0d);
    BOOST_CHECK(obj->msg[13] == 0x0e);
    BOOST_CHECK(obj->msg[14] == 0x0f);
    BOOST_CHECK(obj->msg[15] == 0x10);
    BOOST_CHECK(obj->msg[16] == 0x11);
    // reserved2
    BOOST_CHECK(obj->rTyp == 0x03);
    BOOST_CHECK(obj->rTypAdr == 0x10);
    BOOST_CHECK(obj->state == 0x34);
    // reserved3
    BOOST_CHECK(obj->ackNack == 0x65);
    BOOST_CHECK(obj->crc == 0x5678);

    delete ohb;
}

/* 23 = MOST_CTRL = "MOST control message object" */
BOOST_AUTO_TEST_CASE(ObjectTypes_023)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_CTRL);

    /* ObjectHeader */
    Vector::BLF::MostCtrl * obj = (Vector::BLF::MostCtrl *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (23.000000 * timeFactor));

    /* MostCtrl */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->dir == 1);
    // reserved1
    BOOST_CHECK(obj->sourceAdr == 0x1122);
    BOOST_CHECK(obj->destAdr == 0x3344);
    BOOST_CHECK(obj->msg[ 0] == 0x01);
    BOOST_CHECK(obj->msg[ 1] == 0x02);
    BOOST_CHECK(obj->msg[ 2] == 0x03);
    BOOST_CHECK(obj->msg[ 3] == 0x04);
    BOOST_CHECK(obj->msg[ 4] == 0x05);
    BOOST_CHECK(obj->msg[ 5] == 0x06);
    BOOST_CHECK(obj->msg[ 6] == 0x07);
    BOOST_CHECK(obj->msg[ 7] == 0x08);
    BOOST_CHECK(obj->msg[ 8] == 0x09);
    BOOST_CHECK(obj->msg[ 9] == 0x0a);
    BOOST_CHECK(obj->msg[10] == 0x0b);
    BOOST_CHECK(obj->msg[11] == 0x0c);
    BOOST_CHECK(obj->msg[12] == 0x0d);
    BOOST_CHECK(obj->msg[13] == 0x0e);
    BOOST_CHECK(obj->msg[14] == 0x0f);
    BOOST_CHECK(obj->msg[15] == 0x10);
    BOOST_CHECK(obj->msg[16] == 0x11);
    // reserved2
    BOOST_CHECK(obj->rTyp == 0x03);
    BOOST_CHECK(obj->rTypAdr == 0x03);
    BOOST_CHECK(obj->state == 0x34);
    // reserved3
    BOOST_CHECK(obj->ackNack == 0x12);
    // reserved4

    delete ohb;
}

/* 24 = MOST_LIGHTLOCK = "MOST light lock object" */
BOOST_AUTO_TEST_CASE(ObjectTypes_024)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);

    /* ObjectHeader */
    Vector::BLF::MostLightLock * obj = (Vector::BLF::MostLightLock *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (24.000000 * timeFactor));

    /* MostLightLock */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->state == 2);
    // reserved

    delete ohb;
}

/* 25 = MOST_STATISTIC = "MOST statistic object" */
BOOST_AUTO_TEST_CASE(ObjectTypes_025)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_STATISTIC);

    /* ObjectHeader */
    Vector::BLF::MostStatistic * obj = (Vector::BLF::MostStatistic *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (25.000000 * timeFactor));

    /* MostStatistic */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->pktCnt == 5);
    BOOST_CHECK(obj->frmCnt == 2);
    BOOST_CHECK(obj->lightCnt == 3);
    BOOST_CHECK(obj->bufferLevel == 4);

    delete ohb;
}

/* 34 = MOST_HWMODE = "MOST hardware mode event" */
BOOST_AUTO_TEST_CASE(ObjectTypes_034)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_HWMODE);

    /* ObjectHeader2 */
    Vector::BLF::MostHwMode * obj = (Vector::BLF::MostHwMode *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader2::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    BOOST_CHECK(obj->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (34.000000 * timeFactor));
    //BOOST_CHECK(obj->originalTimeStamp == (uint64_t) (34.000000 * timeFactor));

    /* MostHwMode */
    BOOST_CHECK(obj->channel == 1);
    // reserved1
    BOOST_CHECK(obj->hwMode == 0x12);
    BOOST_CHECK(obj->hwModeMask == 0x34);

    delete ohb;
}

/* 36 = MOST_GENREG = "MOST register data (MOST register)" */
BOOST_AUTO_TEST_CASE(ObjectTypes_036)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_GENREG);

    /* ObjectHeader2 */
    Vector::BLF::MostGenReg * obj = (Vector::BLF::MostGenReg *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader2::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    BOOST_CHECK(obj->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (36.000000 * timeFactor));
    //BOOST_CHECK(obj->originalTimeStamp == (uint64_t) (36.000000 * timeFactor));

    /* MostGenReg */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->subType == 1);
    // reserved1
    BOOST_CHECK(obj->handle == 0);
    BOOST_CHECK(obj->regId == 0x23);
    // reserved2
    BOOST_CHECK(obj->regValue == 0x4567);

    delete ohb;
}

/* 37 = MOST_NETSTATE = "MOST NetState event" */
BOOST_AUTO_TEST_CASE(ObjectTypes_037)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_NETSTATE);

    /* ObjectHeader2 */
    Vector::BLF::MostNetState * obj = (Vector::BLF::MostNetState *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader2::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    BOOST_CHECK(obj->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (37.000000 * timeFactor));
    //BOOST_CHECK(obj->originalTimeStamp == (uint64_t) (37.000000 * timeFactor));

    /* MostNetState */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->stateNew == 3);
    BOOST_CHECK(obj->stateOld == 2);
    // reserved

    delete ohb;
}

/* 54 = LIN_STATISTIC = "LIN statistic event object" */
BOOST_AUTO_TEST_CASE(ObjectTypes_054)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_STATISTIC);

    /* ObjectHeader */
    Vector::BLF::LinStatisticEvent * obj = (Vector::BLF::LinStatisticEvent *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (54.000000 * timeFactor));

    /* LinStatisticEvent */
    BOOST_CHECK(obj->channel == 1);
    // reserved1
    BOOST_CHECK(obj->busLoad == 12.3456789);
    BOOST_CHECK(obj->burstsTotal == 1);
    BOOST_CHECK(obj->burstsOverrun == 2);
    BOOST_CHECK(obj->framesSent == 3);
    BOOST_CHECK(obj->framesReceived == 4);
    BOOST_CHECK(obj->framesUnanswered == 5);
    // reserved2

    delete ohb;
}

/* 57 = LIN_MESSAGE2 = "LIN frame object - extended" */
BOOST_AUTO_TEST_CASE(ObjectTypes_057)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);

    /* ObjectHeader */
    Vector::BLF::LinMessage2 * obj = (Vector::BLF::LinMessage2 *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 1);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (57.000000 * timeFactor));

    /* LinBusEvent */
    BOOST_CHECK(obj->sof == (uint64_t) (0.123456 * timeFactor));
    BOOST_CHECK(obj->eventBaudrate == 0);
    BOOST_CHECK(obj->channel == 4);
    // reserved

    /* LinSynchFieldEvent */
    BOOST_CHECK(obj->synchBreakLength == 0);
    BOOST_CHECK(obj->synchDelLength == 0);

    /* LinMessageDescriptor */
    BOOST_CHECK(obj->supplierId == 0);
    BOOST_CHECK(obj->messageId == 0);
    BOOST_CHECK(obj->nad == 0);
    BOOST_CHECK(obj->id == 1);
    BOOST_CHECK(obj->dlc == 1);
    BOOST_CHECK(obj->checksumModel == 1);

    /* LinDatabyteTimestampEvent */
    BOOST_CHECK(obj->databyteTimestamps[0] == 0);
    BOOST_CHECK(obj->databyteTimestamps[1] == 0);
    BOOST_CHECK(obj->databyteTimestamps[2] == (uint64_t) (0.123456 * timeFactor));
    BOOST_CHECK(obj->databyteTimestamps[3] == 0);
    BOOST_CHECK(obj->databyteTimestamps[4] == 0);
    BOOST_CHECK(obj->databyteTimestamps[5] == 0);
    BOOST_CHECK(obj->databyteTimestamps[6] == 0);
    BOOST_CHECK(obj->databyteTimestamps[7] == 0);
    BOOST_CHECK(obj->databyteTimestamps[8] == 0);

    /* LinMessage2 */
    BOOST_CHECK(obj->data[0] == 0xfe);
    BOOST_CHECK(obj->data[1] == 0xff);
    BOOST_CHECK(obj->data[2] == 0xff);
    BOOST_CHECK(obj->data[3] == 0xff);
    BOOST_CHECK(obj->data[4] == 0xff);
    BOOST_CHECK(obj->data[5] == 0xff);
    BOOST_CHECK(obj->data[6] == 0xff);
    BOOST_CHECK(obj->data[7] == 0xff);
    BOOST_CHECK(obj->crc == 0x3f);
    BOOST_CHECK(obj->dir == 1);
    BOOST_CHECK(obj->simulated == 1);
    BOOST_CHECK(obj->isEtf == 0);
    BOOST_CHECK(obj->etfAssocIndex == 0);
    // @todo the following information is not fully discovered yet
    BOOST_CHECK(obj->etfAssocEtfId == 0xff);   // ???
    BOOST_CHECK(obj->fsmId == 0xff);   // ???
    BOOST_CHECK(obj->fsmState == 0xff);    // ???
//    00 00 00      reserved
//    00 00 00 00   reserved_ver1_only
//    00 00 00 00   ???
//    00 00 00 00   ???
//    00 00 00 00   ???
//    00 00 00 00   ???
//                      respBaudrate (4)
//                      exactHeaderBaudrate (8)
//                      earlyStopbitOffset (4)
//                      earlyStopbitOffsetResponse (4)

    delete ohb;
}

/* 62 = LIN_WAKEUP2 = "LIN wakeup event object  - extended" */
BOOST_AUTO_TEST_CASE(ObjectTypes_062)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_WAKEUP2);

    /* ObjectHeader */
    Vector::BLF::LinWakeupEvent2 * obj = (Vector::BLF::LinWakeupEvent2 *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (62.000000 * timeFactor));

    /* LinBusEvent */
    BOOST_CHECK(obj->sof == (uint64_t) (62.000000 * timeFactor));
    BOOST_CHECK(obj->eventBaudrate == 2);
    BOOST_CHECK(obj->channel == 1);
    // reserved

    /* LinWakeupEvent2 */
    BOOST_CHECK(obj->lengthInfo == 0);
    BOOST_CHECK(obj->signal == 0x12);
    BOOST_CHECK(obj->external == 0);
    // reserved

    delete ohb;
}

/* 69 = MOST_ALLOCTAB = "MOST Allocation table event" */
BOOST_AUTO_TEST_CASE(ObjectTypes_069)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ALLOCTAB);

    /* ObjectHeader */
    Vector::BLF::MostAllocTab * obj = (Vector::BLF::MostAllocTab *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader2::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    BOOST_CHECK(obj->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (69.000000 * timeFactor));
    //BOOST_CHECK(obj->originalTimeStamp == (uint64_t) (69.000000 * timeFactor));

    /* MostAllocTable */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->length == 0x3c);
    // reserved
    BOOST_CHECK(obj->tableData[0x00] == 0x00);
    BOOST_CHECK(obj->tableData[0x01] == 0x01);
    BOOST_CHECK(obj->tableData[0x02] == 0x02);
    BOOST_CHECK(obj->tableData[0x03] == 0x03);
    BOOST_CHECK(obj->tableData[0x04] == 0x04);
    BOOST_CHECK(obj->tableData[0x05] == 0x05);
    BOOST_CHECK(obj->tableData[0x06] == 0x06);
    BOOST_CHECK(obj->tableData[0x07] == 0x07);
    BOOST_CHECK(obj->tableData[0x08] == 0x08);
    BOOST_CHECK(obj->tableData[0x09] == 0x09);
    BOOST_CHECK(obj->tableData[0x0a] == 0x0a);
    BOOST_CHECK(obj->tableData[0x0b] == 0x0b);
    BOOST_CHECK(obj->tableData[0x0c] == 0x0c);
    BOOST_CHECK(obj->tableData[0x0d] == 0x0d);
    BOOST_CHECK(obj->tableData[0x0e] == 0x0e);
    BOOST_CHECK(obj->tableData[0x0f] == 0x0f);
    BOOST_CHECK(obj->tableData[0x10] == 0x10);
    BOOST_CHECK(obj->tableData[0x11] == 0x11);
    BOOST_CHECK(obj->tableData[0x12] == 0x12);
    BOOST_CHECK(obj->tableData[0x13] == 0x13);
    BOOST_CHECK(obj->tableData[0x14] == 0x14);
    BOOST_CHECK(obj->tableData[0x15] == 0x15);
    BOOST_CHECK(obj->tableData[0x16] == 0x16);
    BOOST_CHECK(obj->tableData[0x17] == 0x17);
    BOOST_CHECK(obj->tableData[0x18] == 0x18);
    BOOST_CHECK(obj->tableData[0x19] == 0x19);
    BOOST_CHECK(obj->tableData[0x1a] == 0x1a);
    BOOST_CHECK(obj->tableData[0x1b] == 0x1b);
    BOOST_CHECK(obj->tableData[0x1c] == 0x1c);
    BOOST_CHECK(obj->tableData[0x1d] == 0x1d);
    BOOST_CHECK(obj->tableData[0x1e] == 0x1e);
    BOOST_CHECK(obj->tableData[0x1f] == 0x1f);
    BOOST_CHECK(obj->tableData[0x20] == 0x20);
    BOOST_CHECK(obj->tableData[0x21] == 0x21);
    BOOST_CHECK(obj->tableData[0x22] == 0x22);
    BOOST_CHECK(obj->tableData[0x23] == 0x23);
    BOOST_CHECK(obj->tableData[0x24] == 0x24);
    BOOST_CHECK(obj->tableData[0x25] == 0x25);
    BOOST_CHECK(obj->tableData[0x26] == 0x26);
    BOOST_CHECK(obj->tableData[0x27] == 0x27);
    BOOST_CHECK(obj->tableData[0x28] == 0x28);
    BOOST_CHECK(obj->tableData[0x29] == 0x29);
    BOOST_CHECK(obj->tableData[0x2a] == 0x2a);
    BOOST_CHECK(obj->tableData[0x2b] == 0x2b);
    BOOST_CHECK(obj->tableData[0x2c] == 0x2c);
    BOOST_CHECK(obj->tableData[0x2d] == 0x2d);
    BOOST_CHECK(obj->tableData[0x2e] == 0x2e);
    BOOST_CHECK(obj->tableData[0x2f] == 0x2f);
    BOOST_CHECK(obj->tableData[0x30] == 0x30);
    BOOST_CHECK(obj->tableData[0x31] == 0x31);
    BOOST_CHECK(obj->tableData[0x32] == 0x32);
    BOOST_CHECK(obj->tableData[0x33] == 0x33);
    BOOST_CHECK(obj->tableData[0x34] == 0x34);
    BOOST_CHECK(obj->tableData[0x35] == 0x35);
    BOOST_CHECK(obj->tableData[0x36] == 0x36);
    BOOST_CHECK(obj->tableData[0x37] == 0x37);
    BOOST_CHECK(obj->tableData[0x38] == 0x38);
    BOOST_CHECK(obj->tableData[0x39] == 0x39);
    BOOST_CHECK(obj->tableData[0x3a] == 0x3a);
    BOOST_CHECK(obj->tableData[0x3b] == 0x3b);

    delete ohb;
}

/* 73 = CAN_ERROR_EXT = "CAN error frame object (extended)" */
BOOST_AUTO_TEST_CASE(ObjectTypes_073)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);

    /* ObjectHeader */
    Vector::BLF::CanErrorFrameExt * obj = (Vector::BLF::CanErrorFrameExt *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (73.000000 * timeFactor));

    /* CanErrorExt */
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->length == 6);
    BOOST_CHECK(obj->flags == 1);
    BOOST_CHECK(obj->ecc == 1);
    BOOST_CHECK(obj->position == 0);
    BOOST_CHECK(obj->dlc == 0);
    // reserved1
    BOOST_CHECK(obj->frameLengthInNs == 0);
    //BOOST_CHECK(obj->id == 0);
    BOOST_CHECK(obj->flagsExt == 0x3001); // TX|1
    // reserved2
    //BOOST_CHECK(obj->data[0] == 0x00);
    //BOOST_CHECK(obj->data[1] == 0x00);
    //BOOST_CHECK(obj->data[2] == 0x00);
    //BOOST_CHECK(obj->data[3] == 0x00);
    //BOOST_CHECK(obj->data[4] == 0x00);
    //BOOST_CHECK(obj->data[5] == 0x00);
    //BOOST_CHECK(obj->data[6] == 0x00);
    //BOOST_CHECK(obj->data[7] == 0x00);

    delete ohb;
}

/* 97 = AFDX_FRAME */
BOOST_AUTO_TEST_CASE(ObjectTypes_097)
{
    /* ObjectHeaderBase */
    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->signature == Vector::BLF::ObjectSignature);
    BOOST_REQUIRE(ohb->headerSize == ohb->calculateHeaderSize());
    BOOST_REQUIRE(ohb->headerVersion == 1);
    BOOST_REQUIRE(ohb->objectSize == ohb->calculateObjectSize());
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);

    /* ObjectHeader */
    Vector::BLF::AfdxFrame * obj = (Vector::BLF::AfdxFrame *) ohb;
    uint64_t timeFactor = 0;
    switch (obj->objectFlags) {
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeTenMics:
        timeFactor = 10 * 1000 * 1000;
        break;
    case Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans:
        timeFactor = 1000 * 1000 * 1000;
        break;
    default:
        BOOST_ERROR("objectFlags");
    }
    // reserved
    BOOST_CHECK(obj->objectVersion == 0);
    BOOST_CHECK(obj->objectTimeStamp == (uint64_t) (97.000000 * timeFactor));

    /* AfdxFrame */
    BOOST_CHECK(obj->sourceAddress[0] == 0x11);
    BOOST_CHECK(obj->sourceAddress[1] == 0x22);
    BOOST_CHECK(obj->sourceAddress[2] == 0x33);
    BOOST_CHECK(obj->sourceAddress[3] == 0x44);
    BOOST_CHECK(obj->sourceAddress[4] == 0x55);
    BOOST_CHECK(obj->sourceAddress[5] == 0x66);
    BOOST_CHECK(obj->channel == 1);
    BOOST_CHECK(obj->destinationAddress[0] == 0x77);
    BOOST_CHECK(obj->destinationAddress[1] == 0x88);
    BOOST_CHECK(obj->destinationAddress[2] == 0x99);
    BOOST_CHECK(obj->destinationAddress[3] == 0xaa);
    BOOST_CHECK(obj->destinationAddress[4] == 0xbb);
    BOOST_CHECK(obj->destinationAddress[5] == 0xcc);
    BOOST_CHECK(obj->dir == Vector::BLF::AfdxFrame::Dir::Rx);
    BOOST_CHECK(obj->type == 0x0800);
    BOOST_CHECK(obj->tpid == 0x0000);
    BOOST_CHECK(obj->tci == 0x0000);
    BOOST_CHECK(obj->ethChannel == 0x01);
    // reserved1
    BOOST_CHECK(obj->afdxFlags == 0x0000);
    // reserved2
    BOOST_CHECK(obj->bagUsec == 0);
    BOOST_CHECK(obj->payLoadLength == 0x32);
    // reserved3
    BOOST_CHECK(obj->payLoad[0x00] == 0x00);
    BOOST_CHECK(obj->payLoad[0x01] == 0x01);
    BOOST_CHECK(obj->payLoad[0x02] == 0x02);
    BOOST_CHECK(obj->payLoad[0x03] == 0x03);
    BOOST_CHECK(obj->payLoad[0x04] == 0x04);
    BOOST_CHECK(obj->payLoad[0x05] == 0x05);
    BOOST_CHECK(obj->payLoad[0x06] == 0x06);
    BOOST_CHECK(obj->payLoad[0x07] == 0x07);
    BOOST_CHECK(obj->payLoad[0x08] == 0x08);
    BOOST_CHECK(obj->payLoad[0x09] == 0x09);
    BOOST_CHECK(obj->payLoad[0x0a] == 0x0a);
    BOOST_CHECK(obj->payLoad[0x0b] == 0x0b);
    BOOST_CHECK(obj->payLoad[0x0c] == 0x0c);
    BOOST_CHECK(obj->payLoad[0x0d] == 0x0d);
    BOOST_CHECK(obj->payLoad[0x0e] == 0x0e);
    BOOST_CHECK(obj->payLoad[0x0f] == 0x0f);
    BOOST_CHECK(obj->payLoad[0x10] == 0x10);
    BOOST_CHECK(obj->payLoad[0x11] == 0x11);
    BOOST_CHECK(obj->payLoad[0x12] == 0x12);
    BOOST_CHECK(obj->payLoad[0x13] == 0x13);
    BOOST_CHECK(obj->payLoad[0x14] == 0x14);
    BOOST_CHECK(obj->payLoad[0x15] == 0x15);
    BOOST_CHECK(obj->payLoad[0x16] == 0x16);
    BOOST_CHECK(obj->payLoad[0x17] == 0x17);
    BOOST_CHECK(obj->payLoad[0x18] == 0x18);
    BOOST_CHECK(obj->payLoad[0x19] == 0x19);
    BOOST_CHECK(obj->payLoad[0x1a] == 0x1a);
    BOOST_CHECK(obj->payLoad[0x1b] == 0x1b);
    BOOST_CHECK(obj->payLoad[0x1c] == 0x1c);
    BOOST_CHECK(obj->payLoad[0x1d] == 0x1d);
    BOOST_CHECK(obj->payLoad[0x1e] == 0x1e);
    BOOST_CHECK(obj->payLoad[0x1f] == 0x1f);
    BOOST_CHECK(obj->payLoad[0x20] == 0x20);
    BOOST_CHECK(obj->payLoad[0x21] == 0x21);
    BOOST_CHECK(obj->payLoad[0x22] == 0x22);
    BOOST_CHECK(obj->payLoad[0x23] == 0x23);
    BOOST_CHECK(obj->payLoad[0x24] == 0x24);
    BOOST_CHECK(obj->payLoad[0x25] == 0x25);
    BOOST_CHECK(obj->payLoad[0x26] == 0x26);
    BOOST_CHECK(obj->payLoad[0x27] == 0x27);
    BOOST_CHECK(obj->payLoad[0x28] == 0x28);
    BOOST_CHECK(obj->payLoad[0x29] == 0x29);
    BOOST_CHECK(obj->payLoad[0x2a] == 0x2a);
    BOOST_CHECK(obj->payLoad[0x2b] == 0x2b);
    BOOST_CHECK(obj->payLoad[0x2c] == 0x2c);
    BOOST_CHECK(obj->payLoad[0x2d] == 0x2d);
    BOOST_CHECK(obj->payLoad[0x2e] == 0x2e);
    BOOST_CHECK(obj->payLoad[0x2f] == 0x2f);
    BOOST_CHECK(obj->payLoad[0x30] == 0x30);
    BOOST_CHECK(obj->payLoad[0x31] == 0x31);

    delete ohb;
}

BOOST_AUTO_TEST_CASE(CloseLogfile)
{
    /* check file statistics */
    BOOST_CHECK(file.fileStatistics.uncompressedFileSize == file.currentUncompressedFileSize);
    BOOST_CHECK(file.fileStatistics.objectCount == file.currentObjectCount);

    /* close file */
    file.close();
}
