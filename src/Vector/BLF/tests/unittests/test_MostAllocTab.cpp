// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE MostAllocTab
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_ALLOCTAB = 69 */
BOOST_AUTO_TEST_CASE(MostAllocTab_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_MostAllocTab.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ALLOCTAB);
    auto * obj = dynamic_cast<Vector::BLF::MostAllocTab *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_ALLOCTAB);

    /* ObjectHeader2 */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedObjectHeader, 0x33);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x4444444444444444);
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0x5555555555555555);

    /* MostAllocTab */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->length, 3);
    BOOST_CHECK_EQUAL(obj->reservedMostAllocTab, 0);
    BOOST_CHECK_EQUAL(obj->tableData[0], 4);
    BOOST_CHECK_EQUAL(obj->tableData[1], 5);
    BOOST_CHECK_EQUAL(obj->tableData[2], 6);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ALLOCTAB);

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

BOOST_AUTO_TEST_CASE(MostAllocTab_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_MostAllocTab.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ALLOCTAB);
    auto * obj = dynamic_cast<Vector::BLF::MostAllocTab *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_ALLOCTAB);

    /* ObjectHeader2 */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 32775000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* MostAllocTab */
    BOOST_CHECK_EQUAL(obj->channel, 2);
    BOOST_CHECK_EQUAL(obj->length, 0x3C);
    // reserved
    BOOST_CHECK_EQUAL(obj->tableData[0x00], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x01], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x02], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x03], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x04], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x05], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x06], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x07], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x08], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x09], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x0a], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x0b], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x0c], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x0d], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x0e], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x0f], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x10], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x11], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x12], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x13], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x14], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x15], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x16], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x17], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x18], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x19], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x1a], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x1b], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x1c], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x1d], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x1e], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x1f], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x20], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x21], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x22], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x23], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x24], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x25], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x26], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x27], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x28], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x29], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x2a], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x2b], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x2c], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x2d], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x2e], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x2f], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x30], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x31], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x32], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x33], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x34], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x35], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x36], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x37], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x38], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x39], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x3a], 0x70);
    BOOST_CHECK_EQUAL(obj->tableData[0x3b], 0x70);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
