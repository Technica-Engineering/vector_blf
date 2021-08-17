// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE File
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** check error conditions in open */
BOOST_AUTO_TEST_CASE(OpenErrors) {
    Vector::BLF::File file;

    /* try to open an unexisting file for reading */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/FileNotExists.blf", std::ios_base::in);
    BOOST_CHECK(!file.is_open());

    /* try to open an uncreatable file for writing */
    file.open(CMAKE_CURRENT_BINARY_DIR "/events_from_binlog/DirNotExists/File.blf", std::ios_base::out);
    BOOST_CHECK(!file.is_open());

    /* open an existing file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK(file.is_open());

    /* open it again */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK(file.is_open());
}

/** try to create objects that are not triggered anyway by other test cases */
BOOST_AUTO_TEST_CASE(createUnknownObjects) {
    /* doesn't exist */
    BOOST_CHECK(Vector::BLF::File::createObject(Vector::BLF::ObjectType::UNKNOWN) == nullptr);
    BOOST_CHECK(Vector::BLF::File::createObject(Vector::BLF::ObjectType::Reserved26) == nullptr);
    BOOST_CHECK(Vector::BLF::File::createObject(Vector::BLF::ObjectType::Reserved27) == nullptr);
    BOOST_CHECK(Vector::BLF::File::createObject(Vector::BLF::ObjectType::Reserved28) == nullptr);
    BOOST_CHECK(Vector::BLF::File::createObject(Vector::BLF::ObjectType::Reserved52) == nullptr);
    BOOST_CHECK(Vector::BLF::File::createObject(Vector::BLF::ObjectType::Reserved53) == nullptr);
    BOOST_CHECK(Vector::BLF::File::createObject(Vector::BLF::ObjectType::Reserved108) == nullptr);
    BOOST_CHECK(Vector::BLF::File::createObject(Vector::BLF::ObjectType::Reserved116) == nullptr);
    BOOST_CHECK(Vector::BLF::File::createObject(Vector::BLF::ObjectType::Reserved117) == nullptr);

    /* this should exist */
    Vector::BLF::ObjectHeaderBase * ohb;
    ohb = Vector::BLF::File::createObject(Vector::BLF::ObjectType::LOG_CONTAINER);
    BOOST_REQUIRE(ohb);
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::LOG_CONTAINER);
    delete ohb;
}

/** test getter/setter for defaultContainerSize */
BOOST_AUTO_TEST_CASE(defaultContainerSize) {
    Vector::BLF::File file;

    BOOST_CHECK_EQUAL(file.defaultLogContainerSize(), 0x20000);
    file.setDefaultLogContainerSize(0x30000);
    BOOST_CHECK_EQUAL(file.defaultLogContainerSize(), 0x30000);
}

/** Test file with only two CanMessages, but no LogContainers. */
BOOST_AUTO_TEST_CASE(fileWithoutLogContainers) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/errors/FileWithoutLogContainers.blf", std::ios_base::in);
    BOOST_REQUIRE(file.is_open());

    /* No LogContainer */
    Vector::BLF::ObjectHeaderBase * ohb;
    ohb = file.read();
    BOOST_CHECK(ohb == nullptr);
    BOOST_CHECK(!file.good());
    delete ohb;

    file.close();
}

/** Test file without two CanMessages in a truncated compressed LogContainer (-8 Bytes). */
BOOST_AUTO_TEST_CASE(fileWithTruncatedCompressedLogContainer) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/errors/FileWithTruncatedCompressedLogContainer.blf", std::ios_base::in);
    BOOST_REQUIRE(file.is_open());

    /* LogContainer is truncated */
    Vector::BLF::ObjectHeaderBase * ohb;
    ohb = file.read();
    BOOST_CHECK(ohb == nullptr);
    BOOST_CHECK(!file.good());
    delete ohb;

    file.close();
}

/** Test file with two CanMessages, in a truncated uncompressed LogContainer (-8 Bytes). */
BOOST_AUTO_TEST_CASE(fileWithTruncatedUncompressedLogContainer) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/errors/FileWithTruncatedUncompressedLogContainer.blf", std::ios_base::in);
    BOOST_REQUIRE(file.is_open());

    /* LogContainer is truncated */
    Vector::BLF::ObjectHeaderBase * ohb;
    ohb = file.read();
    BOOST_CHECK(ohb == nullptr);
    BOOST_CHECK(!file.good());
    delete ohb;

    file.close();
}

/** Test file without two CanMessages, second is truncated (-8 Bytes). */
BOOST_AUTO_TEST_CASE(fileWithTruncatedCanMessage) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/errors/FileWithTruncatedCanMessage.blf", std::ios_base::in);
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;

    /* first CanMessage is ok */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    BOOST_CHECK(file.good());
    delete ohb;

    /* second CanMessage is truncated */
    ohb = file.read();
    BOOST_CHECK(ohb == nullptr);
    BOOST_CHECK(!file.good());
    delete ohb;

    file.close();
}

/** Test file without two CanMessage, where second has objectType set to 0xA0. */
BOOST_AUTO_TEST_CASE(fileWithUnknownObjectType) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/errors/FileWithUnknownObjectType.blf", std::ios_base::in);
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;

    /* first CanMessage is ok */
    ohb = file.read();
    BOOST_REQUIRE(ohb);
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    BOOST_CHECK(file.good());
    delete ohb;

    /* second CanMessage has objectType set to 0xA0 */
    ohb = file.read();
    BOOST_CHECK(ohb == nullptr);
    BOOST_CHECK(!file.good());
    delete ohb;

    file.close();
}

/** Test open and close cycle to see if there is nothing freed forcefully. */
BOOST_AUTO_TEST_CASE(OpenCloseCycles) {
    Vector::BLF::File logfile;

    logfile.open(CMAKE_CURRENT_BINARY_DIR "test.blf", std::ios_base::out);
    logfile.close();
}
