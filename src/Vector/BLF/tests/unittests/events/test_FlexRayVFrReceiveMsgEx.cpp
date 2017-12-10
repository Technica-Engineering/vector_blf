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

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrReceiveMsgEx * flexRayVFrReceiveMsgEx;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    flexRayVFrReceiveMsgEx = static_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerSize == flexRayVFrReceiveMsgEx->calculateHeaderSize());
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerVersion == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectSize == flexRayVFrReceiveMsgEx->calculateObjectSize());
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    /* ObjectHeader */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectVersion == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectTimeStamp == 42000000); // ns
    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channel == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->version == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channelMask == 1); // FlexRay Channel A
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dir == 0); // Rx
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clientIndex == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clusterNo == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameId == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc1 == 151);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc2 == 151);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->byteCount == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataCount == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->cycle == 25);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->tag == 2);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->data == 0x00d0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameFlags == 0x06);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->appParameter == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameCrc == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameLengthNs == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameId1 == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->pduOffset == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->blfLogMask == 0);
    // reserved
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x00] == 21);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x01] == 87);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x02] == 22);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x03] == 148);
    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    flexRayVFrReceiveMsgEx = static_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerSize == flexRayVFrReceiveMsgEx->calculateHeaderSize());
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerVersion == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectSize == flexRayVFrReceiveMsgEx->calculateObjectSize());
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    /* ObjectHeader */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectVersion == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->objectTimeStamp == 42600000); // ns
    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channel == 2);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->version == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->channelMask == 2); // FlexRay Channel B
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dir == 0); // Rx
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clientIndex == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->clusterNo == 1);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameId == 13);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc1 == 620);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->headerCrc2 == 620);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->byteCount == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataCount == 4);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->cycle == 25);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->tag == 2);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->data == 0x0180);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameFlags == 0x02);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->appParameter == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameCrc == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameLengthNs == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->frameId1 == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->pduOffset == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->blfLogMask == 0);
    // reserved
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x00] == 2);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x01] == 89);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x02] == 0);
    BOOST_CHECK(flexRayVFrReceiveMsgEx->dataBytes[0x03] == 13);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
