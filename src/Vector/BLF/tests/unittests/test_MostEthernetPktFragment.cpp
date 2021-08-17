// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE MostEthernetPktFragment
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_ETHERNET_PKT_FRAGMENT = 81 */
BOOST_AUTO_TEST_CASE(MostEthernetPktFragment_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_MostEthernetPktFragment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT);
    auto * obj = dynamic_cast<Vector::BLF::MostEthernetPktFragment *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT);

    /* ObjectHeader2 */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedObjectHeader, 0x33);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x4444444444444444);
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0x5555555555555555);

    /* MostEthernetPktFragment */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->reservedMostEthernetPktFragment1, 0x22);
    BOOST_CHECK_EQUAL(obj->ackNack, 0x33);
    BOOST_CHECK_EQUAL(obj->validMask, 0x44444444);
    BOOST_CHECK_EQUAL(obj->sourceMacAdr, 0x55555555);
    BOOST_CHECK_EQUAL(obj->destMacAdr, 0x66666666);
    BOOST_CHECK_EQUAL(obj->pAck, 0x77);
    BOOST_CHECK_EQUAL(obj->cAck, 0x88);
    BOOST_CHECK_EQUAL(obj->reservedMostEthernetPktFragment2, 0x9999);
    BOOST_CHECK_EQUAL(obj->crc, 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->dataLen, 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->dataLenAnnounced, 0xCCCCCCCC);
    BOOST_CHECK_EQUAL(obj->firstDataLen, 3);
    BOOST_CHECK_EQUAL(obj->reservedMostEthernetPktFragment3, 0);
    BOOST_CHECK_EQUAL(obj->firstData[0], 4);
    BOOST_CHECK_EQUAL(obj->firstData[1], 5);
    BOOST_CHECK_EQUAL(obj->firstData[2], 6);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT);

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

BOOST_AUTO_TEST_CASE(MostEthernetPktFragment_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_MostEthernetPktFragment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT);
    auto * obj = dynamic_cast<Vector::BLF::MostEthernetPktFragment *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT);

    /* ObjectHeader2 */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 5708800000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* MostEthernetPktFragment */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved
    BOOST_CHECK_EQUAL(obj->ackNack, 0x11); // Ack|NoResp
    BOOST_CHECK_EQUAL(obj->validMask, 0x01020304);
    BOOST_CHECK_EQUAL(obj->sourceMacAdr, 0x010203040506);
    BOOST_CHECK_EQUAL(obj->destMacAdr, 0x112233445566);
    BOOST_CHECK_EQUAL(obj->pAck, 0x01); // Buffer full
    BOOST_CHECK_EQUAL(obj->cAck, 0x44); // OK
    // reserved
    BOOST_CHECK_EQUAL(obj->crc, 0xAABBCCDD);
    BOOST_CHECK_EQUAL(obj->dataLen, 0x0006);
    BOOST_CHECK_EQUAL(obj->dataLenAnnounced, 0x0210);
    BOOST_CHECK_EQUAL(obj->firstDataLen, 0x0006);
    // reserved
    BOOST_CHECK_EQUAL(obj->firstData[0], 0x01);
    BOOST_CHECK_EQUAL(obj->firstData[1], 0x02);
    BOOST_CHECK_EQUAL(obj->firstData[2], 0x03);
    BOOST_CHECK_EQUAL(obj->firstData[3], 0x04);
    BOOST_CHECK_EQUAL(obj->firstData[4], 0x05);
    BOOST_CHECK_EQUAL(obj->firstData[5], 0x06);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
