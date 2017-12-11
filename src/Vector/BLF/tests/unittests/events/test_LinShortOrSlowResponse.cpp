#define BOOST_TEST_MODULE LinShortOrSlowResponse
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_SHORT_OR_SLOW_RESPONSE = 88 */
BOOST_AUTO_TEST_CASE(LinShortOrSlowResponse)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinShortOrSlowResponse.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE);
    Vector::BLF::LinShortOrSlowResponse * obj = static_cast<Vector::BLF::LinShortOrSlowResponse *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1298765000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 1279516000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 19230);
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved

    /* LinSynchFieldEvent */
    BOOST_CHECK_EQUAL(obj->synchBreakLength, 937250);
    BOOST_CHECK_EQUAL(obj->synchDelLength, 102625);

    /* LinMessageDescriptor */
    BOOST_CHECK_EQUAL(obj->supplierId, 0);
    BOOST_CHECK_EQUAL(obj->messageId, 0);
    BOOST_CHECK_EQUAL(obj->nad, 0);
    BOOST_CHECK_EQUAL(obj->id, 1);
    BOOST_CHECK_EQUAL(obj->dlc, 8);
    BOOST_CHECK_EQUAL(obj->checksumModel, 0xff);

    /* LinDatabyteTimestampEvent */
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[0], 1281570000); // ns
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[1], 1283679000); // ns
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[2], 1285759000); // ns
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[3], 1287839000); // ns
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[4], 1289927000); // ns
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[5], 1292007000); // ns
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[6], 1294087000); // ns
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[7], 1296167000); // ns
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[8], 1298244000); // ns

    /* LinShortOrSlowResponse */
    BOOST_CHECK_EQUAL(obj->numberOfRespBytes, 9);
    BOOST_CHECK_EQUAL(obj->respBytes[0], 0x11);
    BOOST_CHECK_EQUAL(obj->respBytes[1], 0x12);
    BOOST_CHECK_EQUAL(obj->respBytes[2], 0x13);
    BOOST_CHECK_EQUAL(obj->respBytes[3], 0x14);
    BOOST_CHECK_EQUAL(obj->respBytes[4], 0x15);
    BOOST_CHECK_EQUAL(obj->respBytes[5], 0x16);
    BOOST_CHECK_EQUAL(obj->respBytes[6], 0x17);
    BOOST_CHECK_EQUAL(obj->respBytes[7], 0x18);
    BOOST_CHECK_EQUAL(obj->respBytes[8], 0x99);
    BOOST_CHECK_EQUAL(obj->slowResponse, 1);
    BOOST_CHECK_EQUAL(obj->interruptedByBreak, 0);
    // reserved

    delete obj;

    file.close();
}
