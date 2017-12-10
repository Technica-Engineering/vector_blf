#define BOOST_TEST_MODULE MostSystemEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_SYSTEM_EVENT = 82 */
BOOST_AUTO_TEST_CASE(MostSystemEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostSystemEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostSystemEvent * mostSystemEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_SYSTEM_EVENT);
    mostSystemEvent = static_cast<Vector::BLF::MostSystemEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostSystemEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostSystemEvent->headerSize == mostSystemEvent->calculateHeaderSize());
    BOOST_CHECK(mostSystemEvent->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostSystemEvent->objectSize == mostSystemEvent->calculateObjectSize());
    BOOST_CHECK(mostSystemEvent->objectType == Vector::BLF::ObjectType::MOST_SYSTEM_EVENT);
    /* ObjectHeader2 */
    BOOST_CHECK(mostSystemEvent->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostSystemEvent->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostSystemEvent->objectVersion == 0);
    BOOST_CHECK(mostSystemEvent->objectTimeStamp == 1027900000); // ns
    BOOST_CHECK(mostSystemEvent->originalTimeStamp == 0);
    /* MostSystemEvent */
    mostSystemEvent = static_cast<Vector::BLF::MostSystemEvent *>(ohb);
    BOOST_CHECK(mostSystemEvent->channel == 1);
    BOOST_CHECK(mostSystemEvent->id == 1);
    BOOST_CHECK(mostSystemEvent->value == 1);
    BOOST_CHECK(mostSystemEvent->valueOld == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
