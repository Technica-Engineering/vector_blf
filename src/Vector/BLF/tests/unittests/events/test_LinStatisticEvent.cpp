#define BOOST_TEST_MODULE LinStatisticEvent
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

/* LIN_STATISTIC = 54 */
BOOST_AUTO_TEST_CASE(LinStatisticEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinStatisticEvent.blf");
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
