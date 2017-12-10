#define BOOST_TEST_MODULE LinSleepModeEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_SLEEP = 20 */
BOOST_AUTO_TEST_CASE(LinSleepModeEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinSleepModeEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSleepModeEvent * linSleepModeEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SLEEP);
    linSleepModeEvent = static_cast<Vector::BLF::LinSleepModeEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSleepModeEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSleepModeEvent->headerSize == linSleepModeEvent->calculateHeaderSize());
    BOOST_CHECK(linSleepModeEvent->headerVersion == 1);
    BOOST_CHECK(linSleepModeEvent->objectSize == linSleepModeEvent->calculateObjectSize());
    BOOST_CHECK(linSleepModeEvent->objectType == Vector::BLF::ObjectType::LIN_SLEEP);
    /* ObjectHeader */
    BOOST_CHECK(linSleepModeEvent->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linSleepModeEvent->objectVersion == 0);
    BOOST_CHECK(linSleepModeEvent->objectTimeStamp == 777200000); // ns
    /* LinSleepModeEvent */
    BOOST_CHECK(linSleepModeEvent->channel == 1);
    BOOST_CHECK(linSleepModeEvent->reason == 1);
    BOOST_CHECK(linSleepModeEvent->flags == (uint8_t) Vector::BLF::LinSleepModeEvent::Flags::WasAwake);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
