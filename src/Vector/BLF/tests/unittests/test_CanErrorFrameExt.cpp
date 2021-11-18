// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE CanErrorFrameExt
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_ERROR_EXT = 73 */
BOOST_AUTO_TEST_CASE(CanErrorFrameExt_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanErrorFrameExt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);
    auto * obj = dynamic_cast<Vector::BLF::CanErrorFrameExt *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* CanErrorFrameExt */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->length, 0x2222);
    BOOST_CHECK_EQUAL(obj->flags, 0x33333333);
    BOOST_CHECK_EQUAL(obj->ecc, 0x44);
    BOOST_CHECK_EQUAL(obj->position, 0x55);
    BOOST_CHECK_EQUAL(obj->dlc, 0x66);
    BOOST_CHECK_EQUAL(obj->reservedCanErrorFrameExt1, 0x77);
    BOOST_CHECK_EQUAL(obj->frameLengthInNs, 0x88888888);
    BOOST_CHECK_EQUAL(obj->id, 0x99999999);
    BOOST_CHECK_EQUAL(obj->flagsExt, 0xAAAA);
    BOOST_CHECK_EQUAL(obj->reservedCanErrorFrameExt2, 0xBBBB);
    BOOST_CHECK_EQUAL(obj->data[0], 0xCC);
    BOOST_CHECK_EQUAL(obj->data[1], 0xDD);
    BOOST_CHECK_EQUAL(obj->data[2], 0xEE);
    BOOST_CHECK_EQUAL(obj->data[3], 0xFF);
    BOOST_CHECK_EQUAL(obj->data[4], 0x11);
    BOOST_CHECK_EQUAL(obj->data[5], 0x22);
    BOOST_CHECK_EQUAL(obj->data[6], 0x33);
    BOOST_CHECK_EQUAL(obj->data[7], 0x44);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);

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

BOOST_AUTO_TEST_CASE(CanErrorFrameExt_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_CanErrorFrameExt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);
    auto * obj = dynamic_cast<Vector::BLF::CanErrorFrameExt *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1592186000); // ns

    /* CanErrorFrameExt */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->length, 6);
    BOOST_CHECK_EQUAL(obj->flags, 1); // SJA 1000
    BOOST_CHECK_EQUAL(obj->ecc, 0xa2);
    BOOST_CHECK_EQUAL(obj->position, 0);
    BOOST_CHECK_EQUAL(obj->dlc, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->frameLengthInNs, 0);
    BOOST_CHECK_EQUAL(obj->id, 0xffffffff);
    BOOST_CHECK_EQUAL(obj->flagsExt, 0x20a2);
    // reserved
    //BOOST_CHECK_EQUAL(canErrorFrameExt->data[0], 0);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
