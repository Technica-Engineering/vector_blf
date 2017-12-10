#define BOOST_TEST_MODULE GpsEvent
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

/* GPS_EVENT = 46 */
BOOST_AUTO_TEST_CASE(GpsEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_GpsEvent.blf");
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
