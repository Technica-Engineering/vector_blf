// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE AfdxBusStatistic
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* AFDX_BUS_STATISTIC = 107 */
BOOST_AUTO_TEST_CASE(AfdxBusStatistic_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_AfdxBusStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_BUS_STATISTIC);
    auto * obj = dynamic_cast<Vector::BLF::AfdxBusStatistic *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::AFDX_BUS_STATISTIC);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* AfdxBusStatistic */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->flags, 0x2222);
    BOOST_CHECK_EQUAL(obj->statDuration, 0x33333333);
    BOOST_CHECK_EQUAL(obj->statRxPacketCountHW, 0x44444444);
    BOOST_CHECK_EQUAL(obj->statTxPacketCountHW, 0x55555555);
    BOOST_CHECK_EQUAL(obj->statRxErrorCountHW, 0x66666666);
    BOOST_CHECK_EQUAL(obj->statTxErrorCountHW, 0x77777777);
    BOOST_CHECK_EQUAL(obj->statRxBytesHW, 0x88888888);
    BOOST_CHECK_EQUAL(obj->statTxBytesHW, 0x99999999);
    BOOST_CHECK_EQUAL(obj->statRxPacketCount, 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->statTxPacketCount, 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->statDroppedPacketCount, 0xCCCCCCCC);
    BOOST_CHECK_EQUAL(obj->statInvalidPacketCount, 0xDDDDDDDD);
    BOOST_CHECK_EQUAL(obj->statLostPacketCount, 0xEEEEEEEE);
    BOOST_CHECK_EQUAL(obj->line, 0xFF);
    BOOST_CHECK_EQUAL(obj->linkStatus, 0x11);
    BOOST_CHECK_EQUAL(obj->linkSpeed, 0x2222);
    BOOST_CHECK_EQUAL(obj->linkLost, 0x3333);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_BUS_STATISTIC);

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

BOOST_AUTO_TEST_CASE(AfdxStatistic_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_AfdxStatistic.blf");
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
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1000763955); // ns

    /* AfdxStatistic */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->flags, 0xb);
    BOOST_CHECK_EQUAL(obj->rxPacketCount, 3);
    BOOST_CHECK_EQUAL(obj->rxByteCount, 417);
    BOOST_CHECK_EQUAL(obj->txPacketCount, 0);
    BOOST_CHECK_EQUAL(obj->txByteCount, 0);
    BOOST_CHECK_EQUAL(obj->collisionCount, 0);
    BOOST_CHECK_EQUAL(obj->errorCount, 0);
    BOOST_CHECK_EQUAL(obj->statDroppedRedundantPacketCount, 0);
    BOOST_CHECK_EQUAL(obj->statRedundantErrorPacketCount, 0);
    BOOST_CHECK_EQUAL(obj->statIntegrityErrorPacketCount, 0);
    BOOST_CHECK_EQUAL(obj->statAvrgPeriodMsec, 0);
    BOOST_CHECK_EQUAL(obj->statAvrgJitterMysec, 0);
    BOOST_CHECK_EQUAL(obj->vlid, 0);
    BOOST_CHECK_EQUAL(obj->statDuration, 0);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
