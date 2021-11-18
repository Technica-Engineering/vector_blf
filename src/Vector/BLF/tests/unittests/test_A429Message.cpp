// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE A429Message
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* A429_MESSAGE = 113 */
BOOST_AUTO_TEST_CASE(A429Message) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_A429Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::A429_MESSAGE);
    auto * obj = dynamic_cast<Vector::BLF::A429Message *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::A429_MESSAGE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* A429Message */
    BOOST_CHECK_EQUAL(obj->a429Data[0], 0x11);
    BOOST_CHECK_EQUAL(obj->a429Data[1], 0x22);
    BOOST_CHECK_EQUAL(obj->a429Data[2], 0x33);
    BOOST_CHECK_EQUAL(obj->a429Data[3], 0x44);
    BOOST_CHECK_EQUAL(obj->channel, 0x5555);
    BOOST_CHECK_EQUAL(obj->dir, 0x66);
    BOOST_CHECK_EQUAL(obj->reservedA429Message1, 0x77);
    BOOST_CHECK_EQUAL(obj->bitrate, 0x88888888);
    BOOST_CHECK_EQUAL(obj->errReason, 0x79999999); // signed
    BOOST_CHECK_EQUAL(obj->errPosition, 0xAAAA);
    BOOST_CHECK_EQUAL(obj->reservedA429Message2, 0x0000);
    BOOST_CHECK_EQUAL(obj->reservedA429Message3, 0x00000000);
    BOOST_CHECK_EQUAL(obj->frameGap, 0xBBBBBBBBBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->frameLength, 0xCCCCCCCC);
    BOOST_CHECK_EQUAL(obj->msgCtrl, 0xDDDD);
    BOOST_CHECK_EQUAL(obj->reservedA429Message4, 0x0000);
    BOOST_CHECK_EQUAL(obj->cycleTime, 0xEEEEEEEE);
    BOOST_CHECK_EQUAL(obj->error, 0xFFFFFFFF);
    BOOST_CHECK_EQUAL(obj->bitLenOfLastBit, 0x11111111);
    BOOST_CHECK_EQUAL(obj->reservedA429Message5, 0x00000000);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::A429_MESSAGE);

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
