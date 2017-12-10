#define BOOST_TEST_MODULE MostSpy
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_SPY = 22 */
BOOST_AUTO_TEST_CASE(MostSpy)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostSpy.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostSpy * mostSpy;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_SPY);
    mostSpy = static_cast<Vector::BLF::MostSpy *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostSpy->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostSpy->headerSize == mostSpy->calculateHeaderSize());
    BOOST_CHECK(mostSpy->headerVersion == 1);
    BOOST_CHECK(mostSpy->objectSize == mostSpy->calculateObjectSize());
    BOOST_CHECK(mostSpy->objectType == Vector::BLF::ObjectType::MOST_SPY);
    /* ObjectHeader */
    BOOST_CHECK(mostSpy->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(mostSpy->objectVersion == 0);
    BOOST_CHECK(mostSpy->objectTimeStamp == 113526000); // ns
    /* MostSpy */
    BOOST_CHECK(mostSpy->channel == 1);
    BOOST_CHECK(mostSpy->dir == 0); // Rx
    // reserved
    BOOST_CHECK(mostSpy->sourceAdr == 0xffff);
    BOOST_CHECK(mostSpy->destAdr == 0x0100);
    BOOST_CHECK(mostSpy->msg[ 0] == 0x01);
    BOOST_CHECK(mostSpy->msg[ 1] == 0x01);
    BOOST_CHECK(mostSpy->msg[ 2] == 0x00);
    BOOST_CHECK(mostSpy->msg[ 3] == 0x0C);
    BOOST_CHECK(mostSpy->msg[ 4] == 0x04);
    BOOST_CHECK(mostSpy->msg[ 5] == 0x31);
    BOOST_CHECK(mostSpy->msg[ 6] == 0x01);
    BOOST_CHECK(mostSpy->msg[ 7] == 0x52);
    BOOST_CHECK(mostSpy->msg[ 8] == 0x01);
    BOOST_CHECK(mostSpy->msg[ 9] == 0x00);
    BOOST_CHECK(mostSpy->msg[10] == 0x00);
    BOOST_CHECK(mostSpy->msg[11] == 0x00);
    BOOST_CHECK(mostSpy->msg[12] == 0x00);
    BOOST_CHECK(mostSpy->msg[13] == 0x00);
    BOOST_CHECK(mostSpy->msg[14] == 0x00);
    BOOST_CHECK(mostSpy->msg[15] == 0x00);
    BOOST_CHECK(mostSpy->msg[16] == 0x00);
    // reserved
    BOOST_CHECK(mostSpy->rTyp == 0); // Normal
    BOOST_CHECK(mostSpy->rTypAdr == 0x10); // Node position
    BOOST_CHECK(mostSpy->state == 0x01); // bus active
    // reserved
    BOOST_CHECK(mostSpy->ackNack == 0x12); // Valid | NAck
    BOOST_CHECK(mostSpy->crc == 0xAA33);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
