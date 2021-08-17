// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE CanFdMessage64
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_FD_MESSAGE_64 = 101 */
BOOST_AUTO_TEST_CASE(CanFdMessage64) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanFdMessage64.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_MESSAGE_64);
    auto * obj = dynamic_cast<Vector::BLF::CanFdMessage64 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_FD_MESSAGE_64);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* CanFdMessage64 */
    BOOST_CHECK_EQUAL(obj->channel, 0x11);
    BOOST_CHECK_EQUAL(obj->dlc, 0x22);
    BOOST_CHECK_EQUAL(obj->validDataBytes, 64);
    BOOST_CHECK_EQUAL(obj->txCount, 0x44);
    BOOST_CHECK_EQUAL(obj->id, 0x55555555);
    BOOST_CHECK_EQUAL(obj->frameLength, 0x66666666);
    BOOST_CHECK_EQUAL(obj->flags, 0x77777777);
    BOOST_CHECK_EQUAL(obj->btrCfgArb, 0x88888888);
    BOOST_CHECK_EQUAL(obj->btrCfgData, 0x99999999);
    BOOST_CHECK_EQUAL(obj->timeOffsetBrsNs, 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->timeOffsetCrcDelNs, 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->bitCount, 0xCCCC);
    BOOST_CHECK_EQUAL(obj->dir, 0xDD);
    BOOST_CHECK_EQUAL(obj->extDataOffset, 0x50);
    BOOST_CHECK_EQUAL(obj->crc, 0xFFFFFFFF);
    for (uint8_t i = 0; i < 64; i++)
        BOOST_CHECK_EQUAL(obj->data[i], i);
    BOOST_CHECK_EQUAL(obj->btrExtArb, 0x11111111);
    BOOST_CHECK_EQUAL(obj->btrExtData, 0x22222222);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_MESSAGE_64);

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

BOOST_AUTO_TEST_CASE(CanFdMessage64_Write) {
    /* open file for writing */
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_BINARY_DIR "/test_CanFdMessage64_Write.blf", std::ios_base::out);
    BOOST_REQUIRE(file.is_open());

    /* write message */
    auto * canFdMessage64 = new Vector::BLF::CanFdMessage64;
    canFdMessage64->channel = 1;
    canFdMessage64->dlc = 9;
    canFdMessage64->id = 0x33;
    canFdMessage64->data.resize(12);
    canFdMessage64->data[0] = 0x44;
    canFdMessage64->data[1] = 0x55;
    canFdMessage64->data[2] = 0x55;
    canFdMessage64->data[3] = 0x55;
    canFdMessage64->data[4] = 0x55;
    canFdMessage64->data[5] = 0x55;
    canFdMessage64->data[6] = 0x55;
    canFdMessage64->data[7] = 0x55;
    canFdMessage64->data[8] = 0x55;
    canFdMessage64->data[9] = 0x55;
    canFdMessage64->data[10] = 0x55;
    canFdMessage64->data[11] = 0x55;
    file.write(canFdMessage64);

    /* close file */
    file.close();
}
