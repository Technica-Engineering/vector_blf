#define BOOST_TEST_MODULE LinReceiveError2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

static bool isEqual(double a, double b)
{
    return ((a - b) < 0.000001) && ((b - a) < 0.000001);
}

/* LIN_RCV_ERROR2 = 61 */
BOOST_AUTO_TEST_CASE(LinReceiveError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinReceiveError2.blf");
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
