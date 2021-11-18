// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE CanFdErrorFrame64
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_FD_ERROR_64 = 104 */
BOOST_AUTO_TEST_CASE(CanFdErrorFrame64) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanFdErrorFrame64.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_ERROR_64);
    auto * obj = dynamic_cast<Vector::BLF::CanFdErrorFrame64 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_FD_ERROR_64);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* CanFdErrorFrame64 */
    BOOST_CHECK_EQUAL(obj->channel, 0x11);
    BOOST_CHECK_EQUAL(obj->dlc, 0x22);
    BOOST_CHECK_EQUAL(obj->validDataBytes, 64);
    BOOST_CHECK_EQUAL(obj->ecc, 0x44);
    BOOST_CHECK_EQUAL(obj->flags, 0x5555);
    BOOST_CHECK_EQUAL(obj->errorCodeExt, 0x6666);
    BOOST_CHECK_EQUAL(obj->extFlags, 0x7777);
    BOOST_CHECK_EQUAL(obj->extDataOffset, 0x8C);
    BOOST_CHECK_EQUAL(obj->reservedCanFdErrorFrame1, 0x99);
    BOOST_CHECK_EQUAL(obj->id, 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->frameLength, 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->btrCfgArb, 0xCCCCCCCC);
    BOOST_CHECK_EQUAL(obj->btrCfgData, 0xDDDDDDDD);
    BOOST_CHECK_EQUAL(obj->timeOffsetBrsNs, 0xEEEEEEEE);
    BOOST_CHECK_EQUAL(obj->timeOffsetCrcDelNs, 0xFFFFFFFF);
    BOOST_CHECK_EQUAL(obj->crc, 0x11111111);
    BOOST_CHECK_EQUAL(obj->errorPosition, 0x2222);
    BOOST_CHECK_EQUAL(obj->reservedCanFdErrorFrame2, 0x3333);
    for (uint8_t i = 0; i < 64; i++)
        BOOST_CHECK_EQUAL(obj->data[i], i);

    /* CanFdExtFrameData */
    BOOST_CHECK_EQUAL(obj->btrExtArb, 0x11111111);
    BOOST_CHECK_EQUAL(obj->btrExtData, 0x22222222);


    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_ERROR_64);

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
