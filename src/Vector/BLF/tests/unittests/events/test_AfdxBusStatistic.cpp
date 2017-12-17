#define BOOST_TEST_MODULE AfdxBusStatistic
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* AFDX_BUS_STATISTIC = 107 */
BOOST_AUTO_TEST_CASE(AfdxBusStatistic)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_AfdxBusStatistic.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_BUS_STATISTIC);
    Vector::BLF::AfdxBusStatistic * obj = static_cast<Vector::BLF::AfdxBusStatistic *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::AFDX_BUS_STATISTIC);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* AfdxBusStatistic */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->flags, 0x2222);
    BOOST_CHECK_EQUAL(obj->statDuration, 0x33333333);
    BOOST_CHECK_EQUAL(obj->statRxPacketCountHW, 0x44444444);
    BOOST_CHECK_EQUAL(obj->statTxPacketCountHW, 0x55555555);
    BOOST_CHECK_EQUAL(obj->statRxErrorCountHW, 0x66666666);
    BOOST_CHECK_EQUAL(obj->statTxErrorCountHW, 0x77777777);
    BOOST_CHECK_EQUAL(obj->statRxBytesHW, 0x88888888);
    BOOST_CHECK_EQUAL(obj->statTxBytesHW, 0x99999999);
    BOOST_CHECK_EQUAL(obj->statRxPacketCount, 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->statTxPacketCount, 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->statDroppedPacketCount, 0xCCCCCCCC);
    BOOST_CHECK_EQUAL(obj->statInvalidPacketCount, 0xDDDDDDDD);
    BOOST_CHECK_EQUAL(obj->statLostPacketCount, 0xEEEEEEEE);
    BOOST_CHECK_EQUAL(obj->line, 0xFF);
    BOOST_CHECK_EQUAL(obj->linkStatus, 0x11);
    BOOST_CHECK_EQUAL(obj->linkSpeed, 0x2222);
    BOOST_CHECK_EQUAL(obj->linkLost, 0x3333);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_BUS_STATISTIC);

    delete ohb;

    file.close();
}
