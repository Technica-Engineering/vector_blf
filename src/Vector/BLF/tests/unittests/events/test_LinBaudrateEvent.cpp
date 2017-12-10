#define BOOST_TEST_MODULE LinBaudrateEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_BAUDRATE = 19 */
BOOST_AUTO_TEST_CASE(LinBaudrateEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinBaudrateEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinBaudrateEvent * linBaudrateEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_BAUDRATE);
    linBaudrateEvent = static_cast<Vector::BLF::LinBaudrateEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linBaudrateEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linBaudrateEvent->headerSize == linBaudrateEvent->calculateHeaderSize());
    BOOST_CHECK(linBaudrateEvent->headerVersion == 1);
    BOOST_CHECK(linBaudrateEvent->objectSize == linBaudrateEvent->calculateObjectSize());
    BOOST_CHECK(linBaudrateEvent->objectType == Vector::BLF::ObjectType::LIN_BAUDRATE);
    /* ObjectHeader */
    BOOST_CHECK(linBaudrateEvent->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linBaudrateEvent->objectVersion == 0);
    BOOST_CHECK(linBaudrateEvent->objectTimeStamp == 18800000); // ns
    /* LinBaudrate */
    BOOST_CHECK(linBaudrateEvent->channel == 1);
    // reserved
    BOOST_CHECK(linBaudrateEvent->baudrate == 9615);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
