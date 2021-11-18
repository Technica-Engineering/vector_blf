// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE DiagRequestInterpretation
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* DIAG_REQUEST_INTERPRETATION = 119 */
BOOST_AUTO_TEST_CASE(DiagRequestInterpretation) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_DiagRequestInterpretation.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::DIAG_REQUEST_INTERPRETATION);
    auto * obj = dynamic_cast<Vector::BLF::DiagRequestInterpretation *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::DIAG_REQUEST_INTERPRETATION);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* DiagRequestInterpretation */
    BOOST_CHECK_EQUAL(obj->diagDescriptionHandle, 0x11111111);
    BOOST_CHECK_EQUAL(obj->diagVariantHandle, 0x22222222);
    BOOST_CHECK_EQUAL(obj->diagServiceHandle, 0x33333333);
    BOOST_CHECK_EQUAL(obj->ecuQualifierLength, 3);
    BOOST_CHECK_EQUAL(obj->variantQualifierLength, 3);
    BOOST_CHECK_EQUAL(obj->serviceQualifierLength, 3);
    BOOST_CHECK_EQUAL(obj->ecuQualifier, "xyz");
    BOOST_CHECK_EQUAL(obj->variantQualifier, "xyz");
    BOOST_CHECK_EQUAL(obj->serviceQualifier, "xyz");

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::DIAG_REQUEST_INTERPRETATION);

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
