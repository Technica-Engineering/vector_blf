// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE Most50Message
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_50_MESSAGE = 84 */
BOOST_AUTO_TEST_CASE(Most50Message_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_Most50Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);
    auto * obj = dynamic_cast<Vector::BLF::Most50Message *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);

    /* ObjectHeader2 */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedObjectHeader, 0x33);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x4444444444444444);
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0x5555555555555555);

    /* Most50Message */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->dir, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedMost50Message1, 0x33);
    BOOST_CHECK_EQUAL(obj->sourceAdr, 0x44444444);
    BOOST_CHECK_EQUAL(obj->destAdr, 0x55555555);
    BOOST_CHECK_EQUAL(obj->transferType, 0x66);
    BOOST_CHECK_EQUAL(obj->state, 0x77);
    BOOST_CHECK_EQUAL(obj->ackNack, 0x88);
    BOOST_CHECK_EQUAL(obj->reservedMost50Message2, 0x99);
    BOOST_CHECK_EQUAL(obj->crc, 0xAAAA);
    BOOST_CHECK_EQUAL(obj->reservedMost50Message3, 0xBBBB);
    BOOST_CHECK_EQUAL(obj->priority, 0xCC);
    BOOST_CHECK_EQUAL(obj->reservedMost50Message4, 0xDD);
    BOOST_CHECK_EQUAL(obj->msgLen, 3);
    BOOST_CHECK_EQUAL(obj->reservedMost50Message5, 0);
    BOOST_CHECK_EQUAL(obj->msg[0], 4);
    BOOST_CHECK_EQUAL(obj->msg[1], 5);
    BOOST_CHECK_EQUAL(obj->msg[2], 6);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);

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

BOOST_AUTO_TEST_CASE(Most50Message_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_Most50Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);
    auto * obj = dynamic_cast<Vector::BLF::Most50Message *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);

    /* ObjectHeader2 */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 200000000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* Most50Message */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->dir, 0); // Rx
    // reserved
    BOOST_CHECK_EQUAL(obj->sourceAdr, 0xEF00);
    BOOST_CHECK_EQUAL(obj->destAdr, 0x0101);
    BOOST_CHECK_EQUAL(obj->transferType, 2); // Spy
    BOOST_CHECK_EQUAL(obj->state, 0x01); // bus active
    BOOST_CHECK_EQUAL(obj->ackNack, 0x00);
    // reserved
    BOOST_CHECK_EQUAL(obj->crc, 0x5678);
    // reserved
    BOOST_CHECK_EQUAL(obj->priority, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->msgLen, 9);
    // reserved
    BOOST_CHECK_EQUAL(obj->msg[0], 0x11);
    BOOST_CHECK_EQUAL(obj->msg[1], 0x01);
    BOOST_CHECK_EQUAL(obj->msg[2], 0x22);
    BOOST_CHECK_EQUAL(obj->msg[3], 0x23);
    BOOST_CHECK_EQUAL(obj->msg[4], 0x04);
    BOOST_CHECK_EQUAL(obj->msg[5], 0x11);
    BOOST_CHECK_EQUAL(obj->msg[6], 0x22);
    BOOST_CHECK_EQUAL(obj->msg[7], 0x33);
    BOOST_CHECK_EQUAL(obj->msg[8], 0x44);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
