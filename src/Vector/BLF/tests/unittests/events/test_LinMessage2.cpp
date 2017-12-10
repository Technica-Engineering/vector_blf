#define BOOST_TEST_MODULE LinMessage2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

static bool isEqual(double a, double b)
{
    return ((a - b) < 0.000001) && ((b - a) < 0.000001);
}

/* LIN_MESSAGE2 = 57 */
BOOST_AUTO_TEST_CASE(LinMessage2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinMessage2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinMessage2 * linMessage2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);
    linMessage2 = static_cast<Vector::BLF::LinMessage2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linMessage2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linMessage2->headerSize == linMessage2->calculateHeaderSize());
    BOOST_CHECK(linMessage2->headerVersion == 1);
    BOOST_CHECK(linMessage2->objectSize == linMessage2->calculateObjectSize());
    BOOST_CHECK(linMessage2->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);
    /* ObjectHeader */
    BOOST_CHECK(linMessage2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linMessage2->objectVersion == 1);
    BOOST_CHECK(linMessage2->objectTimeStamp == 73973000); // ns
    /* LinMessage2 */
    BOOST_CHECK(linMessage2->data[0] == 0x00);
    BOOST_CHECK(linMessage2->data[1] == 0xf0);
    BOOST_CHECK(linMessage2->data[2] == 0xf0);
    BOOST_CHECK(linMessage2->data[3] == 0xff);
    BOOST_CHECK(linMessage2->data[4] == 0xff);
    BOOST_CHECK(linMessage2->data[5] == 0xff);
    BOOST_CHECK(linMessage2->data[6] == 0xff);
    BOOST_CHECK(linMessage2->data[7] == 0xff);
    BOOST_CHECK(linMessage2->crc == 0x70);
    BOOST_CHECK(linMessage2->dir == 1); // Tx
    BOOST_CHECK(linMessage2->simulated == 1);
    BOOST_CHECK(linMessage2->isEtf == 0);
    BOOST_CHECK(linMessage2->etfAssocIndex == 0);
    BOOST_CHECK(linMessage2->etfAssocEtfId == 0xff);
    BOOST_CHECK(linMessage2->fsmId == 0xff);
    BOOST_CHECK(linMessage2->fsmState == 0xff);
    // reserved
    BOOST_CHECK(linMessage2->respBaudrate == 19231);
    BOOST_CHECK(isEqual(linMessage2->exactHeaderBaudrate, 19230.769231));
    BOOST_CHECK(linMessage2->earlyStopbitOffset == 26000);
    BOOST_CHECK(linMessage2->earlyStopbitOffsetResponse == 26000);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
