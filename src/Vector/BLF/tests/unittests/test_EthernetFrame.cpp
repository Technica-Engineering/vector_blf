// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE EthernetFrame
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* ETHERNET_FRAME = 71 */
BOOST_AUTO_TEST_CASE(EthernetFrame_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_EthernetFrame.blf");
    // contains e02df3980261d1e46a93b78249a2b81e.lobj
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);
    auto * obj = dynamic_cast<Vector::BLF::EthernetFrame *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* EthernetFrame */
    BOOST_CHECK_EQUAL(obj->sourceAddress[0], 0x11);
    BOOST_CHECK_EQUAL(obj->sourceAddress[1], 0x22);
    BOOST_CHECK_EQUAL(obj->sourceAddress[2], 0x33);
    BOOST_CHECK_EQUAL(obj->sourceAddress[3], 0x44);
    BOOST_CHECK_EQUAL(obj->sourceAddress[4], 0x55);
    BOOST_CHECK_EQUAL(obj->sourceAddress[5], 0x66);
    BOOST_CHECK_EQUAL(obj->channel, 0x7777);
    BOOST_CHECK_EQUAL(obj->destinationAddress[0], 0x88);
    BOOST_CHECK_EQUAL(obj->destinationAddress[1], 0x99);
    BOOST_CHECK_EQUAL(obj->destinationAddress[2], 0xAA);
    BOOST_CHECK_EQUAL(obj->destinationAddress[3], 0xBB);
    BOOST_CHECK_EQUAL(obj->destinationAddress[4], 0xCC);
    BOOST_CHECK_EQUAL(obj->destinationAddress[5], 0xDD);
    BOOST_CHECK_EQUAL(obj->dir, 0xEEEE);
    BOOST_CHECK_EQUAL(obj->type, 0xFFFF);
    BOOST_CHECK_EQUAL(obj->tpid, 0x1111);
    BOOST_CHECK_EQUAL(obj->tci, 0x2222);
    BOOST_CHECK_EQUAL(obj->payLoadLength, 3);
    // reserved
    BOOST_CHECK_EQUAL(obj->payLoad[0], 4);
    BOOST_CHECK_EQUAL(obj->payLoad[1], 5);
    BOOST_CHECK_EQUAL(obj->payLoad[2], 6);
    // @todo padding 2 bytes

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);
    // @todo padding 3 bytes

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

BOOST_AUTO_TEST_CASE(EthernetFrame_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_EthernetFrame.blf");
    // contains eeff3faf012cc9a9eb7efcb186f79480.lobj
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);
    auto * obj = dynamic_cast<Vector::BLF::EthernetFrame *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0); // ns

    /* EthernetFrame */
    std::vector<uint8_t> expectedSourceAddress = {
        0x40, 0x00, 0x00, 0x00, 0x00, 0x04
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->sourceAddress.begin(), obj->sourceAddress.end(), expectedSourceAddress.begin(), expectedSourceAddress.end());
    BOOST_CHECK_EQUAL(obj->channel, 2);
    std::vector<uint8_t> expectedDestinationAddress = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->destinationAddress.begin(), obj->destinationAddress.end(), expectedDestinationAddress.begin(), expectedDestinationAddress.end());
    BOOST_CHECK_EQUAL(obj->dir, 1);
    BOOST_CHECK_EQUAL(obj->type, 0x0806);
    BOOST_CHECK_EQUAL(obj->tpid, 0x0000);
    BOOST_CHECK_EQUAL(obj->tci, 0x0000);
    BOOST_CHECK_EQUAL(obj->payLoadLength, 0x2e);
    BOOST_CHECK_EQUAL(obj->reservedEthernetFrame, 0x0000102b1936211e);
    // reserved (0x1e, 0x21, 0x36, 0x19)
    std::vector<uint8_t> expectedPayLoad = {
        0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
        0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0xc0, 0xa8,
        0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xc0, 0xa8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->payLoad.begin(), obj->payLoad.end(), expectedPayLoad.begin(), expectedPayLoad.end());
    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

#if 0
BOOST_AUTO_TEST_CASE(EthernetFrame_7a5d95c7e63f268ca2d7492c2201b805) {
    Vector::BLF::CompressedFile file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/lobj/EthernetFrame/7a5d95c7e63f268ca2d7492c2201b805.lobj", std::ios_base::in | std::ios_base::binary);
    BOOST_REQUIRE(file.is_open());

    auto obj = new Vector::BLF::EthernetFrame;
    obj->read(file);
    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, 128);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize()); // @todo 128 != 126
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 39323000); // ns

    /* EthernetFrame */
    const std::vector<uint8_t> expectedSourceAddress = {
        0x02, 0x7d, 0xfa, 0x00, 0x10, 0x02
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->sourceAddress.cbegin(), obj->sourceAddress.cend(), expectedSourceAddress.cbegin(), expectedSourceAddress.cend());
    BOOST_CHECK_EQUAL(obj->channel, 17);
    const std::vector<uint8_t> expectedDestinationAddress = {
        0x01, 0x80, 0xc2, 0x00, 0x00, 0x0e
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->destinationAddress.cbegin(), obj->destinationAddress.cend(), expectedDestinationAddress.cbegin(), expectedDestinationAddress.cend());
    BOOST_CHECK_EQUAL(obj->dir, 0);
    BOOST_CHECK_EQUAL(obj->type, 0x88f7);
    BOOST_CHECK_EQUAL(obj->tpid, 0x0000);
    BOOST_CHECK_EQUAL(obj->tci, 0x0000);
    BOOST_CHECK_EQUAL(obj->payLoadLength, 0x3e);
    // reserved
    const std::vector<uint8_t> expectedPayLoad =
    {
        0x00, 0x00, 0x01, 0x80, 0xc2, 0x00, 0x00, 0x0e,
        0x02, 0x7d, 0xfa, 0x00, 0x10, 0x02, 0x88, 0xf7,
        0x10, 0x02, 0x00, 0x2c, 0x00, 0x00, 0x02, 0x08,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x02, 0x7d, 0xfa, 0xff,
        0xfe, 0x00, 0x10, 0x02, 0x00, 0x05, 0x55, 0x90,
        0x00, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->payLoad.cbegin(), obj->payLoad.cend(), expectedPayLoad.cbegin(), expectedPayLoad.cend());
    delete obj;
}
#endif

#if 0
BOOST_AUTO_TEST_CASE(EthernetFrame_96f6b7bd1df9c40b778a4bb867130b8f) {
    Vector::BLF::CompressedFile file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/lobj/EthernetFrame/96f6b7bd1df9c40b778a4bb867130b8f.lobj", std::ios_base::in | std::ios_base::binary);
    BOOST_REQUIRE(file.is_open());

    auto obj = new Vector::BLF::EthernetFrame;
    obj->read(file);
    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, 234);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize()); // @todo 234 != 233
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 42507000); // ns

    /* EthernetFrame */
    const std::vector<uint8_t> expectedSourceAddress = {
        0x02, 0x7d, 0xfa, 0x00, 0x10, 0x00
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->sourceAddress.cbegin(), obj->sourceAddress.cend(), expectedSourceAddress.cbegin(), expectedSourceAddress.cend());
    BOOST_CHECK_EQUAL(obj->channel, 19);
    const std::vector<uint8_t> expectedDestinationAddress = {
        0x00, 0x22, 0xa0, 0xd1, 0x5b, 0x7c
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->destinationAddress.cbegin(), obj->destinationAddress.cend(), expectedDestinationAddress.cbegin(), expectedDestinationAddress.cend());
    BOOST_CHECK_EQUAL(obj->dir, 0);
    BOOST_CHECK_EQUAL(obj->type, 0x86dd);
    BOOST_CHECK_EQUAL(obj->tpid, 0x8100);
    BOOST_CHECK_EQUAL(obj->tci, 0x0003);
    BOOST_CHECK_EQUAL(obj->payLoadLength, 0xa9);
    // reserved
    const std::vector<uint8_t> expectedPayLoad =
    {
        0x00, 0x00, 0x00, 0x22, 0xa0, 0xd1, 0x5b, 0x7c,
        0x02, 0x7d, 0xfa, 0x00, 0x10, 0x00, 0x81, 0x00,
        0x60, 0x03, 0x86, 0xdd, 0x60, 0x00, 0x00, 0x00,
        0x00, 0x6d, 0x11, 0xff, 0xfd, 0x53, 0x7c, 0xb8,
        0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x10, 0xfd, 0x53, 0x7c, 0xb8,
        0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x73, 0xa7, 0x3a, 0xce, 0x34,
        0x00, 0x6d, 0x9a, 0x69, 0x60, 0x17, 0xc0, 0x50,
        0x00, 0x00, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x51,
        0x00, 0x00, 0x00, 0x4d, 0x30, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x0c, 0xbc, 0x17, 0xda, 0x20, 0x01,
        0x3f, 0x81, 0x64, 0xd3, 0x20, 0x02, 0x3f, 0x81,
        0x4c, 0x00, 0x20, 0x03, 0x3f, 0x81, 0x5e, 0xf5,
        0x20, 0x04, 0x3f, 0x81, 0x61, 0xdf, 0x00, 0x05,
        0x61, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x20,
        0x07, 0x00, 0x00, 0x00, 0x00, 0x20, 0x08, 0x00,
        0x00, 0x00, 0x00, 0x20, 0x09, 0x00, 0x00, 0x00,
        0x00, 0x20, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x10,
        0x0b, 0x08, 0xea, 0x20, 0x0c, 0x00, 0x00, 0x00,
        0x00
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->payLoad.cbegin(), obj->payLoad.cend(), expectedPayLoad.cbegin(), expectedPayLoad.cend());
    delete obj;
}
#endif

BOOST_AUTO_TEST_CASE(EthernetFrame_ab35e16512387c0782a690651d22d05c) {
    Vector::BLF::CompressedFile file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/lobj/EthernetFrame/ab35e16512387c0782a690651d22d05c.lobj", std::ios_base::in | std::ios_base::binary);
    BOOST_REQUIRE(file.is_open());

    auto obj = new Vector::BLF::EthernetFrame;
    obj->read(file);
    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, 148);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 36276000); // ns

    /* EthernetFrame */
    const std::vector<uint8_t> expectedSourceAddress = {
        0x02, 0x7d, 0xfa, 0x00, 0x10, 0x00
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->sourceAddress.cbegin(), obj->sourceAddress.cend(), expectedSourceAddress.cbegin(), expectedSourceAddress.cend());
    BOOST_CHECK_EQUAL(obj->channel, 10);
    const std::vector<uint8_t> expectedDestinationAddress = {
        0x33, 0x33, 0x00, 0x00, 0x00, 0x02
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->destinationAddress.cbegin(), obj->destinationAddress.cend(), expectedDestinationAddress.cbegin(), expectedDestinationAddress.cend());
    BOOST_CHECK_EQUAL(obj->dir, 0);
    BOOST_CHECK_EQUAL(obj->type, 0x86dd);
    BOOST_CHECK_EQUAL(obj->tpid, 0x8100);
    BOOST_CHECK_EQUAL(obj->tci, 0x0002);
    BOOST_CHECK_EQUAL(obj->payLoadLength, 0x54);
    // reserved
    const std::vector<uint8_t> expectedPayLoad =
    {
        0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x00, 0x02,
        0x02, 0x7d, 0xfa, 0x00, 0x10, 0x00, 0x81, 0x00,
        0x80, 0x02, 0x86, 0xdd, 0x60, 0x00, 0x00, 0x00,
        0x00, 0x18, 0x11, 0xff, 0xfd, 0x53, 0x7c, 0xb8,
        0x03, 0x83, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x10, 0xff, 0x14, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x02, 0xa7, 0xf2, 0xa6, 0x3d,
        0x00, 0x18, 0xfc, 0x6b, 0x00, 0x00, 0x00, 0x61,
        0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x38, 0x00,
        0x00, 0x01, 0x00, 0x00
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->payLoad.cbegin(), obj->payLoad.cend(), expectedPayLoad.cbegin(), expectedPayLoad.cend());
    delete obj;
}

BOOST_AUTO_TEST_CASE(EthernetFrame_eeff3faf012cc9a9eb7efcb186f79480) {
    Vector::BLF::CompressedFile file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/lobj/EthernetFrame/eeff3faf012cc9a9eb7efcb186f79480.lobj", std::ios_base::in | std::ios_base::binary);
    BOOST_REQUIRE(file.is_open());

    auto obj = new Vector::BLF::EthernetFrame;
    obj->read(file);
    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, 110); // @todo should be 112
    // BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0); // ns

    /* EthernetFrame */
    const std::vector<uint8_t> expectedSourceAddress = {
        0x40, 0x00, 0x00, 0x00, 0x00, 0x04
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->sourceAddress.cbegin(), obj->sourceAddress.cend(), expectedSourceAddress.cbegin(), expectedSourceAddress.cend());
    BOOST_CHECK_EQUAL(obj->channel, 0x2);
    const std::vector<uint8_t> expectedDestinationAddress = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->destinationAddress.cbegin(), obj->destinationAddress.cend(), expectedDestinationAddress.cbegin(), expectedDestinationAddress.cend());
    BOOST_CHECK_EQUAL(obj->dir, 1);
    BOOST_CHECK_EQUAL(obj->type, 0x0806);
    BOOST_CHECK_EQUAL(obj->tpid, 0x0000);
    BOOST_CHECK_EQUAL(obj->tci, 0x0000);
    BOOST_CHECK_EQUAL(obj->payLoadLength, 0x2e);
    // reserved = 0x1e, 0x21, 0x36, 0x19, 0x2b, 0x10, 0x00, 0x00
    const std::vector<uint8_t> expectedPayLoad =
    {
        0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
        0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0xc0, 0xa8,
        0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xc0, 0xa8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    BOOST_CHECK_EQUAL_COLLECTIONS(obj->payLoad.cbegin(), obj->payLoad.cend(), expectedPayLoad.cbegin(), expectedPayLoad.cend());
    delete obj;
}
