#define BOOST_TEST_MODULE SystemVariable
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* SYS_VARIABLE = 72 */
BOOST_AUTO_TEST_CASE(SystemVariable)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_SystemVariable.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::SystemVariable * systemVariable;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    systemVariable = static_cast<Vector::BLF::SystemVariable *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(systemVariable->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(systemVariable->headerSize == systemVariable->calculateHeaderSize());
    BOOST_CHECK(systemVariable->headerVersion == 1);
    BOOST_CHECK(systemVariable->objectSize == systemVariable->calculateObjectSize());
    BOOST_CHECK(systemVariable->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    /* ObjectHeader */
    BOOST_CHECK(systemVariable->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(systemVariable->objectVersion == 0);
    BOOST_CHECK(systemVariable->objectTimeStamp == 20400000000); // ns
    /* SystemVariable */
    BOOST_CHECK(systemVariable->type == Vector::BLF::SystemVariable::Type::Long);
    // reserved
    BOOST_CHECK(systemVariable->nameLength == 21);
    BOOST_CHECK(systemVariable->dataLength == 4);
    // reserved
    BOOST_CHECK(systemVariable->name == "::WiperSystem::Active");
    BOOST_CHECK(systemVariable->data[0] == 0x06);
    BOOST_CHECK(systemVariable->data[1] == 0x00);
    BOOST_CHECK(systemVariable->data[2] == 0x00);
    BOOST_CHECK(systemVariable->data[3] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
