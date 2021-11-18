// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE AfdxStatus
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* AFDX_STATUS = 106 */
BOOST_AUTO_TEST_CASE(AfdxStatus) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_AfdxStatus.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_STATUS);
    auto * obj = dynamic_cast<Vector::BLF::AfdxStatus *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::AFDX_STATUS);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* AfdxStatus */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);

    /* AfdxLineStatus for A */
    BOOST_CHECK_EQUAL(obj->statusA.flags, 0x1111);
    BOOST_CHECK_EQUAL(obj->statusA.linkStatus, 0x22);
    BOOST_CHECK_EQUAL(obj->statusA.ethernetPhy, 0x33);
    BOOST_CHECK_EQUAL(obj->statusA.duplex, 0x44);
    BOOST_CHECK_EQUAL(obj->statusA.mdi, 0x55);
    BOOST_CHECK_EQUAL(obj->statusA.connector, 0x66);
    BOOST_CHECK_EQUAL(obj->statusA.clockMode, 0x77);
    BOOST_CHECK_EQUAL(obj->statusA.pairs, 0x88);
    BOOST_CHECK_EQUAL(obj->statusA.reservedAfdxLineStatus1, 0x99);
    BOOST_CHECK_EQUAL(obj->statusA.reservedAfdxLineStatus2, 0);
    BOOST_CHECK_EQUAL(obj->statusA.bitrate, 0xAAAAAAAA);

    /* AfdxLineStatus for B */
    BOOST_CHECK_EQUAL(obj->statusB.flags, 0x1111);
    BOOST_CHECK_EQUAL(obj->statusB.linkStatus, 0x22);
    BOOST_CHECK_EQUAL(obj->statusB.ethernetPhy, 0x33);
    BOOST_CHECK_EQUAL(obj->statusB.duplex, 0x44);
    BOOST_CHECK_EQUAL(obj->statusB.mdi, 0x55);
    BOOST_CHECK_EQUAL(obj->statusB.connector, 0x66);
    BOOST_CHECK_EQUAL(obj->statusB.clockMode, 0x77);
    BOOST_CHECK_EQUAL(obj->statusB.pairs, 0x88);
    BOOST_CHECK_EQUAL(obj->statusB.reservedAfdxLineStatus1, 0x99);
    BOOST_CHECK_EQUAL(obj->statusB.reservedAfdxLineStatus2, 0);
    BOOST_CHECK_EQUAL(obj->statusB.bitrate, 0xAAAAAAAA);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_STATUS);

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
