#define BOOST_TEST_MODULE LinReceiveError2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_RCV_ERROR2 = 61 */
BOOST_AUTO_TEST_CASE(LinReceiveError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinReceiveError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR2);
    Vector::BLF::LinReceiveError2 * obj = static_cast<Vector::BLF::LinReceiveError2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR2);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 554673000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 546052000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 19230);
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved

    /* LinSynchFieldEvent */
    BOOST_CHECK_EQUAL(obj->synchBreakLength, 937187);
    BOOST_CHECK_EQUAL(obj->synchDelLength, 112437);
    /* LinReceiveError2 */
    BOOST_CHECK_EQUAL(obj->supplierId, 0);
    BOOST_CHECK_EQUAL(obj->messageId, 0);
    BOOST_CHECK_EQUAL(obj->nad, 0);
    BOOST_CHECK_EQUAL(obj->id, 0x33);
    BOOST_CHECK_EQUAL(obj->dlc, 8);
    BOOST_CHECK_EQUAL(obj->checksumModel, 0xff);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[0], 548121000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[1], 548644000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[2], 549167000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[3], 549690000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[4], 550213000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[5], 550736000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[6], 551259000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[7], 551782000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[8], 552305000);
    BOOST_CHECK_EQUAL(obj->data[0], 0x05);
    BOOST_CHECK_EQUAL(obj->data[1], 0x00);
    BOOST_CHECK_EQUAL(obj->data[2], 0x00);
    BOOST_CHECK_EQUAL(obj->data[3], 0x00);
    BOOST_CHECK_EQUAL(obj->data[4], 0x00);
    BOOST_CHECK_EQUAL(obj->data[5], 0xff);
    BOOST_CHECK_EQUAL(obj->data[6], 0xff);
    BOOST_CHECK_EQUAL(obj->data[7], 0xff);
    BOOST_CHECK_EQUAL(obj->fsmId, 0xff);
    BOOST_CHECK_EQUAL(obj->fsmState, 0xff);
    BOOST_CHECK_EQUAL(obj->stateReason, 12);
    BOOST_CHECK_EQUAL(obj->offendingByte, 0);
    BOOST_CHECK_EQUAL(obj->shortError, 0);
    BOOST_CHECK_EQUAL(obj->timeoutDuringDlcDetection, 0);
    BOOST_CHECK_EQUAL(obj->isEtf, 0);
    BOOST_CHECK_EQUAL(obj->hasDatabytes, 1);
    BOOST_CHECK_EQUAL(obj->respBaudrate, 19231);
    // reserved
    BOOST_CHECK_EQUAL(obj->exactHeaderBaudrate, 19230.769231);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffset, 26000);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffsetResponse, 26000);

    delete obj;

    file.close();
}
