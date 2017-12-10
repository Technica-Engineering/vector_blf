#define BOOST_TEST_MODULE LinDisturbanceEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_DISTURBANCE_EVENT = 89 */
BOOST_AUTO_TEST_CASE(LinDisturbanceEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinDisturbanceEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinDisturbanceEvent * linDisturbanceEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_DISTURBANCE_EVENT);
    linDisturbanceEvent = static_cast<Vector::BLF::LinDisturbanceEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linDisturbanceEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linDisturbanceEvent->headerSize == linDisturbanceEvent->calculateHeaderSize());
    BOOST_CHECK(linDisturbanceEvent->headerVersion == 1);
    BOOST_CHECK(linDisturbanceEvent->objectSize == linDisturbanceEvent->calculateObjectSize());
    BOOST_CHECK(linDisturbanceEvent->objectType == Vector::BLF::ObjectType::LIN_DISTURBANCE_EVENT);
    /* ObjectHeader */
    BOOST_CHECK(linDisturbanceEvent->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linDisturbanceEvent->objectVersion == 0);
    BOOST_CHECK(linDisturbanceEvent->objectTimeStamp == 1323661000); // ns
    /* LinDisturbanceEvent */
    BOOST_CHECK(linDisturbanceEvent->channel == 1);
    BOOST_CHECK(linDisturbanceEvent->id == 0x2D);
    BOOST_CHECK(linDisturbanceEvent->disturbingFrameId == 0xFF);
    BOOST_CHECK(linDisturbanceEvent->disturbanceType == 0); // dominant disturbance
    BOOST_CHECK(linDisturbanceEvent->byteIndex == 1);
    BOOST_CHECK(linDisturbanceEvent->bitIndex == 6);
    BOOST_CHECK(linDisturbanceEvent->bitOffsetInSixteenthBits == 0);
    BOOST_CHECK(linDisturbanceEvent->disturbanceLengthInSixteenthBits == 16);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
