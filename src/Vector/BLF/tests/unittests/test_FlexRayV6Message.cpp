// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE FlexRayV6Message
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* FLEXRAY_MESSAGE = 41 */
BOOST_AUTO_TEST_CASE(FlexRayV6Message) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_FlexRayV6Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_MESSAGE);
    auto * obj = dynamic_cast<Vector::BLF::FlexRayV6Message *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FLEXRAY_MESSAGE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* FlexRayV6Message */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->dir, 0x22);
    BOOST_CHECK_EQUAL(obj->lowTime, 0x33);
    BOOST_CHECK_EQUAL(obj->fpgaTick, 0x44444444);
    BOOST_CHECK_EQUAL(obj->fpgaTickOverflow, 0x55555555);
    BOOST_CHECK_EQUAL(obj->clientIndexFlexRayV6Message, 0x66666666);
    BOOST_CHECK_EQUAL(obj->clusterTime, 0x77777777);
    BOOST_CHECK_EQUAL(obj->frameId, 0x8888);
    BOOST_CHECK_EQUAL(obj->headerCrc, 0x9999);
    BOOST_CHECK_EQUAL(obj->frameState, 0xAAAA);
    BOOST_CHECK_EQUAL(obj->length, 0xBB);
    BOOST_CHECK_EQUAL(obj->cycle, 0xCC);
    BOOST_CHECK_EQUAL(obj->headerBitMask, 0xDD);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayV6Message1, 0xEE);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayV6Message2, 0xFFFF);
    for (uint8_t i = 0; i < 64; i++)
        BOOST_CHECK_EQUAL(obj->dataBytes[i], i);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_MESSAGE);

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
