#define BOOST_TEST_MODULE LinDisturbanceEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_DISTURBANCE_EVENT = 89 */
BOOST_AUTO_TEST_CASE(LinDisturbanceEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinDisturbanceEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_DISTURBANCE_EVENT);
    Vector::BLF::LinDisturbanceEvent * obj = static_cast<Vector::BLF::LinDisturbanceEvent *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_DISTURBANCE_EVENT);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1323661000); // ns

    /* LinDisturbanceEvent */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->id, 0x2D);
    BOOST_CHECK_EQUAL(obj->disturbingFrameId, 0xFF);
    BOOST_CHECK_EQUAL(obj->disturbanceType, 0); // dominant disturbance
    BOOST_CHECK_EQUAL(obj->byteIndex, 1);
    BOOST_CHECK_EQUAL(obj->bitIndex, 6);
    BOOST_CHECK_EQUAL(obj->bitOffsetInSixteenthBits, 0);
    BOOST_CHECK_EQUAL(obj->disturbanceLengthInSixteenthBits, 16);

    delete obj;

    file.close();
}
