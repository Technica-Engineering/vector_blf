// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE LinReceiveError2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_RCV_ERROR2 = 61 */
BOOST_AUTO_TEST_CASE(LinReceiveError2_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_LinReceiveError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR2);
    auto * obj = dynamic_cast<Vector::BLF::LinReceiveError2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR2);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
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

    /* LinReceiveError2 */
    BOOST_CHECK_EQUAL(obj->data[0], 0x11);
    BOOST_CHECK_EQUAL(obj->data[1], 0x22);
    BOOST_CHECK_EQUAL(obj->data[2], 0x33);
    BOOST_CHECK_EQUAL(obj->data[3], 0x44);
    BOOST_CHECK_EQUAL(obj->data[4], 0x55);
    BOOST_CHECK_EQUAL(obj->data[5], 0x66);
    BOOST_CHECK_EQUAL(obj->data[6], 0x77);
    BOOST_CHECK_EQUAL(obj->data[7], 0x88);
    BOOST_CHECK_EQUAL(obj->fsmId, 0x99);
    BOOST_CHECK_EQUAL(obj->fsmState, 0xAA);
    BOOST_CHECK_EQUAL(obj->stateReason, 0xBB);
    BOOST_CHECK_EQUAL(obj->offendingByte, 0xCC);
    BOOST_CHECK_EQUAL(obj->shortError, 0xDD);
    BOOST_CHECK_EQUAL(obj->timeoutDuringDlcDetection, 0xEE);
    BOOST_CHECK_EQUAL(obj->isEtf, 0xFF);
    BOOST_CHECK_EQUAL(obj->hasDatabytes, 0x11);
    BOOST_CHECK_EQUAL(obj->respBaudrate, 0x22222222);
    BOOST_CHECK_EQUAL(obj->reservedLinReceiveError, 0x33333333);
    BOOST_CHECK_EQUAL(obj->exactHeaderBaudrate, 4.0);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffset, 0x55555555);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffsetResponse, 0x66666666);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR2);

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

BOOST_AUTO_TEST_CASE(LinReceiveError2_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_LinReceiveError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR2);
    auto * obj = dynamic_cast<Vector::BLF::LinReceiveError2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR2);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 554673000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 546052000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 19230);
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved

    /* LinSynchFieldEvent */
    BOOST_CHECK_EQUAL(obj->synchBreakLength, 937187);
    BOOST_CHECK_EQUAL(obj->synchDelLength, 112437);

    /* LinReceiveError2 */
    BOOST_CHECK_EQUAL(obj->supplierId, 0);
    BOOST_CHECK_EQUAL(obj->messageId, 0);
    BOOST_CHECK_EQUAL(obj->nad, 0);
    BOOST_CHECK_EQUAL(obj->id, 0x33);
    BOOST_CHECK_EQUAL(obj->dlc, 8);
    BOOST_CHECK_EQUAL(obj->checksumModel, 0xff);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[0], 548121000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[1], 548644000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[2], 549167000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[3], 549690000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[4], 550213000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[5], 550736000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[6], 551259000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[7], 551782000);
    BOOST_CHECK_EQUAL(obj->databyteTimestamps[8], 552305000);
    BOOST_CHECK_EQUAL(obj->data[0], 0x05);
    BOOST_CHECK_EQUAL(obj->data[1], 0x00);
    BOOST_CHECK_EQUAL(obj->data[2], 0x00);
    BOOST_CHECK_EQUAL(obj->data[3], 0x00);
    BOOST_CHECK_EQUAL(obj->data[4], 0x00);
    BOOST_CHECK_EQUAL(obj->data[5], 0xff);
    BOOST_CHECK_EQUAL(obj->data[6], 0xff);
    BOOST_CHECK_EQUAL(obj->data[7], 0xff);
    BOOST_CHECK_EQUAL(obj->fsmId, 0xff);
    BOOST_CHECK_EQUAL(obj->fsmState, 0xff);
    BOOST_CHECK_EQUAL(obj->stateReason, 12);
    BOOST_CHECK_EQUAL(obj->offendingByte, 0);
    BOOST_CHECK_EQUAL(obj->shortError, 0);
    BOOST_CHECK_EQUAL(obj->timeoutDuringDlcDetection, 0);
    BOOST_CHECK_EQUAL(obj->isEtf, 0);
    BOOST_CHECK_EQUAL(obj->hasDatabytes, 1);
    BOOST_CHECK_EQUAL(obj->respBaudrate, 19231);
    // reserved
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
