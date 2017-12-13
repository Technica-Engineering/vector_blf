#define BOOST_TEST_MODULE DriverOverrun
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* OVERRUN_ERROR = 91 */
BOOST_AUTO_TEST_CASE(DriverOverrun)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_DriverOverrun.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::OVERRUN_ERROR);
    Vector::BLF::DriverOverrun * obj = static_cast<Vector::BLF::DriverOverrun *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::OVERRUN_ERROR);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* CanErrorFrame */
    BOOST_CHECK(obj->busType == Vector::BLF::DriverOverrun::BusType::Can);
    BOOST_CHECK_EQUAL(obj->channel, 0x2222);
    BOOST_CHECK_EQUAL(obj->reserved, 0x3333);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::OVERRUN_ERROR);

    delete ohb;

    file.close();
}
