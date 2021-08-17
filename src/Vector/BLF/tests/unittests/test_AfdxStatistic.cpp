// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE AfdxStatistic
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* AFDX_STATISTIC = 98 */
BOOST_AUTO_TEST_CASE(AfdxStatistic) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_AfdxStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_STATISTIC);
    auto * obj = dynamic_cast<Vector::BLF::AfdxStatistic *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::AFDX_STATISTIC);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* AfdxStatistic */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->flags, 0x2222);
    BOOST_CHECK_EQUAL(obj->rxPacketCount, 0x33333333);
    BOOST_CHECK_EQUAL(obj->rxByteCount, 0x44444444);
    BOOST_CHECK_EQUAL(obj->txPacketCount, 0x55555555);
    BOOST_CHECK_EQUAL(obj->txByteCount, 0x66666666);
    BOOST_CHECK_EQUAL(obj->collisionCount, 0x77777777);
    BOOST_CHECK_EQUAL(obj->errorCount, 0x88888888);
    BOOST_CHECK_EQUAL(obj->statDroppedRedundantPacketCount, 0x99999999);
    BOOST_CHECK_EQUAL(obj->statRedundantErrorPacketCount, 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->statIntegrityErrorPacketCount, 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->statAvrgPeriodMsec, 0xCCCCCCCC);
    BOOST_CHECK_EQUAL(obj->statAvrgJitterMysec, 0xDDDDDDDD);
    BOOST_CHECK_EQUAL(obj->vlid, 0xEEEEEEEE);
    BOOST_CHECK_EQUAL(obj->statDuration, 0xFFFFFFFF);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_STATISTIC);

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
