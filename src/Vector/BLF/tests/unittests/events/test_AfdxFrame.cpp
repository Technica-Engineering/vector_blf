#define BOOST_TEST_MODULE AfdxFrame
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* AFDX_FRAME = 97 */
BOOST_AUTO_TEST_CASE(AfdxFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_AfdxFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::AfdxFrame * afdxFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    afdxFrame = static_cast<Vector::BLF::AfdxFrame *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(afdxFrame->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(afdxFrame->headerSize == afdxFrame->calculateHeaderSize());
    BOOST_CHECK(afdxFrame->headerVersion == 1);
    BOOST_CHECK(afdxFrame->objectSize == afdxFrame->calculateObjectSize());
    BOOST_CHECK(afdxFrame->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    /* ObjectHeader */
    BOOST_CHECK(afdxFrame->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(afdxFrame->objectVersion == 0);
    BOOST_CHECK(afdxFrame->objectTimeStamp == 0); // ns
    /* AfdxFrame */
    BOOST_CHECK(afdxFrame->sourceAddress[0] == 0x40);
    BOOST_CHECK(afdxFrame->sourceAddress[1] == 0x00);
    BOOST_CHECK(afdxFrame->sourceAddress[2] == 0x00);
    BOOST_CHECK(afdxFrame->sourceAddress[3] == 0x00);
    BOOST_CHECK(afdxFrame->sourceAddress[4] == 0x00);
    BOOST_CHECK(afdxFrame->sourceAddress[5] == 0x04);
    BOOST_CHECK(afdxFrame->channel == 0x0001);
    BOOST_CHECK(afdxFrame->destinationAddress[0] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[1] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[2] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[3] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[4] == 0xff);
    BOOST_CHECK(afdxFrame->destinationAddress[5] == 0xff);
    BOOST_CHECK(afdxFrame->dir == Vector::BLF::AfdxFrame::Dir::Tx);
    BOOST_CHECK(afdxFrame->type == 0x0806);
    BOOST_CHECK(afdxFrame->tpid == 0x0000);
    BOOST_CHECK(afdxFrame->tci == 0x0000);
    BOOST_CHECK(afdxFrame->ethChannel == 0x01);
    // reserved
    BOOST_CHECK(afdxFrame->afdxFlags == 0x0040);
    // reserved
    BOOST_CHECK(afdxFrame->bagUsec == 0);
    BOOST_CHECK(afdxFrame->payLoadLength == 0x002e);
    // reserved
    BOOST_CHECK(afdxFrame->payLoad[0x00] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x01] == 0x01);
    BOOST_CHECK(afdxFrame->payLoad[0x02] == 0x08);
    BOOST_CHECK(afdxFrame->payLoad[0x03] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x04] == 0x06);
    BOOST_CHECK(afdxFrame->payLoad[0x05] == 0x04);
    BOOST_CHECK(afdxFrame->payLoad[0x06] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x07] == 0x01);
    BOOST_CHECK(afdxFrame->payLoad[0x08] == 0x40);
    BOOST_CHECK(afdxFrame->payLoad[0x09] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x0a] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x0b] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x0c] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x0d] == 0x04);
    BOOST_CHECK(afdxFrame->payLoad[0x0e] == 0xc0);
    BOOST_CHECK(afdxFrame->payLoad[0x0f] == 0xa8);
    BOOST_CHECK(afdxFrame->payLoad[0x10] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x11] == 0x01);
    BOOST_CHECK(afdxFrame->payLoad[0x12] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x13] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x14] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x15] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x16] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x17] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x18] == 0xc0);
    BOOST_CHECK(afdxFrame->payLoad[0x19] == 0xa8);
    BOOST_CHECK(afdxFrame->payLoad[0x1a] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x1b] == 0x01);
    BOOST_CHECK(afdxFrame->payLoad[0x1c] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x1d] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x1e] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x1f] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x20] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x21] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x22] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x23] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x24] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x25] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x26] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x27] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x28] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x29] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x2a] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x2b] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x2c] == 0x00);
    BOOST_CHECK(afdxFrame->payLoad[0x2d] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
