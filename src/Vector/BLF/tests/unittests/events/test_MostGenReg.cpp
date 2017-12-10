#define BOOST_TEST_MODULE MostGenReg
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_GENREG = 36 */
BOOST_AUTO_TEST_CASE(MostGenReg)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostGenReg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostGenReg * mostGenReg;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_GENREG);
    mostGenReg = static_cast<Vector::BLF::MostGenReg *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostGenReg->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostGenReg->headerSize == mostGenReg->calculateHeaderSize());
    BOOST_CHECK(mostGenReg->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostGenReg->objectSize == mostGenReg->calculateObjectSize());
    BOOST_CHECK(mostGenReg->objectType == Vector::BLF::ObjectType::MOST_GENREG);
    /* ObjectHeader2 */
    BOOST_CHECK(mostGenReg->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostGenReg->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostGenReg->objectVersion == 0);
    BOOST_CHECK(mostGenReg->objectTimeStamp == 1471300000); // ns
    BOOST_CHECK(mostGenReg->originalTimeStamp == 0);
    /* MostGenReg */
    BOOST_CHECK(mostGenReg->channel == 1);
    BOOST_CHECK(mostGenReg->subType == 1);
    // reserved
    BOOST_CHECK(mostGenReg->handle == 0);
    BOOST_CHECK(mostGenReg->regId == 0x8A);
    // reserved
    BOOST_CHECK(mostGenReg->regValue == 0x0172);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
