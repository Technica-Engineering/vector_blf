#define BOOST_TEST_MODULE SystemVariable
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* SYS_VARIABLE = 72 */
BOOST_AUTO_TEST_CASE(SystemVariable)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_SystemVariable.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    Vector::BLF::SystemVariable * obj = static_cast<Vector::BLF::SystemVariable *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 20400000000); // ns

    /* SystemVariable */
    BOOST_CHECK_EQUAL(obj->type, Vector::BLF::SystemVariable::Type::Long);
    // reserved
    BOOST_CHECK_EQUAL(obj->nameLength, 21);
    BOOST_CHECK_EQUAL(obj->dataLength, 4);
    // reserved
    BOOST_CHECK_EQUAL(obj->name, "::WiperSystem::Active");
    BOOST_CHECK_EQUAL(obj->data[0], 0x06);
    BOOST_CHECK_EQUAL(obj->data[1], 0x00);
    BOOST_CHECK_EQUAL(obj->data[2], 0x00);
    BOOST_CHECK_EQUAL(obj->data[3], 0x00);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);

    delete ohb;

    file.close();
}
