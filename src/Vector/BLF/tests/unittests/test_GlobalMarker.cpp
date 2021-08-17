// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE GlobalMarker
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* GLOBAL_MARKER = 96 */
BOOST_AUTO_TEST_CASE(GlobalMarker_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_GlobalMarker.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);
    auto * obj = dynamic_cast<Vector::BLF::GlobalMarker *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* GlobalMarker */
    BOOST_CHECK_EQUAL(obj->commentedEventType, 0x11111111);
    BOOST_CHECK_EQUAL(obj->foregroundColor, 0x22222222);
    BOOST_CHECK_EQUAL(obj->backgroundColor, 0x33333333);
    BOOST_CHECK_EQUAL(obj->isRelocatable, 0x44);
    BOOST_CHECK_EQUAL(obj->reservedGlobalMarker1, 0);
    BOOST_CHECK_EQUAL(obj->reservedGlobalMarker2, 0);
    BOOST_CHECK_EQUAL(obj->groupNameLength, 3);
    BOOST_CHECK_EQUAL(obj->markerNameLength, 3);
    BOOST_CHECK_EQUAL(obj->descriptionLength, 3);
    BOOST_CHECK_EQUAL(obj->reservedGlobalMarker3, 0);
    BOOST_CHECK_EQUAL(obj->reservedGlobalMarker4, 0);
    BOOST_CHECK_EQUAL(obj->groupName, "xyz");
    BOOST_CHECK_EQUAL(obj->markerName, "xyz");
    BOOST_CHECK_EQUAL(obj->description, "xyz");

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);

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

BOOST_AUTO_TEST_CASE(GlobalMarker_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_GlobalMarker.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);
    auto * obj = dynamic_cast<Vector::BLF::GlobalMarker *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    //BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize()); // Vector bug: sizeof(EventComment) + ...
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 2200804000); // ns

    /* GlobalMarker */
    BOOST_CHECK_EQUAL(obj->commentedEventType, 0);
    BOOST_CHECK_EQUAL(obj->foregroundColor, 0);
    BOOST_CHECK_EQUAL(obj->backgroundColor, 0x00FFFFFF);
    BOOST_CHECK_EQUAL(obj->isRelocatable, 0x50); // ?
    BOOST_CHECK_EQUAL(obj->reservedGlobalMarker1, 0xB0); // ?
    BOOST_CHECK_EQUAL(obj->reservedGlobalMarker2, 0x0136); // ?
    BOOST_CHECK_EQUAL(obj->groupNameLength, 0x83);
    BOOST_CHECK_EQUAL(obj->markerNameLength, 0x83);
    BOOST_CHECK_EQUAL(obj->descriptionLength, 0x105);
    obj->groupName.resize(strnlen(obj->groupName.c_str(), obj->groupName.size())); // Vector bug
    BOOST_CHECK_EQUAL(obj->groupName, "Marker Group");
    obj->markerName.resize(strnlen(obj->markerName.c_str(), obj->markerName.size())); // Vector bug
    BOOST_CHECK_EQUAL(obj->markerName, "[1]");
    obj->description.resize(strnlen(obj->description.c_str(), obj->description.size())); // Vector bug
    BOOST_CHECK_EQUAL(obj->description, "description");

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
