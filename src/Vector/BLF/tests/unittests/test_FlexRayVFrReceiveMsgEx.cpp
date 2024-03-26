// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE FlexRayVFrReceiveMsgEx
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* FR_RCVMESSAGE_EX = 66 */
BOOST_AUTO_TEST_CASE(FlexRayVFrReceiveMsgEx_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_FlexRayVFrReceiveMsgEx.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    auto * obj = dynamic_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
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
    BOOST_CHECK_EQUAL(obj->dataCount, 254);
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
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 0], 0x7777);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 1], 0x8888);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 2], 0x8888);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 3], 0x9999);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 4], 0x9999);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 5], 0xAAAA);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 6], 0xAAAA);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 7], 0xBBBB);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 8], 0xBBBB);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 9], 0xCCCC);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[10], 0xCCCC);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[11], 0xDDDD);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[12], 0xDDDD);
    for (uint8_t i = 0; i < 254; i++)
        BOOST_CHECK_EQUAL(obj->dataBytes[i], i);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx2.size(), 0);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);

    delete ohb;

    /* read last */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::Unknown115);

    delete ohb;

    /* read last */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::Unknown115);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayVFrReceiveMsgEx_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_FlexRayVFrReceiveMsgEx.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    auto * obj = dynamic_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 42000000); // ns

    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->version, 1);
    BOOST_CHECK_EQUAL(obj->channelMask, 1); // FlexRay Channel A
    BOOST_CHECK_EQUAL(obj->dir, 0); // Rx
    BOOST_CHECK_EQUAL(obj->clientIndexFlexRayVFrReceiveMsgEx, 0);
    BOOST_CHECK_EQUAL(obj->clusterNo, 0);
    BOOST_CHECK_EQUAL(obj->frameId, 4);
    BOOST_CHECK_EQUAL(obj->headerCrc1, 151);
    BOOST_CHECK_EQUAL(obj->headerCrc2, 151);
    BOOST_CHECK_EQUAL(obj->byteCount, 4);
    BOOST_CHECK_EQUAL(obj->dataCount, 4);
    BOOST_CHECK_EQUAL(obj->cycle, 25);
    BOOST_CHECK_EQUAL(obj->tag, 2);
    BOOST_CHECK_EQUAL(obj->data, 0xD0);
    BOOST_CHECK_EQUAL(obj->frameFlags, 0x06);
    BOOST_CHECK_EQUAL(obj->appParameter, 0);
    BOOST_CHECK_EQUAL(obj->frameCrc, 0);
    BOOST_CHECK_EQUAL(obj->frameLengthNs, 0);
    BOOST_CHECK_EQUAL(obj->frameId1, 0);
    BOOST_CHECK_EQUAL(obj->pduOffset, 0);
    BOOST_CHECK_EQUAL(obj->blfLogMask, 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 0], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 1], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 2], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 3], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 4], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 5], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 6], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 7], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 8], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 9], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[10], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[11], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[12], 0);
    BOOST_CHECK_EQUAL(obj->dataBytes[0], 0x15);
    BOOST_CHECK_EQUAL(obj->dataBytes[1], 0x57);
    BOOST_CHECK_EQUAL(obj->dataBytes[2], 0x16);
    BOOST_CHECK_EQUAL(obj->dataBytes[3], 0x94);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx2.size(), 0);

    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);
    obj = static_cast<Vector::BLF::FlexRayVFrReceiveMsgEx *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 42600000); // ns

    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK_EQUAL(obj->channel, 2);
    BOOST_CHECK_EQUAL(obj->version, 1);
    BOOST_CHECK_EQUAL(obj->channelMask, 2); // FlexRay Channel B
    BOOST_CHECK_EQUAL(obj->dir, 0); // Rx
    BOOST_CHECK_EQUAL(obj->clientIndexFlexRayVFrReceiveMsgEx, 0);
    BOOST_CHECK_EQUAL(obj->clusterNo, 1);
    BOOST_CHECK_EQUAL(obj->frameId, 13);
    BOOST_CHECK_EQUAL(obj->headerCrc1, 0x026C);
    BOOST_CHECK_EQUAL(obj->headerCrc2, 0x026C);
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
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 0], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 1], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 2], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 3], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 4], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 5], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 6], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 7], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 8], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[ 9], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[10], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[11], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx1[12], 0);
    BOOST_CHECK_EQUAL(obj->dataBytes[0], 0x02);
    BOOST_CHECK_EQUAL(obj->dataBytes[1], 0x59);
    BOOST_CHECK_EQUAL(obj->dataBytes[2], 0x00);
    BOOST_CHECK_EQUAL(obj->dataBytes[3], 0x0D);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx2.size(), 0);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayVFrReceiveMsgEx_62e7a39621065792dc8198da3f31a95e) {
    Vector::BLF::CompressedFile file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/lobj/FlexRayVFrReceiveMsgEx/62e7a39621065792dc8198da3f31a95e.lobj", std::ios_base::in | std::ios_base::binary);
    BOOST_REQUIRE(file.is_open());

    auto obj = new Vector::BLF::FlexRayVFrReceiveMsgEx;
    obj->read(file);
    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, 376);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE_EX);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 344009000); // ns

    /* FlexRayVFrReceiveMsgEx */
    BOOST_CHECK_EQUAL(obj->channel, 0x0001);
    BOOST_CHECK_EQUAL(obj->version, 0x0001);
    BOOST_CHECK_EQUAL(obj->channelMask, 0x0001);
    BOOST_CHECK_EQUAL(obj->dir, 0x0000);
    BOOST_CHECK_EQUAL(obj->clientIndexFlexRayVFrReceiveMsgEx, 0x00000000);
    BOOST_CHECK_EQUAL(obj->clusterNo, 0x00000000);
    BOOST_CHECK_EQUAL(obj->frameId, 0x0057);
    BOOST_CHECK_EQUAL(obj->headerCrc1, 0x07e5);
    BOOST_CHECK_EQUAL(obj->headerCrc2, 0x0000);
    BOOST_CHECK_EQUAL(obj->byteCount, 0x00AA);
    BOOST_CHECK_EQUAL(obj->dataCount, 0x00AA);
    BOOST_CHECK_EQUAL(obj->cycle, 0x0027);
    BOOST_CHECK_EQUAL(obj->tag, 0x00000004);
    BOOST_CHECK_EQUAL(obj->data, 0x00000020);
    BOOST_CHECK_EQUAL(obj->frameFlags, 0x00000002);
    BOOST_CHECK_EQUAL(obj->appParameter, 0x00000000);
    BOOST_CHECK_EQUAL(obj->frameCrc, 0x00A7AFCF);
    BOOST_CHECK_EQUAL(obj->frameLengthNs, 0x00000000);
    BOOST_CHECK_EQUAL(obj->frameId1, 0x0000);
    BOOST_CHECK_EQUAL(obj->pduOffset, 0x0000);
    BOOST_CHECK_EQUAL(obj->blfLogMask, 0x0000);
    const std::array<uint16_t, 13> expectedReservedFlexRayVFrReceiveMsgEx1 = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->reservedFlexRayVFrReceiveMsgEx1.cbegin(), obj->reservedFlexRayVFrReceiveMsgEx1.cend(), expectedReservedFlexRayVFrReceiveMsgEx1.cbegin(), expectedReservedFlexRayVFrReceiveMsgEx1.cend());
    const std::vector<uint8_t> expectedDataBytes = {
                                0xb8, 0x75, 0x00, 0x28, 0x00, 0xc0, 0x15, 0x49, 0x6e, 0xaf, 0x60, 0x00, // 0x0070
        0x3d, 0xe6, 0x12, 0x2f, 0x42, 0xaf, 0x60, 0x00, 0x3d, 0x00, 0x00, 0xc0, 0x40, 0xaf, 0x60, 0x00, // 0x0080
        0x3d, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x35, 0xef, 0x2d, 0x42, 0x00, 0x00, 0x00, // 0x0090
        0x00, 0x28, 0x01, 0x00, 0x00, 0x28, 0x42, 0x18, 0x20, 0x28, 0x42, 0x00, 0x00, 0xc0, 0x40, 0x1a, // 0x00a0
        0xe6, 0x30, 0x42, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x47, 0x01, 0x3c, 0x00, 0x00, 0x00, 0x00, // 0x00b0
        0x00, 0x6b, 0x00, 0x60, 0x05, 0x62, 0x05, 0x9b, 0x0a, 0x00, 0x00, 0x28, 0x02, 0xa4, 0x0a, 0x5d, // 0x00c0
        0x05, 0x67, 0x05, 0xd2, 0x06, 0x65, 0x05, 0x00, 0x00, 0x94, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, // 0x00d0
        0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // 0x00e0
        0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x00f0
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x0100
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00              // 0x0110
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->dataBytes.cbegin(), obj->dataBytes.cend(), expectedDataBytes.cbegin(), expectedDataBytes.cend());
    const std::vector<uint8_t> expectedReservedFlexRayVFrReceiveMsgEx2 = {
                                                                                            0x00, 0x00, // 0x0110
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x0120
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x0130
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x0140
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x0150
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x0160
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                 // 0x0170
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->reservedFlexRayVFrReceiveMsgEx2.cbegin(), obj->reservedFlexRayVFrReceiveMsgEx2.cend(), expectedReservedFlexRayVFrReceiveMsgEx2.cbegin(), expectedReservedFlexRayVFrReceiveMsgEx2.cend());
    delete obj;
}
