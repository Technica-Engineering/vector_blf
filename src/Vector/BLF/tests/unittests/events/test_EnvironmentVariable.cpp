#define BOOST_TEST_MODULE EnvironmentVariable
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* ENV_INTEGER = 6 */
/* ENV_DOUBLE = 7 */
/* ENV_STRING = 8 */
/* ENV_DATA = 9 */
BOOST_AUTO_TEST_CASE(EnvironmentVariable)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_EnvironmentVariable.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EnvironmentVariable * environmentVariable;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::ENV_INTEGER);
    environmentVariable = static_cast<Vector::BLF::EnvironmentVariable *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(environmentVariable->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(environmentVariable->headerSize == environmentVariable->calculateHeaderSize());
    BOOST_CHECK(environmentVariable->headerVersion == 1);
    BOOST_CHECK(environmentVariable->objectSize == environmentVariable->calculateObjectSize());
    BOOST_CHECK(environmentVariable->objectType == Vector::BLF::ObjectType::ENV_INTEGER);
    /* ObjectHeader */
    BOOST_CHECK(environmentVariable->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(environmentVariable->objectVersion == 0);
    BOOST_CHECK(environmentVariable->objectTimeStamp == 30613377); // ns
    /* EnvironmentVariable */
    BOOST_CHECK(environmentVariable->nameLength == 11);
    BOOST_CHECK(environmentVariable->dataLength == 4);
    // reserved
    BOOST_CHECK(environmentVariable->name == "EnvGearDown");
    BOOST_CHECK(environmentVariable->data[0] == 0x01);
    BOOST_CHECK(environmentVariable->data[1] == 0x00);
    BOOST_CHECK(environmentVariable->data[2] == 0x00);
    BOOST_CHECK(environmentVariable->data[3] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
