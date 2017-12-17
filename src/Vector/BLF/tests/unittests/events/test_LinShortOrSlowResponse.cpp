#define BOOST_TEST_MODULE LinShortOrSlowResponse
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

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
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 0x1111111111111111);
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 0x22222222);
    BOOST_CHECK_EQUAL(obj->channel, 0x3333);
    BOOST_CHECK_EQUAL(obj->reservedLinBusEvent, 0x4444);

    /* LinSynchFieldEvent */
    BOOST_CHECK_EQUAL(obj->synchBreakLength, 0x1111111111111111);
    BOOST_CHECK_EQUAL(obj->synchDelLength, 0x2222222222222222);

    /* LinMessageDescriptor */
    BOOST_CHECK_EQUAL(obj->supplierId, 0x1111);
    BOOST_CHECK_EQUAL(obj->messageId, 0x2222);
    BOOST_CHECK_EQUAL(obj->nad, 0x33);
    BOOST_CHECK_EQUAL(obj->id, 0x44);
    BOOST_CHECK_EQUAL(obj->dlc, 0x55);
    BOOST_CHECK_EQUAL(obj->checksumModel, 0x66);

    /* LinDatabyteTimestampEvent */
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[0], 0x1111111111111111);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[1], 0x2222222222222222);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[2], 0x3333333333333333);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[3], 0x4444444444444444);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[4], 0x5555555555555555);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[5], 0x6666666666666666);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[6], 0x7777777777777777);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[7], 0x8888888888888888);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[8], 0x9999999999999999);

    /* LinShortOrSlowResponse */
    BOOST_CHECK_EQUAL(obj->numberOfRespBytes, 0x11111111);
    BOOST_CHECK_EQUAL(obj->respBytes[0], 0x0);
    BOOST_CHECK_EQUAL(obj->respBytes[1], 0x1);
    BOOST_CHECK_EQUAL(obj->respBytes[2], 0x2);
    BOOST_CHECK_EQUAL(obj->respBytes[3], 0x3);
    BOOST_CHECK_EQUAL(obj->respBytes[4], 0x4);
    BOOST_CHECK_EQUAL(obj->respBytes[5], 0x5);
    BOOST_CHECK_EQUAL(obj->respBytes[6], 0x6);
    BOOST_CHECK_EQUAL(obj->respBytes[7], 0x7);
    BOOST_CHECK_EQUAL(obj->respBytes[8], 0x8);
    BOOST_CHECK_EQUAL(obj->slowResponse, 0x22);
    BOOST_CHECK_EQUAL(obj->interruptedByBreak, 0x33);
    BOOST_CHECK_EQUAL(obj->reservedLinShortOrSlowResponse, 0x44);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE);

    delete ohb;

    file.close();
}
