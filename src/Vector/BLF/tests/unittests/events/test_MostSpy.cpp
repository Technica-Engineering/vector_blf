#define BOOST_TEST_MODULE MostSpy
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_SPY = 22 */
BOOST_AUTO_TEST_CASE(MostSpy)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostSpy.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_SPY);
    Vector::BLF::MostSpy * obj = static_cast<Vector::BLF::MostSpy *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_SPY);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* MostSpy */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->dir, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedMostSpy1, 0x33);
    BOOST_CHECK_EQUAL(obj->sourceAdr, 0x44444444);
    BOOST_CHECK_EQUAL(obj->destAdr, 0x55555555);
    for (uint8_t i = 0; i < 17; i++) {
        BOOST_CHECK_EQUAL(obj->msg[i], i);
    }
    BOOST_CHECK_EQUAL(obj->reservedMostSpy2, 0x66);
    BOOST_CHECK_EQUAL(obj->rTyp, 0x7777);
    BOOST_CHECK_EQUAL(obj->rTypAdr, 0x88);
    BOOST_CHECK_EQUAL(obj->state, 0x99);
    BOOST_CHECK_EQUAL(obj->reservedMostSpy3, 0xAA);
    BOOST_CHECK_EQUAL(obj->ackNack, 0xBB);
    BOOST_CHECK_EQUAL(obj->crc, 0xCCCCCCCC);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_SPY);

    delete ohb;

    file.close();
}
