#define BOOST_TEST_MODULE FlexRayVFrStartCycle
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* FR_STARTCYCLE = 49 */
BOOST_AUTO_TEST_CASE(FlexRayVFrStartCycle)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_FlexRayVFrStartCycle.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);
    Vector::BLF::FlexRayVFrStartCycle * obj = static_cast<Vector::BLF::FlexRayVFrStartCycle *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 41700000); // ns

    /* FlexRayVFrStartCycle */
    BOOST_CHECK_EQUAL(obj->channel, 0);
    BOOST_CHECK_EQUAL(obj->version, 2);
    BOOST_CHECK_EQUAL(obj->channelMask, 0); // reserved/invalid
    BOOST_CHECK_EQUAL(obj->dir, 0); // Rx
    BOOST_CHECK_EQUAL(obj->cycle, 0);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->clusterNo, 0xffffffff);
    BOOST_CHECK_EQUAL(obj->nmSize, 2);
    BOOST_CHECK_EQUAL(obj->dataBytes[0], 0);
    BOOST_CHECK_EQUAL(obj->dataBytes[1], 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->tag, 0);
    BOOST_CHECK_EQUAL(obj->data[0], 0);
    BOOST_CHECK_EQUAL(obj->data[1], 0);
    BOOST_CHECK_EQUAL(obj->data[2], 0);
    BOOST_CHECK_EQUAL(obj->data[3], 0);
    BOOST_CHECK_EQUAL(obj->data[4], 0);
    // reserved

    delete obj;

    file.close();
}
