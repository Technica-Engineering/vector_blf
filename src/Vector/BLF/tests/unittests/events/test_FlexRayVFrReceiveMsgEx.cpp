#define BOOST_TEST_MODULE FlexRayVFrReceiveMsgEx
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

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
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->version, 0x2222);
    BOOST_CHECK_EQUAL(obj->channelMask, 0x3333);
    BOOST_CHECK_EQUAL(obj->dir, 0x4444);
    BOOST_CHECK_EQUAL(obj->clientIndexFlexRayVFrReceiveMsgEx, 0x55555555);
    BOOST_CHECK_EQUAL(obj->clusterNo, 0x66666666);
    BOOST_CHECK_EQUAL(obj->frameId, 0x7777);
    BOOST_CHECK_EQUAL(obj->headerCrc1, 0x8888);
    BOOST_CHECK_EQUAL(obj->headerCrc2, 0x9999);
    BOOST_CHECK_EQUAL(obj->byteCount, 0xAAAA);
    BOOST_CHECK_EQUAL(obj->dataCount, 0xBBBB);
    BOOST_CHECK_EQUAL(obj->cycle, 0xCCCC);
    BOOST_CHECK_EQUAL(obj->tag, 0xDDDDDDDD);
    BOOST_CHECK_EQUAL(obj->data, 0xEEEEEEEE);
    BOOST_CHECK_EQUAL(obj->frameFlags, 0xFFFFFFFF);
    BOOST_CHECK_EQUAL(obj->appParameter, 0x11111111);
    BOOST_CHECK_EQUAL(obj->frameCrc, 0x22222222);
    BOOST_CHECK_EQUAL(obj->frameLengthNs, 0x33333333);
    BOOST_CHECK_EQUAL(obj->frameId1, 0x4444);
    BOOST_CHECK_EQUAL(obj->pduOffset, 0x5555);
    BOOST_CHECK_EQUAL(obj->blfLogMask, 0x6666);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1, 0x7777);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx2[0], 0x88888888);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx2[1], 0x99999999);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx2[2], 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx2[3], 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx2[4], 0xCCCCCCCC);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx2[5], 0xDDDDDDDD);
    for (uint8_t i = 0; i < 254; i++) {
        BOOST_CHECK_EQUAL(obj->dataBytes[i], i);
    }
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx3, 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx4, 0);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);

    delete ohb;

    file.close();
}
