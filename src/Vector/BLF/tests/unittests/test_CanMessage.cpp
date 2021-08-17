// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE CanMessage
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_MESSAGE = 1 */
BOOST_AUTO_TEST_CASE(CanMessage_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    auto * obj = dynamic_cast<Vector::BLF::CanMessage *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* CanMessage */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->flags, 0x22);
    BOOST_CHECK_EQUAL(obj->dlc, 0x33);
    BOOST_CHECK_EQUAL(obj->id, 0x44444444);
    BOOST_CHECK_EQUAL(obj->data[0], 0x55);
    BOOST_CHECK_EQUAL(obj->data[1], 0x66);
    BOOST_CHECK_EQUAL(obj->data[2], 0x77);
    BOOST_CHECK_EQUAL(obj->data[3], 0x88);
    BOOST_CHECK_EQUAL(obj->data[4], 0x99);
    BOOST_CHECK_EQUAL(obj->data[5], 0xAA);
    BOOST_CHECK_EQUAL(obj->data[6], 0xBB);
    BOOST_CHECK_EQUAL(obj->data[7], 0xCC);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);

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

BOOST_AUTO_TEST_CASE(CanMessage_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_CanMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    auto * obj = dynamic_cast<Vector::BLF::CanMessage *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 4876870000); // ns

    /* CanMessage */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->flags, 1); // TX
    BOOST_CHECK_EQUAL(obj->dlc, 8);
    BOOST_CHECK_EQUAL(obj->id, 0x854c5638); // 54C5638x
    BOOST_CHECK_EQUAL(obj->data[0], 0);
    BOOST_CHECK_EQUAL(obj->data[1], 0);
    BOOST_CHECK_EQUAL(obj->data[2], 0);
    BOOST_CHECK_EQUAL(obj->data[3], 0);
    BOOST_CHECK_EQUAL(obj->data[4], 0);
    BOOST_CHECK_EQUAL(obj->data[5], 0);
    BOOST_CHECK_EQUAL(obj->data[6], 0);
    BOOST_CHECK_EQUAL(obj->data[7], 0);

    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    obj = static_cast<Vector::BLF::CanMessage *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    // reserved
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 2501000000); // ns

    /* CanMessage */
    BOOST_CHECK_EQUAL(obj->channel, 2);
    BOOST_CHECK_EQUAL(obj->flags, 0); // RX
    BOOST_CHECK_EQUAL(obj->dlc, 8);
    BOOST_CHECK_EQUAL(obj->id, 0x800000c8); // C8x
    BOOST_CHECK_EQUAL(obj->data[0], 9);
    BOOST_CHECK_EQUAL(obj->data[1], 8);
    BOOST_CHECK_EQUAL(obj->data[2], 7);
    BOOST_CHECK_EQUAL(obj->data[3], 6);
    BOOST_CHECK_EQUAL(obj->data[4], 5);
    BOOST_CHECK_EQUAL(obj->data[5], 4);
    BOOST_CHECK_EQUAL(obj->data[6], 3);
    BOOST_CHECK_EQUAL(obj->data[7], 2);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanMessage_Write) {
    /* open file for writing */
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_BINARY_DIR "/test_CanMessage_Write.blf", std::ios_base::out);
    BOOST_REQUIRE(file.is_open());

    /* write message */
    auto * canMessage = new Vector::BLF::CanMessage;
    canMessage->channel = 1;
    canMessage->flags = 1; // TX
    canMessage->dlc = 2;
    canMessage->id = 0x33;
    canMessage->data[0] = 0x44;
    canMessage->data[1] = 0x55;
    file.write(canMessage);

    /* close file */
    file.close();
}
