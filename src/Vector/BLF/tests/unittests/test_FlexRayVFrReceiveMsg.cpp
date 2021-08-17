// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE FlexRayVFrReceiveMsg
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* FR_RCVMESSAGE = 50 */
BOOST_AUTO_TEST_CASE(FlexRayVFrReceiveMsg) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_FlexRayVFrReceiveMsg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE);
    auto * obj = dynamic_cast<Vector::BLF::FlexRayVFrReceiveMsg *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* FlexRayVFrReceiveMsg */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->version, 0x2222);
    BOOST_CHECK_EQUAL(obj->channelMask, 0x3333);
    BOOST_CHECK_EQUAL(obj->dir, 0x44);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsg1, 0);
    BOOST_CHECK_EQUAL(obj->clientIndexFlexRayVFrReceiveMsg, 0x55555555);
    BOOST_CHECK_EQUAL(obj->clusterNo, 0x66666666);
    BOOST_CHECK_EQUAL(obj->frameId, 0x7777);
    BOOST_CHECK_EQUAL(obj->headerCrc1, 0x8888);
    BOOST_CHECK_EQUAL(obj->headerCrc2, 0x9999);
    BOOST_CHECK_EQUAL(obj->byteCount, 0xAAAA);
    BOOST_CHECK_EQUAL(obj->dataCount, 0xBBBB);
    BOOST_CHECK_EQUAL(obj->cycle, 0xCC);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsg2, 0);
    BOOST_CHECK_EQUAL(obj->tag, 0xDDDDDDDD);
    BOOST_CHECK_EQUAL(obj->data, 0xEEEEEEEE);
    BOOST_CHECK_EQUAL(obj->frameFlags, 0xFFFFFFFF);
    BOOST_CHECK_EQUAL(obj->appParameter, 0x11111111);
    for (uint8_t i = 0; i < 254; i++)
        BOOST_CHECK_EQUAL(obj->dataBytes[i], i);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsg3, 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrReceiveMsg4, 0);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE);

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
