#define BOOST_TEST_MODULE MostNetState
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_NETSTATE = 37 */
BOOST_AUTO_TEST_CASE(MostNetState)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostNetState.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostNetState * mostNetState;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_NETSTATE);
    mostNetState = static_cast<Vector::BLF::MostNetState *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostNetState->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostNetState->headerSize == mostNetState->calculateHeaderSize());
    BOOST_CHECK(mostNetState->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostNetState->objectSize == mostNetState->calculateObjectSize());
    BOOST_CHECK(mostNetState->objectType == Vector::BLF::ObjectType::MOST_NETSTATE);
    /* ObjectHeader2 */
    BOOST_CHECK(mostNetState->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostNetState->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostNetState->objectVersion == 0);
    BOOST_CHECK(mostNetState->objectTimeStamp == 1027900000); // ns
    BOOST_CHECK(mostNetState->originalTimeStamp == 0);
    /* MostNetState */
    BOOST_CHECK(mostNetState->channel == 1);
    BOOST_CHECK(mostNetState->stateNew == 3); // NetInterfaceInit
    BOOST_CHECK(mostNetState->stateOld == 2); // PowerOff
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
