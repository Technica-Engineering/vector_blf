#define BOOST_TEST_MODULE CanDriverStatistic
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_STATISTIC = 4 */
BOOST_AUTO_TEST_CASE(CanDriverStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanDriverStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanDriverStatistic * canDriverStatistic;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_STATISTIC);
    canDriverStatistic = static_cast<Vector::BLF::CanDriverStatistic *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canDriverStatistic->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canDriverStatistic->headerSize == canDriverStatistic->calculateHeaderSize());
    BOOST_CHECK(canDriverStatistic->headerVersion == 1);
    BOOST_CHECK(canDriverStatistic->objectSize == canDriverStatistic->calculateObjectSize());
    BOOST_CHECK(canDriverStatistic->objectType == Vector::BLF::ObjectType::CAN_STATISTIC);
    /* ObjectHeader */
    BOOST_CHECK(canDriverStatistic->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canDriverStatistic->objectVersion == 0);
    BOOST_CHECK(canDriverStatistic->objectTimeStamp == 1010000000); // ns
    /* CanDriverStatistic */
    BOOST_CHECK(canDriverStatistic->channel == 1);
    BOOST_CHECK(canDriverStatistic->busLoad == 0);
    BOOST_CHECK(canDriverStatistic->standardDataFrames == 1000);
    BOOST_CHECK(canDriverStatistic->extendedDataFrames == 0);
    BOOST_CHECK(canDriverStatistic->standardRemoteFrames == 15);
    BOOST_CHECK(canDriverStatistic->extendedRemoteFrames == 0);
    BOOST_CHECK(canDriverStatistic->errorFrames == 0);
    BOOST_CHECK(canDriverStatistic->overloadFrames == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
