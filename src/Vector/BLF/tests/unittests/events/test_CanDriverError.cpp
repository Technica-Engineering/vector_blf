#define BOOST_TEST_MODULE CanDriverError
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_DRIVER_ERROR = 31 */
BOOST_AUTO_TEST_CASE(CanDriverError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanDriverError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR);
    Vector::BLF::CanDriverError * obj = static_cast<Vector::BLF::CanDriverError *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* CanDriverError */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->txErrors, 0x22);
    BOOST_CHECK_EQUAL(obj->rxErrors, 0x33);
    BOOST_CHECK_EQUAL(obj->errorCode, 0x44444444);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR);

    delete ohb;

    file.close();
}
