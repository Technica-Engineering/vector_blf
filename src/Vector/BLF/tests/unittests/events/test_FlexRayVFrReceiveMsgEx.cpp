#define BOOST_TEST_MODULE FlexRayVFrReceiveMsgEx
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* FR_RCVMESSAGE_EX = 66 */
BOOST_AUTO_TEST_CASE(FlexRayVFrReceiveMsgEx)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_FlexRayVFrReceiveMsgEx.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    Vector::BLF::FlexRayVFrReceiveMsgEx * obj = static_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 42000000); // ns

    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->version, 1);
    BOOST_CHECK_EQUAL(obj->channelMask, 1); // FlexRay Channel A
    BOOST_CHECK_EQUAL(obj->dir, 0); // Rx
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->clusterNo, 0);
    BOOST_CHECK_EQUAL(obj->frameId, 4);
    BOOST_CHECK_EQUAL(obj->headerCrc1, 151);
    BOOST_CHECK_EQUAL(obj->headerCrc2, 151);
    BOOST_CHECK_EQUAL(obj->byteCount, 4);
    BOOST_CHECK_EQUAL(obj->dataCount, 4);
    BOOST_CHECK_EQUAL(obj->cycle, 25);
    BOOST_CHECK_EQUAL(obj->tag, 2);
    BOOST_CHECK_EQUAL(obj->data, 0x00d0);
    BOOST_CHECK_EQUAL(obj->frameFlags, 0x06);
    BOOST_CHECK_EQUAL(obj->appParameter, 0);
    BOOST_CHECK_EQUAL(obj->frameCrc, 0);
    BOOST_CHECK_EQUAL(obj->frameLengthNs, 0);
    BOOST_CHECK_EQUAL(obj->frameId1, 0);
    BOOST_CHECK_EQUAL(obj->pduOffset, 0);
    BOOST_CHECK_EQUAL(obj->blfLogMask, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->dataBytes[0x00], 21);
    BOOST_CHECK_EQUAL(obj->dataBytes[0x01], 87);
    BOOST_CHECK_EQUAL(obj->dataBytes[0x02], 22);
    BOOST_CHECK_EQUAL(obj->dataBytes[0x03], 148);

    delete obj;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    obj = static_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 42600000); // ns

    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK_EQUAL(obj->channel, 2);
    BOOST_CHECK_EQUAL(obj->version, 1);
    BOOST_CHECK_EQUAL(obj->channelMask, 2); // FlexRay Channel B
    BOOST_CHECK_EQUAL(obj->dir, 0); // Rx
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->clusterNo, 1);
    BOOST_CHECK_EQUAL(obj->frameId, 13);
    BOOST_CHECK_EQUAL(obj->headerCrc1, 620);
    BOOST_CHECK_EQUAL(obj->headerCrc2, 620);
    BOOST_CHECK_EQUAL(obj->byteCount, 4);
    BOOST_CHECK_EQUAL(obj->dataCount, 4);
    BOOST_CHECK_EQUAL(obj->cycle, 25);
    BOOST_CHECK_EQUAL(obj->tag, 2);
    BOOST_CHECK_EQUAL(obj->data, 0x0180);
    BOOST_CHECK_EQUAL(obj->frameFlags, 0x02);
    BOOST_CHECK_EQUAL(obj->appParameter, 0);
    BOOST_CHECK_EQUAL(obj->frameCrc, 0);
    BOOST_CHECK_EQUAL(obj->frameLengthNs, 0);
    BOOST_CHECK_EQUAL(obj->frameId1, 0);
    BOOST_CHECK_EQUAL(obj->pduOffset, 0);
    BOOST_CHECK_EQUAL(obj->blfLogMask, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->dataBytes[0x00], 2);
    BOOST_CHECK_EQUAL(obj->dataBytes[0x01], 89);
    BOOST_CHECK_EQUAL(obj->dataBytes[0x02], 0);
    BOOST_CHECK_EQUAL(obj->dataBytes[0x03], 13);

    delete obj;

    file.close();
}
