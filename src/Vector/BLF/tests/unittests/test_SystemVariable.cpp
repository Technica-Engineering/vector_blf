// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE SystemVariable
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* SYS_VARIABLE = 72 */
BOOST_AUTO_TEST_CASE(SystemVariable_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_SystemVariable.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    auto * obj = dynamic_cast<Vector::BLF::SystemVariable *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* SystemVariable */
    BOOST_CHECK_EQUAL(obj->type, Vector::BLF::SystemVariable::Type::Double);
    BOOST_CHECK_EQUAL(obj->representation, 0x22222222);
    BOOST_CHECK_EQUAL(obj->reservedSystemVariable1, 0x4444444433333333);
    BOOST_CHECK_EQUAL(obj->nameLength, 3);
    BOOST_CHECK_EQUAL(obj->dataLength, 8);
    BOOST_CHECK_EQUAL(obj->reservedSystemVariable2, 0);
    BOOST_CHECK_EQUAL(obj->name, "xyz");
    // BOOST_CHECK_EQUAL(obj->data, )

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    obj = static_cast<Vector::BLF::SystemVariable *>(ohb);
    BOOST_CHECK_EQUAL(obj->type, Vector::BLF::SystemVariable::Type::Long);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    obj = static_cast<Vector::BLF::SystemVariable *>(ohb);
    BOOST_CHECK_EQUAL(obj->type, Vector::BLF::SystemVariable::Type::String);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    obj = static_cast<Vector::BLF::SystemVariable *>(ohb);
    BOOST_CHECK_EQUAL(obj->type, Vector::BLF::SystemVariable::Type::DoubleArray);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    obj = static_cast<Vector::BLF::SystemVariable *>(ohb);
    BOOST_CHECK_EQUAL(obj->type, Vector::BLF::SystemVariable::Type::LongArray);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    obj = static_cast<Vector::BLF::SystemVariable *>(ohb);
    BOOST_CHECK_EQUAL(obj->type, Vector::BLF::SystemVariable::Type::LongLong);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    obj = static_cast<Vector::BLF::SystemVariable *>(ohb);
    BOOST_CHECK_EQUAL(obj->type, Vector::BLF::SystemVariable::Type::ByteArray);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    obj = static_cast<Vector::BLF::SystemVariable *>(ohb);
    BOOST_CHECK_EQUAL(obj->type, Vector::BLF::SystemVariable::Type::ByteArray);

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
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(SystemVariable_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_SystemVariable.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);
    auto * obj = dynamic_cast<Vector::BLF::SystemVariable *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::SYS_VARIABLE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
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

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
