#define BOOST_TEST_MODULE MostStatistic
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_STATISTIC = 25 */
BOOST_AUTO_TEST_CASE(MostStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostStatistic * mostStatistic;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_STATISTIC);
    mostStatistic = static_cast<Vector::BLF::MostStatistic *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostStatistic->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostStatistic->headerSize == mostStatistic->calculateHeaderSize());
    BOOST_CHECK(mostStatistic->headerVersion == 1);
    BOOST_CHECK(mostStatistic->objectSize == mostStatistic->calculateObjectSize());
    BOOST_CHECK(mostStatistic->objectType == Vector::BLF::ObjectType::MOST_STATISTIC);
    /* ObjectHeader */
    BOOST_CHECK(mostStatistic->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(mostStatistic->objectVersion == 0);
    BOOST_CHECK(mostStatistic->objectTimeStamp == 2030000000); // ns
    /* MostStatistic */
    BOOST_CHECK(mostStatistic->channel == 1);
    BOOST_CHECK(mostStatistic->pktCnt == 0);
    BOOST_CHECK(mostStatistic->frmCnt == 0);
    BOOST_CHECK(mostStatistic->lightCnt == 4);
    BOOST_CHECK(mostStatistic->bufferLevel == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
