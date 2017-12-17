#define BOOST_TEST_MODULE EnvironmentVariable
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* ENV_INTEGER = 6 */
/* ENV_DOUBLE = 7 */
/* ENV_STRING = 8 */
/* ENV_DATA = 9 */
BOOST_AUTO_TEST_CASE(EnvironmentVariable)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_EnvironmentVariable.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ENV_INTEGER);
    Vector::BLF::EnvironmentVariable * obj = static_cast<Vector::BLF::EnvironmentVariable *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::ENV_INTEGER);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 30613377); // ns

    /* EnvironmentVariable */
    BOOST_CHECK_EQUAL(obj->nameLength, 11);
    BOOST_CHECK_EQUAL(obj->dataLength, 4);
    // reserved
    BOOST_CHECK_EQUAL(obj->name, "EnvGearDown");
    BOOST_CHECK_EQUAL(obj->data[0], 0x01);
    BOOST_CHECK_EQUAL(obj->data[1], 0x00);
    BOOST_CHECK_EQUAL(obj->data[2], 0x00);
    BOOST_CHECK_EQUAL(obj->data[3], 0x00);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ENV_INTEGER);

    delete ohb;

    file.close();
}
