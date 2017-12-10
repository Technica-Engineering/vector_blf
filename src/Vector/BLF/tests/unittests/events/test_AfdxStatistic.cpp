#define BOOST_TEST_MODULE AfdxStatistic
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* AFDX_STATISTIC = 98 */
BOOST_AUTO_TEST_CASE(AfdxStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_AfdxStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::AfdxStatistic * afdxStatistic;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_STATISTIC);
    afdxStatistic = static_cast<Vector::BLF::AfdxStatistic *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(afdxStatistic->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(afdxStatistic->headerSize == afdxStatistic->calculateHeaderSize());
    BOOST_CHECK(afdxStatistic->headerVersion == 1);
    BOOST_CHECK(afdxStatistic->objectSize == afdxStatistic->calculateObjectSize());
    BOOST_CHECK(afdxStatistic->objectType == Vector::BLF::ObjectType::AFDX_STATISTIC);
    /* ObjectHeader */
    BOOST_CHECK(afdxStatistic->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(afdxStatistic->objectVersion == 0);
    BOOST_CHECK(afdxStatistic->objectTimeStamp == 1000763955); // ns
    /* AfdxStatistic */
    BOOST_CHECK(afdxStatistic->channel == 1);
    BOOST_CHECK(afdxStatistic->flags == 0xb);
    BOOST_CHECK(afdxStatistic->rxPacketCount == 3);
    BOOST_CHECK(afdxStatistic->rxByteCount == 417);
    BOOST_CHECK(afdxStatistic->txPacketCount == 0);
    BOOST_CHECK(afdxStatistic->txByteCount == 0);
    BOOST_CHECK(afdxStatistic->collisionCount == 0);
    BOOST_CHECK(afdxStatistic->errorCount == 0);
    BOOST_CHECK(afdxStatistic->statDroppedRedundantPacketCount == 0);
    BOOST_CHECK(afdxStatistic->statRedundantErrorPacketCount == 0);
    BOOST_CHECK(afdxStatistic->statIntegrityErrorPacketCount == 0);
    BOOST_CHECK(afdxStatistic->statAvrgPeriodMsec == 0);
    BOOST_CHECK(afdxStatistic->statAvrgJitterMysec == 0);
    BOOST_CHECK(afdxStatistic->vlid == 0);
    BOOST_CHECK(afdxStatistic->statDuration == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
