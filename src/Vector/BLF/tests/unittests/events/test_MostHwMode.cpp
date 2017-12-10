#define BOOST_TEST_MODULE MostHwMode
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_HWMODE = 34 */
BOOST_AUTO_TEST_CASE(MostHwMode)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostHwMode.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostHwMode * mostHwMode;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_HWMODE);
    mostHwMode = static_cast<Vector::BLF::MostHwMode *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostHwMode->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostHwMode->headerSize == mostHwMode->calculateHeaderSize());
    BOOST_CHECK(mostHwMode->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostHwMode->objectSize == mostHwMode->calculateObjectSize());
    BOOST_CHECK(mostHwMode->objectType == Vector::BLF::ObjectType::MOST_HWMODE);
    /* ObjectHeader2 */
    BOOST_CHECK(mostHwMode->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostHwMode->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostHwMode->objectVersion == 0);
    BOOST_CHECK(mostHwMode->objectTimeStamp == 3560000000); // ns
    BOOST_CHECK(mostHwMode->originalTimeStamp == 0);
    /* MostHwMode */
    BOOST_CHECK(mostHwMode->channel == 1);
    // reserved
    BOOST_CHECK(mostHwMode->hwMode == 0x01); // active
    BOOST_CHECK(mostHwMode->hwModeMask == 0x01); // ByPass
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
