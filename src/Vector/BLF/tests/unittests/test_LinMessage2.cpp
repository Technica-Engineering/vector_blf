// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE LinMessage2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_MESSAGE2 = 57 */
BOOST_AUTO_TEST_CASE(LinMessage2_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_LinMessage2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);
    auto * obj = dynamic_cast<Vector::BLF::LinMessage2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 3);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 0x1111111111111111);
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 0x22222222);
    BOOST_CHECK_EQUAL(obj->channel, 0x3333);
    BOOST_CHECK_EQUAL(obj->reservedLinBusEvent, 0x4444);

    /* LinSynchFieldEvent */
    BOOST_CHECK_EQUAL(obj->synchBreakLength, 0x1111111111111111);
    BOOST_CHECK_EQUAL(obj->synchDelLength, 0x2222222222222222);

    /* LinMessageDescriptor */
    BOOST_CHECK_EQUAL(obj->supplierId, 0x1111);
    BOOST_CHECK_EQUAL(obj->messageId, 0x2222);
    BOOST_CHECK_EQUAL(obj->nad, 0x33);
    BOOST_CHECK_EQUAL(obj->id, 0x44);
    BOOST_CHECK_EQUAL(obj->dlc, 0x55);
    BOOST_CHECK_EQUAL(obj->checksumModel, 0x66);

    /* LinDatabyteTimestampEvent */
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[0], 0x1111111111111111);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[1], 0x2222222222222222);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[2], 0x3333333333333333);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[3], 0x4444444444444444);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[4], 0x5555555555555555);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[5], 0x6666666666666666);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[6], 0x7777777777777777);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[7], 0x8888888888888888);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[8], 0x9999999999999999);

    /* LinMessage2 */
    BOOST_CHECK_EQUAL(obj->data[0], 0x11);
    BOOST_CHECK_EQUAL(obj->data[1], 0x22);
    BOOST_CHECK_EQUAL(obj->data[2], 0x33);
    BOOST_CHECK_EQUAL(obj->data[3], 0x44);
    BOOST_CHECK_EQUAL(obj->data[4], 0x55);
    BOOST_CHECK_EQUAL(obj->data[5], 0x66);
    BOOST_CHECK_EQUAL(obj->data[6], 0x77);
    BOOST_CHECK_EQUAL(obj->data[7], 0x88);
    BOOST_CHECK_EQUAL(obj->crc, 0x9999);
    BOOST_CHECK_EQUAL(obj->dir, 0xAA);
    BOOST_CHECK_EQUAL(obj->simulated, 0xBB);
    BOOST_CHECK_EQUAL(obj->isEtf, 0xCC);
    BOOST_CHECK_EQUAL(obj->etfAssocIndex, 0xDD);
    BOOST_CHECK_EQUAL(obj->etfAssocEtfId, 0xEE);
    BOOST_CHECK_EQUAL(obj->fsmId, 0xFF);
    BOOST_CHECK_EQUAL(obj->fsmState, 0x11);
    BOOST_CHECK_EQUAL(obj->reservedLinMessage1, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedLinMessage2, 0x3333);
    BOOST_CHECK_EQUAL(obj->respBaudrate, 0x44444444);
    BOOST_CHECK_EQUAL(obj->exactHeaderBaudrate, 5.0);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffset, 0x66666666);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffsetResponse, 0x77777777);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);

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

BOOST_AUTO_TEST_CASE(LinMessage2_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_LinMessage2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);
    auto * obj = dynamic_cast<Vector::BLF::LinMessage2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 73973000); // ns

    /* LinMessage2 */
    BOOST_CHECK_EQUAL(obj->data[0], 0x00);
    BOOST_CHECK_EQUAL(obj->data[1], 0xf0);
    BOOST_CHECK_EQUAL(obj->data[2], 0xf0);
    BOOST_CHECK_EQUAL(obj->data[3], 0xff);
    BOOST_CHECK_EQUAL(obj->data[4], 0xff);
    BOOST_CHECK_EQUAL(obj->data[5], 0xff);
    BOOST_CHECK_EQUAL(obj->data[6], 0xff);
    BOOST_CHECK_EQUAL(obj->data[7], 0xff);
    BOOST_CHECK_EQUAL(obj->crc, 0x70);
    BOOST_CHECK_EQUAL(obj->dir, 1); // Tx
    BOOST_CHECK_EQUAL(obj->simulated, 1);
    BOOST_CHECK_EQUAL(obj->isEtf, 0);
    BOOST_CHECK_EQUAL(obj->etfAssocIndex, 0);
    BOOST_CHECK_EQUAL(obj->etfAssocEtfId, 0xff);
    BOOST_CHECK_EQUAL(obj->fsmId, 0xff);
    BOOST_CHECK_EQUAL(obj->fsmState, 0xff);
    // reserved
    BOOST_CHECK_EQUAL(obj->respBaudrate, 19231);
    BOOST_CHECK_EQUAL(obj->exactHeaderBaudrate, 19230.769231);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffset, 26000);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffsetResponse, 26000);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/** write and read a LinMessage with objectVersion0 */
BOOST_AUTO_TEST_CASE(LinMessageVersion0) {
    Vector::BLF::UncompressedFile file;

    /* write to file */
    Vector::BLF::LinMessage2 linMessage1;
    BOOST_CHECK_EQUAL(linMessage1.calculateObjectSize(), 0xB8);
    linMessage1.apiMajor = 1;
    BOOST_CHECK_EQUAL(linMessage1.calculateObjectSize(), 0xA4);
    linMessage1.write(file);

    /* read from file */
    Vector::BLF::LinMessage2 linMessage2;
    linMessage2.read(file);
    BOOST_CHECK_EQUAL(linMessage2.apiMajor, 1);
}
