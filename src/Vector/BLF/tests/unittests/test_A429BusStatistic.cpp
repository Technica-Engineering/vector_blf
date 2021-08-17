// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE A429BusStatistic
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* A429_BUS_STATISTIC = 112 */
BOOST_AUTO_TEST_CASE(A429BusStatistic) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_A429BusStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::A429_BUS_STATISTIC);
    auto * obj = dynamic_cast<Vector::BLF::A429BusStatistic *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::A429_BUS_STATISTIC);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* A429BusStatistic */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->dir, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedA429BusStatistic, 0);
    BOOST_CHECK_EQUAL(obj->busload, 0x33333333);
    BOOST_CHECK_EQUAL(obj->dataTotal, 0x44444444);
    BOOST_CHECK_EQUAL(obj->errorTotal, 0x55555555);
    BOOST_CHECK_EQUAL(obj->bitrate, 0x66666666);
    BOOST_CHECK_EQUAL(obj->parityErrors, 0x7777);
    BOOST_CHECK_EQUAL(obj->bitrateErrors, 0x8888);
    BOOST_CHECK_EQUAL(obj->gapErrors, 0x9999);
    BOOST_CHECK_EQUAL(obj->lineErrors, 0xAAAA);
    BOOST_CHECK_EQUAL(obj->formatErrors, 0xBBBB);
    BOOST_CHECK_EQUAL(obj->dutyFactorErrors, 0xCCCC);
    BOOST_CHECK_EQUAL(obj->wordLenErrors, 0xDDDD);
    BOOST_CHECK_EQUAL(obj->codingErrors, 0xEEEE);
    BOOST_CHECK_EQUAL(obj->idleErrors, 0xFFFF);
    BOOST_CHECK_EQUAL(obj->levelErrors, 0x1111);
    for (uint16_t i = 0; i < 256; i++)
        BOOST_CHECK_EQUAL(obj->labelCount[i], i);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::A429_BUS_STATISTIC);

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
