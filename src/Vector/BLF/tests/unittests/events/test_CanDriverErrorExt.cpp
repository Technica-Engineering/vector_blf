#define BOOST_TEST_MODULE CanDriverErrorExt
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_DRIVER_ERROR_EXT = 74 */
BOOST_AUTO_TEST_CASE(CanDriverErrorExt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanDriverErrorExt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT);
    Vector::BLF::CanDriverErrorExt * obj = static_cast<Vector::BLF::CanDriverErrorExt *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* CanMessage */
    BOOST_CHECK_EQUAL(obj->channel,0x1111);
    BOOST_CHECK_EQUAL(obj->txErrors, 0x22);
    BOOST_CHECK_EQUAL(obj->rxErrors, 0x33);
    BOOST_CHECK_EQUAL(obj->errorCode, 0x44444444);
    BOOST_CHECK_EQUAL(obj->flags, 0x55555555);
    BOOST_CHECK_EQUAL(obj->state, 0x66);
    BOOST_CHECK_EQUAL(obj->reserved1, 0x77);
    BOOST_CHECK_EQUAL(obj->reserved2, 0x8888);
    BOOST_CHECK_EQUAL(obj->reserved3[0], 0x99999999);
    BOOST_CHECK_EQUAL(obj->reserved3[1], 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->reserved3[2], 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->reserved3[3], 0xCCCCCCCC);

    delete obj;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT);

    delete obj;

    file.close();
}
