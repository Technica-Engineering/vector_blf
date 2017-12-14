#define BOOST_TEST_MODULE AfdxStatistic
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* AFDX_STATISTIC = 98 */
BOOST_AUTO_TEST_CASE(AfdxStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_AfdxStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_STATISTIC);
    Vector::BLF::AfdxStatistic * obj = static_cast<Vector::BLF::AfdxStatistic *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::AFDX_STATISTIC);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1000763955);

    /* AfdxStatistic */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->flags, 0xb);
    BOOST_CHECK_EQUAL(obj->rxPacketCount, 3);
    BOOST_CHECK_EQUAL(obj->rxByteCount, 417);
    BOOST_CHECK_EQUAL(obj->txPacketCount, 0);
    BOOST_CHECK_EQUAL(obj->txByteCount, 0);
    BOOST_CHECK_EQUAL(obj->collisionCount, 0);
    BOOST_CHECK_EQUAL(obj->errorCount, 0);
    BOOST_CHECK_EQUAL(obj->statDroppedRedundantPacketCount, 0);
    BOOST_CHECK_EQUAL(obj->statRedundantErrorPacketCount, 0);
    BOOST_CHECK_EQUAL(obj->statIntegrityErrorPacketCount, 0);
    BOOST_CHECK_EQUAL(obj->statAvrgPeriodMsec, 0);
    BOOST_CHECK_EQUAL(obj->statAvrgJitterMysec, 0);
    BOOST_CHECK_EQUAL(obj->vlid, 0);
    BOOST_CHECK_EQUAL(obj->statDuration, 0);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR);

    delete ohb;

    file.close();
}
