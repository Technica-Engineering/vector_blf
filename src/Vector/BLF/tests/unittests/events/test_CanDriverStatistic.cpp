#define BOOST_TEST_MODULE CanDriverStatistic
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_STATISTIC = 4 */
BOOST_AUTO_TEST_CASE(CanDriverStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanDriverStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_STATISTIC);
    Vector::BLF::CanDriverStatistic * obj = static_cast<Vector::BLF::CanDriverStatistic *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_STATISTIC);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1010000000); // ns

    /* CanDriverStatistic */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->busLoad, 0);
    BOOST_CHECK_EQUAL(obj->standardDataFrames, 1000);
    BOOST_CHECK_EQUAL(obj->extendedDataFrames, 0);
    BOOST_CHECK_EQUAL(obj->standardRemoteFrames, 15);
    BOOST_CHECK_EQUAL(obj->extendedRemoteFrames, 0);
    BOOST_CHECK_EQUAL(obj->errorFrames, 0);
    BOOST_CHECK_EQUAL(obj->overloadFrames, 0);
    // reserved

    delete obj;

    file.close();
}
