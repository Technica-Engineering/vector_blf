// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE FlexRayVFrStartCycle
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* FR_STARTCYCLE = 49 */
BOOST_AUTO_TEST_CASE(FlexRayVFrStartCycle_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_FlexRayVFrStartCycle.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);
    auto * obj = dynamic_cast<Vector::BLF::FlexRayVFrStartCycle *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* FlexRayVFrStartCycle */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->version, 0x2222);
    BOOST_CHECK_EQUAL(obj->channelMask, 0x3333);
    BOOST_CHECK_EQUAL(obj->dir, 0x44);
    BOOST_CHECK_EQUAL(obj->cycle, 0x55);
    BOOST_CHECK_EQUAL(obj->clientIndexFlexRayVFrStartCycle, 0x66666666);
    BOOST_CHECK_EQUAL(obj->clusterNo, 0x77777777);
    BOOST_CHECK_EQUAL(obj->nmSize, 0x8888);
    for (uint16_t i = 0; i < 12; i++)
        BOOST_CHECK_EQUAL(obj->dataBytes[i], i);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrStartCycle1, 0);
    BOOST_CHECK_EQUAL(obj->tag, 0x99999999);
    BOOST_CHECK_EQUAL(obj->data[0], 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->data[1], 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->data[2], 0xCCCCCCCC);
    BOOST_CHECK_EQUAL(obj->data[3], 0xDDDDDDDD);
    BOOST_CHECK_EQUAL(obj->data[4], 0xEEEEEEEE);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrStartCycle2, 0xFFFF);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);

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

BOOST_AUTO_TEST_CASE(FlexRayVFrStartCycle_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_FlexRayVFrStartCycle.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);
    auto * obj = dynamic_cast<Vector::BLF::FlexRayVFrStartCycle *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_STARTCYCLE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
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

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
