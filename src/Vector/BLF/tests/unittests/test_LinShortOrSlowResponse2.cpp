// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE LinShortOrSlowResponse2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_SHORT_OR_SLOW_RESPONSE2 = 105 */
BOOST_AUTO_TEST_CASE(LinShortOrSlowResponse2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_LinShortOrSlowResponse2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE2);
    auto * obj = dynamic_cast<Vector::BLF::LinShortOrSlowResponse2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE2);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* LinShortOrSlowResponse2 */
    BOOST_CHECK_EQUAL(obj->numberOfRespBytes, 0x11111111);
    BOOST_CHECK_EQUAL(obj->respBytes[0], 0x22);
    BOOST_CHECK_EQUAL(obj->respBytes[1], 0x33);
    BOOST_CHECK_EQUAL(obj->respBytes[2], 0x44);
    BOOST_CHECK_EQUAL(obj->respBytes[3], 0x55);
    BOOST_CHECK_EQUAL(obj->respBytes[4], 0x66);
    BOOST_CHECK_EQUAL(obj->respBytes[5], 0x77);
    BOOST_CHECK_EQUAL(obj->respBytes[6], 0x88);
    BOOST_CHECK_EQUAL(obj->respBytes[7], 0x99);
    BOOST_CHECK_EQUAL(obj->respBytes[8], 0xAA);
    BOOST_CHECK_EQUAL(obj->slowResponse, 0xBB);
    BOOST_CHECK_EQUAL(obj->interruptedByBreak, 0xCC);
    BOOST_CHECK_EQUAL(obj->reservedLinShortOrSlowResponse1, 0xDD);
    BOOST_CHECK_EQUAL(obj->exactHeaderBaudrate, 14.0);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffset, 15.0);
    BOOST_CHECK_EQUAL(obj->reservedLinShortOrSlowResponse2, 0);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE2);

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
