// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE AfdxFrame
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* AFDX_FRAME = 97 */
BOOST_AUTO_TEST_CASE(AfdxFrame_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_AfdxFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    auto * obj = dynamic_cast<Vector::BLF::AfdxFrame *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::AFDX_FRAME);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* AfdxFrame */
    BOOST_CHECK_EQUAL(obj->sourceAddress[0], 0x11);
    BOOST_CHECK_EQUAL(obj->sourceAddress[1], 0x22);
    BOOST_CHECK_EQUAL(obj->sourceAddress[2], 0x33);
    BOOST_CHECK_EQUAL(obj->sourceAddress[3], 0x44);
    BOOST_CHECK_EQUAL(obj->sourceAddress[4], 0x55);
    BOOST_CHECK_EQUAL(obj->sourceAddress[5], 0x66);
    BOOST_CHECK_EQUAL(obj->channel, 0x7777);
    BOOST_CHECK_EQUAL(obj->destinationAddress[0], 0x88);
    BOOST_CHECK_EQUAL(obj->destinationAddress[1], 0x99);
    BOOST_CHECK_EQUAL(obj->destinationAddress[2], 0xAA);
    BOOST_CHECK_EQUAL(obj->destinationAddress[3], 0xBB);
    BOOST_CHECK_EQUAL(obj->destinationAddress[4], 0xCC);
    BOOST_CHECK_EQUAL(obj->destinationAddress[5], 0xDD);
    BOOST_CHECK_EQUAL(obj->dir, 0x01); // Tx
    BOOST_CHECK_EQUAL(obj->type, 0xEEEE);
    BOOST_CHECK_EQUAL(obj->tpid, 0xFFFF);
    BOOST_CHECK_EQUAL(obj->tci, 0x1111);
    BOOST_CHECK_EQUAL(obj->ethChannel, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedAfdxFrame1, 0);
    BOOST_CHECK_EQUAL(obj->afdxFlags, 0x3333);
    BOOST_CHECK_EQUAL(obj->reservedAfdxFrame2, 0);
    BOOST_CHECK_EQUAL(obj->bagUsec, 0x44444444);
    BOOST_CHECK_EQUAL(obj->payLoadLength, 3);
    BOOST_CHECK_EQUAL(obj->reservedAfdxFrame3, 0);
    BOOST_CHECK_EQUAL(obj->reservedAfdxFrame4, 0);
    BOOST_CHECK_EQUAL(obj->payLoad[0], 5);
    BOOST_CHECK_EQUAL(obj->payLoad[1], 6);
    BOOST_CHECK_EQUAL(obj->payLoad[2], 7);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);

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

BOOST_AUTO_TEST_CASE(AfdxFrame_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_AfdxFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    auto * obj = dynamic_cast<Vector::BLF::AfdxFrame *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::AFDX_FRAME);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0); // ns

    /* AfdxFrame */
    BOOST_CHECK_EQUAL(obj->sourceAddress[0], 0x40);
    BOOST_CHECK_EQUAL(obj->sourceAddress[1], 0x00);
    BOOST_CHECK_EQUAL(obj->sourceAddress[2], 0x00);
    BOOST_CHECK_EQUAL(obj->sourceAddress[3], 0x00);
    BOOST_CHECK_EQUAL(obj->sourceAddress[4], 0x00);
    BOOST_CHECK_EQUAL(obj->sourceAddress[5], 0x04);
    BOOST_CHECK_EQUAL(obj->channel, 0x0001);
    BOOST_CHECK_EQUAL(obj->destinationAddress[0], 0xff);
    BOOST_CHECK_EQUAL(obj->destinationAddress[1], 0xff);
    BOOST_CHECK_EQUAL(obj->destinationAddress[2], 0xff);
    BOOST_CHECK_EQUAL(obj->destinationAddress[3], 0xff);
    BOOST_CHECK_EQUAL(obj->destinationAddress[4], 0xff);
    BOOST_CHECK_EQUAL(obj->destinationAddress[5], 0xff);
    BOOST_CHECK_EQUAL(obj->dir, 0x01); // Tx
    BOOST_CHECK_EQUAL(obj->type, 0x0806);
    BOOST_CHECK_EQUAL(obj->tpid, 0x0000);
    BOOST_CHECK_EQUAL(obj->tci, 0x0000);
    BOOST_CHECK_EQUAL(obj->ethChannel, 0x01);
    // reserved
    BOOST_CHECK_EQUAL(obj->afdxFlags, 0x0040);
    // reserved
    BOOST_CHECK_EQUAL(obj->bagUsec, 0);
    BOOST_CHECK_EQUAL(obj->payLoadLength, 0x002e);
    // reserved
    BOOST_CHECK_EQUAL(obj->payLoad[0x00], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x01], 0x01);
    BOOST_CHECK_EQUAL(obj->payLoad[0x02], 0x08);
    BOOST_CHECK_EQUAL(obj->payLoad[0x03], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x04], 0x06);
    BOOST_CHECK_EQUAL(obj->payLoad[0x05], 0x04);
    BOOST_CHECK_EQUAL(obj->payLoad[0x06], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x07], 0x01);
    BOOST_CHECK_EQUAL(obj->payLoad[0x08], 0x40);
    BOOST_CHECK_EQUAL(obj->payLoad[0x09], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x0a], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x0b], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x0c], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x0d], 0x04);
    BOOST_CHECK_EQUAL(obj->payLoad[0x0e], 0xc0);
    BOOST_CHECK_EQUAL(obj->payLoad[0x0f], 0xa8);
    BOOST_CHECK_EQUAL(obj->payLoad[0x10], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x11], 0x01);
    BOOST_CHECK_EQUAL(obj->payLoad[0x12], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x13], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x14], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x15], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x16], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x17], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x18], 0xc0);
    BOOST_CHECK_EQUAL(obj->payLoad[0x19], 0xa8);
    BOOST_CHECK_EQUAL(obj->payLoad[0x1a], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x1b], 0x01);
    BOOST_CHECK_EQUAL(obj->payLoad[0x1c], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x1d], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x1e], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x1f], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x20], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x21], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x22], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x23], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x24], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x25], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x26], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x27], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x28], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x29], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x2a], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x2b], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x2c], 0x00);
    BOOST_CHECK_EQUAL(obj->payLoad[0x2d], 0x00);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
