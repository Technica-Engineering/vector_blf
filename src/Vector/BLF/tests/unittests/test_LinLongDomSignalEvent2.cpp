// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE LinLongDomSignalEvent2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_LONG_DOM_SIG2 = 75 */
BOOST_AUTO_TEST_CASE(LinLongDomSignalEvent2_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_LinLongDomSignalEvent2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    auto * obj = dynamic_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);

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

    /* LinLongDomSignalEvent2 */
    BOOST_CHECK_EQUAL(obj->type, 0x11);
    BOOST_CHECK_EQUAL(obj->reservedLinLongDomSignalEvent1, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedLinLongDomSignalEvent2, 0x4433);
    BOOST_CHECK_EQUAL(obj->reservedLinLongDomSignalEvent3, 0x88776655);
    BOOST_CHECK_EQUAL(obj->length, 0xAAAAAAAAAAAAAAAA);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);

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

BOOST_AUTO_TEST_CASE(LinLongDomSignalEvent2_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_LinLongDomSignalEvent2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    auto * obj = dynamic_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 8976802000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 8971798000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 9615);
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved

    /* LinLongDomSignalEvent2 */
    BOOST_CHECK_EQUAL(obj->type, 0); // Signal just detected
    // reserved
    BOOST_CHECK_EQUAL(obj->length, 5003000); // us

    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    obj = static_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 8977000000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 8971798000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 9615);
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved

    /* LinLongDomSignalEvent2 */
    BOOST_CHECK_EQUAL(obj->type, 2); // Signal continuation
    // reserved
    BOOST_CHECK_EQUAL(obj->length, 5201000); // us

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
