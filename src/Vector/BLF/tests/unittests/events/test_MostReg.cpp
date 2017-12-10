#define BOOST_TEST_MODULE MostReg
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_REG = 35 */
BOOST_AUTO_TEST_CASE(MostReg)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostReg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostReg * mostReg;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_REG);
    mostReg = static_cast<Vector::BLF::MostReg *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostReg->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostReg->headerSize == mostReg->calculateHeaderSize());
    BOOST_CHECK(mostReg->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostReg->objectSize == mostReg->calculateObjectSize());
    BOOST_CHECK(mostReg->objectType == Vector::BLF::ObjectType::MOST_REG);
    /* ObjectHeader2 */
    BOOST_CHECK(mostReg->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostReg->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostReg->objectVersion == 0);
    BOOST_CHECK(mostReg->objectTimeStamp == 9050000000); // ns
    BOOST_CHECK(mostReg->originalTimeStamp == 0);
    /* MostReg */
    BOOST_CHECK(mostReg->channel == 1);
    BOOST_CHECK(mostReg->subType == 0);
    // reserved
    BOOST_CHECK(mostReg->handle == 0);
    BOOST_CHECK(mostReg->offset == 0x0000);
    BOOST_CHECK(mostReg->chip == 1); // OS8104
    BOOST_CHECK(mostReg->regDataLen == 0x10);
    BOOST_CHECK(mostReg->regData[0x00] == 0x00);
    BOOST_CHECK(mostReg->regData[0x01] == 0x01);
    BOOST_CHECK(mostReg->regData[0x02] == 0x02);
    BOOST_CHECK(mostReg->regData[0x03] == 0x03);
    BOOST_CHECK(mostReg->regData[0x04] == 0x04);
    BOOST_CHECK(mostReg->regData[0x05] == 0x05);
    BOOST_CHECK(mostReg->regData[0x06] == 0x06);
    BOOST_CHECK(mostReg->regData[0x07] == 0x07);
    BOOST_CHECK(mostReg->regData[0x08] == 0x08);
    BOOST_CHECK(mostReg->regData[0x09] == 0x09);
    BOOST_CHECK(mostReg->regData[0x0a] == 0x0a);
    BOOST_CHECK(mostReg->regData[0x0b] == 0x0b);
    BOOST_CHECK(mostReg->regData[0x0c] == 0x0c);
    BOOST_CHECK(mostReg->regData[0x0d] == 0x0d);
    BOOST_CHECK(mostReg->regData[0x0e] == 0x0e);
    BOOST_CHECK(mostReg->regData[0x0f] == 0x0f);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
