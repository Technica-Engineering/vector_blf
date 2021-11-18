// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE LinCrcError2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_CRC_ERROR2 = 60 */
BOOST_AUTO_TEST_CASE(LinCrcError2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_LinCrcError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_CRC_ERROR2);
    auto * obj = dynamic_cast<Vector::BLF::LinCrcError2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_CRC_ERROR2);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* LinCrcError2 */
    BOOST_CHECK_EQUAL(obj->data[0], 0x11);
    BOOST_CHECK_EQUAL(obj->data[1], 0x22);
    BOOST_CHECK_EQUAL(obj->data[2], 0x33);
    BOOST_CHECK_EQUAL(obj->data[3], 0x44);
    BOOST_CHECK_EQUAL(obj->data[4], 0x55);
    BOOST_CHECK_EQUAL(obj->data[5], 0x66);
    BOOST_CHECK_EQUAL(obj->data[6], 0x77);
    BOOST_CHECK_EQUAL(obj->data[7], 0x88);
    BOOST_CHECK_EQUAL(obj->crc, 0x9999);
    BOOST_CHECK_EQUAL(obj->dir, 0xAA);
    BOOST_CHECK_EQUAL(obj->fsmId, 0xBB);
    BOOST_CHECK_EQUAL(obj->fsmState, 0xCC);
    BOOST_CHECK_EQUAL(obj->simulated, 0xDD);
    BOOST_CHECK_EQUAL(obj->reservedLinCrcError1, 0xEEEE);
    BOOST_CHECK_EQUAL(obj->respBaudrate, 0xFFFFFFFF);
    BOOST_CHECK_EQUAL(obj->reservedLinCrcError2, 0x11111111);
    BOOST_CHECK_EQUAL(obj->exactHeaderBaudrate, 2.0);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffset, 0x33333333);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffsetResponse, 0x44444444);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_CRC_ERROR2);

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
