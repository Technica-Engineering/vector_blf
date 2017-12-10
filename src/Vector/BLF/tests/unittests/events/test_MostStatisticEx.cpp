#define BOOST_TEST_MODULE MostStatisticEx
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_STATISTICEX = 67 */
BOOST_AUTO_TEST_CASE(MostStatisticEx)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostStatisticEx.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostStatisticEx * mostStatisticEx;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_STATISTICEX);
    mostStatisticEx = static_cast<Vector::BLF::MostStatisticEx *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostStatisticEx->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostStatisticEx->headerSize == mostStatisticEx->calculateHeaderSize());
    BOOST_CHECK(mostStatisticEx->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostStatisticEx->objectSize == mostStatisticEx->calculateObjectSize());
    BOOST_CHECK(mostStatisticEx->objectType == Vector::BLF::ObjectType::MOST_STATISTICEX);
    /* ObjectHeader2 */
    BOOST_CHECK(mostStatisticEx->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostStatisticEx->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostStatisticEx->objectVersion == 0);
    BOOST_CHECK(mostStatisticEx->objectTimeStamp == 2024742000); // ns
    BOOST_CHECK(mostStatisticEx->originalTimeStamp == 0);
    /* MostStatisticEx */
    BOOST_CHECK(mostStatisticEx->channel == 2);
    // reserved
    BOOST_CHECK(mostStatisticEx->codingErrors == 0x000006);
    BOOST_CHECK(mostStatisticEx->frameCounter == 0x00A395);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
