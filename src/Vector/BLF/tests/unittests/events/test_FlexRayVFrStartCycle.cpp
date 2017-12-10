#define BOOST_TEST_MODULE FlexRayVFrStartCycle
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* FR_STARTCYCLE = 49 */
BOOST_AUTO_TEST_CASE(FlexRayVFrStartCycle)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_FlexRayVFrStartCycle.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrStartCycle * flexRayVFrStartCycle;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);
    flexRayVFrStartCycle = static_cast<Vector::BLF::FlexRayVFrStartCycle *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(flexRayVFrStartCycle->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(flexRayVFrStartCycle->headerSize == flexRayVFrStartCycle->calculateHeaderSize());
    BOOST_CHECK(flexRayVFrStartCycle->headerVersion == 1);
    BOOST_CHECK(flexRayVFrStartCycle->objectSize == flexRayVFrStartCycle->calculateObjectSize());
    BOOST_CHECK(flexRayVFrStartCycle->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);
    /* ObjectHeader */
    BOOST_CHECK(flexRayVFrStartCycle->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(flexRayVFrStartCycle->objectVersion == 0);
    BOOST_CHECK(flexRayVFrStartCycle->objectTimeStamp == 41700000); // ns
    /* FlexRayVFrStartCycle */
    BOOST_CHECK(flexRayVFrStartCycle->channel == 0);
    BOOST_CHECK(flexRayVFrStartCycle->version == 2);
    BOOST_CHECK(flexRayVFrStartCycle->channelMask == 0); // reserved/invalid
    BOOST_CHECK(flexRayVFrStartCycle->dir == 0); // Rx
    BOOST_CHECK(flexRayVFrStartCycle->cycle == 0);
    BOOST_CHECK(flexRayVFrStartCycle->clientIndex == 0);
    BOOST_CHECK(flexRayVFrStartCycle->clusterNo == 0xffffffff);
    BOOST_CHECK(flexRayVFrStartCycle->nmSize == 2);
    BOOST_CHECK(flexRayVFrStartCycle->dataBytes[0] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->dataBytes[1] == 0);
    // reserved
    BOOST_CHECK(flexRayVFrStartCycle->tag == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[0] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[1] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[2] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[3] == 0);
    BOOST_CHECK(flexRayVFrStartCycle->data[4] == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
