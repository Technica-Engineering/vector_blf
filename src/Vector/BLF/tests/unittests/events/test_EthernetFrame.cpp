#define BOOST_TEST_MODULE EthernetFrame
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* ETHERNET_FRAME = 71 */
BOOST_AUTO_TEST_CASE(EthernetFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_EthernetFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EthernetFrame * ethernetFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);
    ethernetFrame = static_cast<Vector::BLF::EthernetFrame *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(ethernetFrame->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(ethernetFrame->headerSize == ethernetFrame->calculateHeaderSize());
    BOOST_CHECK(ethernetFrame->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(ethernetFrame->objectSize == ethernetFrame->calculateObjectSize());
    BOOST_CHECK(ethernetFrame->objectType == Vector::BLF::ObjectType::ETHERNET_FRAME);
    /* ObjectHeader */
    BOOST_CHECK(ethernetFrame->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(ethernetFrame->objectVersion == 0);
    BOOST_CHECK(ethernetFrame->objectTimeStamp == 0); // ns
    /* EthernetFrame */
    BOOST_CHECK(ethernetFrame->sourceAddress[0] == 0x40);
    BOOST_CHECK(ethernetFrame->sourceAddress[1] == 0x00);
    BOOST_CHECK(ethernetFrame->sourceAddress[2] == 0x00);
    BOOST_CHECK(ethernetFrame->sourceAddress[3] == 0x00);
    BOOST_CHECK(ethernetFrame->sourceAddress[4] == 0x00);
    BOOST_CHECK(ethernetFrame->sourceAddress[5] == 0x04);
    BOOST_CHECK(ethernetFrame->channel == 2);
    BOOST_CHECK(ethernetFrame->destinationAddress[0] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[1] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[2] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[3] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[4] == 0xff);
    BOOST_CHECK(ethernetFrame->destinationAddress[5] == 0xff);
    BOOST_CHECK(ethernetFrame->dir == 1);
    BOOST_CHECK(ethernetFrame->type == 0x0806);
    BOOST_CHECK(ethernetFrame->tpid == 0x0000);
    BOOST_CHECK(ethernetFrame->tci == 0x0000);
    BOOST_CHECK(ethernetFrame->payLoadLength == 0x2e);
    // reserved
    BOOST_CHECK(ethernetFrame->payLoad[0x00] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x01] == 0x01);
    BOOST_CHECK(ethernetFrame->payLoad[0x02] == 0x08);
    BOOST_CHECK(ethernetFrame->payLoad[0x03] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x04] == 0x06);
    BOOST_CHECK(ethernetFrame->payLoad[0x05] == 0x04);
    BOOST_CHECK(ethernetFrame->payLoad[0x06] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x07] == 0x01);
    BOOST_CHECK(ethernetFrame->payLoad[0x08] == 0x40);
    BOOST_CHECK(ethernetFrame->payLoad[0x09] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x0a] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x0b] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x0c] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x0d] == 0x04);
    BOOST_CHECK(ethernetFrame->payLoad[0x0e] == 0xc0);
    BOOST_CHECK(ethernetFrame->payLoad[0x0f] == 0xa8);
    BOOST_CHECK(ethernetFrame->payLoad[0x10] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x11] == 0x01);
    BOOST_CHECK(ethernetFrame->payLoad[0x12] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x13] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x14] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x15] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x16] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x17] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x18] == 0xc0);
    BOOST_CHECK(ethernetFrame->payLoad[0x19] == 0xa8);
    BOOST_CHECK(ethernetFrame->payLoad[0x1a] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x1b] == 0x01);
    BOOST_CHECK(ethernetFrame->payLoad[0x1c] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x1d] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x1e] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x1f] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x20] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x21] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x22] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x23] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x24] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x25] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x26] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x27] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x28] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x29] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x2a] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x2b] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x2c] == 0x00);
    BOOST_CHECK(ethernetFrame->payLoad[0x2d] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
