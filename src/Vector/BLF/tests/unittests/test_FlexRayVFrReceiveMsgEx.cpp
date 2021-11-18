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
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 0], 0x7777);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 1], 0x8888);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 2], 0x8888);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 3], 0x9999);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 4], 0x9999);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 5], 0xAAAA);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 6], 0xAAAA);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 7], 0xBBBB);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 8], 0xBBBB);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 9], 0xCCCC);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[10], 0xCCCC);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[11], 0xDDDD);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[12], 0xDDDD);
    for (uint8_t i = 0; i < 254; i++)
        BOOST_CHECK_EQUAL(obj->dataBytes[i], i);

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
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 0], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 1], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 2], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 3], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 4], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 5], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 6], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 7], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 8], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 9], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[10], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[11], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[12], 0);
    BOOST_CHECK_EQUAL(obj->dataBytes[0], 0x15);
    BOOST_CHECK_EQUAL(obj->dataBytes[1], 0x57);
    BOOST_CHECK_EQUAL(obj->dataBytes[2], 0x16);
    BOOST_CHECK_EQUAL(obj->dataBytes[3], 0x94);

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
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 0], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 1], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 2], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 3], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 4], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 5], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 6], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 7], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 8], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[ 9], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[10], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[11], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsgEx[12], 0);
    BOOST_CHECK_EQUAL(obj->dataBytes[0], 0x02);
    BOOST_CHECK_EQUAL(obj->dataBytes[1], 0x59);
    BOOST_CHECK_EQUAL(obj->dataBytes[2], 0x00);
    BOOST_CHECK_EQUAL(obj->dataBytes[3], 0x0D);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
