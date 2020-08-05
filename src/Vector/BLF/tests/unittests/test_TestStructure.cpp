#define BOOST_TEST_MODULE TestStructure
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* TEST_STRUCTURE = 118 */
BOOST_AUTO_TEST_CASE(TestStructure) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_TestStructure.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::TEST_STRUCTURE);
    auto * obj = dynamic_cast<Vector::BLF::TestStructure *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::TEST_STRUCTURE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* TestStructure */
    BOOST_CHECK_EQUAL(obj->executionObjectIdentify, 0x11111111);
    BOOST_CHECK_EQUAL(obj->type, static_cast<uint16_t>(Vector::BLF::TestStructure::Type::TM_TESTMODULE));
    BOOST_CHECK_EQUAL(obj->uniqueNo, 0x22222222);
    BOOST_CHECK_EQUAL(obj->action, static_cast<uint16_t>(Vector::BLF::TestStructure::Action::BEGIN));
    BOOST_CHECK_EQUAL(obj->result, static_cast<uint16_t>(Vector::BLF::TestStructure::Result::PASSED));
    BOOST_CHECK_EQUAL(obj->executingObjectNameLength, 3);
    BOOST_CHECK_EQUAL(obj->nameLength, 3);
    BOOST_CHECK_EQUAL(obj->textLength, 3);
    BOOST_CHECK(obj->executingObjectName == u"xyz");
    BOOST_CHECK(obj->name == u"xyz");
    BOOST_CHECK(obj->text == u"xyz");

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::TEST_STRUCTURE);

    delete ohb;

    /* read last */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::Unknown115);

    delete ohb;

    /* read last */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::Unknown115);

    delete ohb;

    /* read eof */
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    file.close();
}
