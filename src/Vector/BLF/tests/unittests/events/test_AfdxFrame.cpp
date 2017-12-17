#define BOOST_TEST_MODULE AfdxFrame
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* AFDX_FRAME = 97 */
BOOST_AUTO_TEST_CASE(AfdxFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_AfdxFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);
    Vector::BLF::AfdxFrame * obj = static_cast<Vector::BLF::AfdxFrame *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::AFDX_FRAME);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* AfdxFrame */
    BOOST_CHECK_EQUAL(obj->sourceAddress[0], 0x11);
    BOOST_CHECK_EQUAL(obj->sourceAddress[1], 0x22);
    BOOST_CHECK_EQUAL(obj->sourceAddress[2], 0x33);
    BOOST_CHECK_EQUAL(obj->sourceAddress[3], 0x44);
    BOOST_CHECK_EQUAL(obj->sourceAddress[4], 0x55);
    BOOST_CHECK_EQUAL(obj->sourceAddress[5], 0x66);
    BOOST_CHECK_EQUAL(obj->channel, 0x7777);
    BOOST_CHECK_EQUAL(obj->destinationAddress[0], 0x88);
    BOOST_CHECK_EQUAL(obj->destinationAddress[1], 0x99);
    BOOST_CHECK_EQUAL(obj->destinationAddress[2], 0xAA);
    BOOST_CHECK_EQUAL(obj->destinationAddress[3], 0xBB);
    BOOST_CHECK_EQUAL(obj->destinationAddress[4], 0xCC);
    BOOST_CHECK_EQUAL(obj->destinationAddress[5], 0xDD);
    BOOST_CHECK_EQUAL(obj->dir, Vector::BLF::AfdxFrame::Dir::Tx);
    BOOST_CHECK_EQUAL(obj->type, 0xEEEE);
    BOOST_CHECK_EQUAL(obj->tpid, 0xFFFF);
    BOOST_CHECK_EQUAL(obj->tci, 0x1111);
    BOOST_CHECK_EQUAL(obj->ethChannel, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedAfdxFrame1, 0);
    BOOST_CHECK_EQUAL(obj->afdxFlags, 0x3333);
    BOOST_CHECK_EQUAL(obj->reservedAfdxFrame2, 0);
    BOOST_CHECK_EQUAL(obj->bagUsec, 0x44444444);
    BOOST_CHECK_EQUAL(obj->payLoadLength, 3);
    BOOST_CHECK_EQUAL(obj->reservedAfdxFrame3, 0);
    BOOST_CHECK_EQUAL(obj->reservedAfdxFrame4, 0);
    BOOST_CHECK_EQUAL(obj->payLoad[0], 5);
    BOOST_CHECK_EQUAL(obj->payLoad[1], 6);
    BOOST_CHECK_EQUAL(obj->payLoad[2], 7);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::AFDX_FRAME);

    delete ohb;

    file.close();
}
