// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE SerialEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* SERIAL_EVENT = 90 */
BOOST_AUTO_TEST_CASE(SerialEvent_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_SerialEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);
    auto * obj = dynamic_cast<Vector::BLF::SerialEvent *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* SerialEvent */
    BOOST_REQUIRE_EQUAL(obj->flags, Vector::BLF::SerialEvent::Flags::KLineEvent);
    BOOST_CHECK_EQUAL(obj->port, 0x22222222);
    BOOST_CHECK_EQUAL(obj->baudrate, 0x33333333);
    BOOST_CHECK_EQUAL(obj->reservedSerialEvent, 0x44444444);

    /* GeneralSerialEvent */
    BOOST_CHECK_EQUAL(obj->general.dataLength, 3);
    BOOST_CHECK_EQUAL(obj->general.timeStampsLength, 3 * sizeof(int64_t));
    BOOST_CHECK_EQUAL(obj->general.data[0], 0x11);
    BOOST_CHECK_EQUAL(obj->general.data[1], 0x22);
    BOOST_CHECK_EQUAL(obj->general.data[2], 0x33);
    BOOST_CHECK_EQUAL(obj->general.timeStamps[0], 0x4444);
    BOOST_CHECK_EQUAL(obj->general.timeStamps[1], 0x5555);
    BOOST_CHECK_EQUAL(obj->general.timeStamps[2], 0x6666);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);
    obj = static_cast<Vector::BLF::SerialEvent *>(ohb);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_REQUIRE_EQUAL(obj->flags, Vector::BLF::SerialEvent::Flags::SingleByte);
    /* SingleByteSerialEvent */
    BOOST_CHECK_EQUAL(obj->singleByte.byte, 0x11);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);
    obj = static_cast<Vector::BLF::SerialEvent *>(ohb);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_REQUIRE_EQUAL(obj->flags, Vector::BLF::SerialEvent::Flags::CompactByte);
    /* CompactSerialEvent */
    BOOST_CHECK_EQUAL(obj->compact.compactLength, 3);
    BOOST_CHECK_EQUAL(obj->compact.compactData[0], 0x11);
    BOOST_CHECK_EQUAL(obj->compact.compactData[1], 0x22);
    BOOST_CHECK_EQUAL(obj->compact.compactData[2], 0x33);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);

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

BOOST_AUTO_TEST_CASE(SerialEvent_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_SerialEvent.blf");
    BOOST_REQUIRE(file.is_open());


    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);
    auto * obj = dynamic_cast<Vector::BLF::SerialEvent *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 12315000000); // ns

    /* SerialEvent */
    BOOST_CHECK_EQUAL(obj->flags,
                      Vector::BLF::SerialEvent::Flags::KLineEvent |
                      Vector::BLF::SerialEvent::Flags::CompactByte);
    BOOST_CHECK_EQUAL(obj->port, 2);
    BOOST_CHECK_EQUAL(obj->baudrate, 10400);
    BOOST_CHECK_EQUAL(obj->reservedSerialEvent, 0);

    /* CompactSerialEvent */
    BOOST_CHECK_EQUAL(obj->compact.compactLength, 7);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 0], 0x83);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 1], 0x11);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 2], 0x61);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 3], 0x7F);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 4], 0x1A);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 5], 0x78);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 6], 0x06);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 7], 0xCA);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 8], 0x04);
    BOOST_CHECK_EQUAL(obj->compact.compactData[ 9], 0x03);
    BOOST_CHECK_EQUAL(obj->compact.compactData[10], 0x00);
    BOOST_CHECK_EQUAL(obj->compact.compactData[11], 0x2B);
    BOOST_CHECK_EQUAL(obj->compact.compactData[12], 0x10);
    BOOST_CHECK_EQUAL(obj->compact.compactData[13], 0x00);
    BOOST_CHECK_EQUAL(obj->compact.compactData[14], 0x00);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
