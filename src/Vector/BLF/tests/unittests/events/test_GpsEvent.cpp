#define BOOST_TEST_MODULE GpsEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* GPS_EVENT = 46 */
BOOST_AUTO_TEST_CASE(GpsEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_GpsEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::GPS_EVENT);
    Vector::BLF::GpsEvent * obj = static_cast<Vector::BLF::GpsEvent *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::GPS_EVENT);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* GpsEvent */
    BOOST_CHECK_EQUAL(obj->flags, 0x11111111);
    BOOST_CHECK_EQUAL(obj->channel, 0x2222);
    BOOST_CHECK_EQUAL(obj->reserved, 0x3333);
    BOOST_CHECK_EQUAL(obj->latitude, 4.0);
    BOOST_CHECK_EQUAL(obj->longitude, 5.0);
    BOOST_CHECK_EQUAL(obj->altitude, 6.0);
    BOOST_CHECK_EQUAL(obj->speed, 7.0);
    BOOST_CHECK_EQUAL(obj->course, 8.0);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::GPS_EVENT);

    delete ohb;

    file.close();
}
