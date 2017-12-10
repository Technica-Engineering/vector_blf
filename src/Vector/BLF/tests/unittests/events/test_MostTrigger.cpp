#define BOOST_TEST_MODULE MostTrigger
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_TRIGGER = 39 */
BOOST_AUTO_TEST_CASE(MostTrigger)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostTrigger.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostTrigger * mostTrigger;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_TRIGGER);
    mostTrigger = static_cast<Vector::BLF::MostTrigger *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostTrigger->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostTrigger->headerSize == mostTrigger->calculateHeaderSize());
    BOOST_CHECK(mostTrigger->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostTrigger->objectSize == mostTrigger->calculateObjectSize());
    BOOST_CHECK(mostTrigger->objectType == Vector::BLF::ObjectType::MOST_TRIGGER);
    /* ObjectHeader2 */
    BOOST_CHECK(mostTrigger->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostTrigger->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostTrigger->objectVersion == 0);
    BOOST_CHECK(mostTrigger->objectTimeStamp == 1303700000); // ns
    BOOST_CHECK(mostTrigger->originalTimeStamp == 0);
    /* MostTrigger */
    BOOST_CHECK(mostTrigger->channel == 1);
    // reserved
    BOOST_CHECK(mostTrigger->mode == 2); // synchronization slave
    BOOST_CHECK(mostTrigger->hw == 4); // VN2600/VN2610
    BOOST_CHECK(mostTrigger->previousTriggerValue == 1);
    BOOST_CHECK(mostTrigger->currentTriggerValue == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
