// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE FlexRayVFrError
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* FR_ERROR = 47 */
BOOST_AUTO_TEST_CASE(FlexRayVFrError) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_FlexRayVFrError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_ERROR);
    auto * obj = dynamic_cast<Vector::BLF::FlexRayVFrError *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FR_ERROR);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* FlexRayVFrError */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->version, 0x2222);
    BOOST_CHECK_EQUAL(obj->channelMask, 0x3333);
    BOOST_CHECK_EQUAL(obj->cycle, 0x44);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrError1, 0);
    BOOST_CHECK_EQUAL(obj->clientIndexFlexRayVFrError, 0x55555555);
    BOOST_CHECK_EQUAL(obj->clusterNo, 0x66666666);
    BOOST_CHECK_EQUAL(obj->tag, 0x77777777);
    BOOST_CHECK_EQUAL(obj->data[0], 0x88888888);
    BOOST_CHECK_EQUAL(obj->data[1], 0x99999999);
    BOOST_CHECK_EQUAL(obj->data[2], 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->data[3], 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayVFrError2, 0xCCCC);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_ERROR);

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
