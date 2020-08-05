#define BOOST_TEST_MODULE File
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** Open and index file */
BOOST_AUTO_TEST_CASE(Test1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK_GT(file.tellg(), 0);

    file.seekg(0);
    Vector::BLF::FileStatistics fileStatistics;
    std::vector<uint8_t> data1(fileStatistics.statisticsSize);
    file.read(data1.data(), data1.size());
    fileStatistics.fromData(data1.begin());
    BOOST_CHECK_EQUAL(fileStatistics.signature, Vector::BLF::FileSignature);
    BOOST_CHECK_EQUAL(file.tellg(), fileStatistics.statisticsSize);

    Vector::BLF::CanMessage canMessage;
    std::vector<uint8_t> data2(96); // 96 is the known size of the object
    BOOST_CHECK_EQUAL(file.read(data2.data(), data2.size()), 96);
    canMessage.fromData(data2.begin());
    BOOST_CHECK_EQUAL(canMessage.signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(canMessage.objectSize, canMessage.calculateObjectSize());
    BOOST_CHECK(canMessage.objectType == Vector::BLF::ObjectType::CAN_MESSAGE);

    file.close();
}

/** check error conditions in open */
BOOST_AUTO_TEST_CASE(OpenErrors) {
    Vector::BLF::File file;

    /* try to open an unexisting file for reading */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/FileNotExists.blf", std::ios_base::in);
    BOOST_CHECK(!file.is_open());
    file.close();

    /* try to open an uncreatable file for writing */
    file.open(CMAKE_CURRENT_BINARY_DIR "/events_from_binlog/DirNotExists/File.blf", std::ios_base::out);
    BOOST_CHECK(!file.is_open());
    file.close();

    /* open an existing file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK(file.is_open());

    /* open it again */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK(file.is_open());
    file.close();
}

/** try to create objects that are not triggered anyway by other test cases */
BOOST_AUTO_TEST_CASE(createUnknownObjects) {
    /* doesn't exist */
    BOOST_CHECK(Vector::BLF::makeObject(Vector::BLF::ObjectType::UNKNOWN) == nullptr);
    BOOST_CHECK(Vector::BLF::makeObject(Vector::BLF::ObjectType::Reserved26) == nullptr);
    BOOST_CHECK(Vector::BLF::makeObject(Vector::BLF::ObjectType::Reserved27) == nullptr);
    BOOST_CHECK(Vector::BLF::makeObject(Vector::BLF::ObjectType::Reserved28) == nullptr);
    BOOST_CHECK(Vector::BLF::makeObject(Vector::BLF::ObjectType::Reserved52) == nullptr);
    BOOST_CHECK(Vector::BLF::makeObject(Vector::BLF::ObjectType::Reserved53) == nullptr);
    BOOST_CHECK(Vector::BLF::makeObject(Vector::BLF::ObjectType::Reserved108) == nullptr);
    BOOST_CHECK(Vector::BLF::makeObject(Vector::BLF::ObjectType::Reserved116) == nullptr);
    BOOST_CHECK(Vector::BLF::makeObject(Vector::BLF::ObjectType::Reserved117) == nullptr);

    /* this should exist */
    Vector::BLF::ObjectHeaderBase * ohb;
    ohb = Vector::BLF::makeObject(Vector::BLF::ObjectType::LOG_CONTAINER);
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

    /* CanMessage */
    Vector::BLF::ObjectHeaderBase * ohb;
    ohb = file.read();
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    delete ohb;

    /* CanMessage */
    ohb = file.read();
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    delete ohb;

    /* No CanMessage */
    ohb = file.read();
    BOOST_CHECK(ohb == nullptr);

    file.close();
}

/** Test file without two CanMessages in a truncated compressed LogContainer (-8 Bytes). */
BOOST_AUTO_TEST_CASE(fileWithTruncatedCompressedLogContainer) {
    Vector::BLF::File file;
    BOOST_REQUIRE_THROW(file.open(CMAKE_CURRENT_SOURCE_DIR "/errors/FileWithTruncatedCompressedLogContainer.blf", std::ios_base::in), Vector::BLF::Exception);
}

/** Test file with two CanMessages, in a truncated uncompressed LogContainer (-8 Bytes). */
BOOST_AUTO_TEST_CASE(fileWithTruncatedUncompressedLogContainer) {
    Vector::BLF::File file;
    BOOST_REQUIRE_THROW(file.open(CMAKE_CURRENT_SOURCE_DIR "/errors/FileWithTruncatedUncompressedLogContainer.blf", std::ios_base::in), Vector::BLF::Exception);
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
    delete ohb;

    /* second CanMessage is truncated */
    ohb = file.read();
    BOOST_CHECK(ohb == nullptr);
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
    delete ohb;

    /* second CanMessage has objectType set to 0xA0 */
    ohb = file.read();
    BOOST_CHECK(ohb == nullptr);
    delete ohb;

    file.close();
}
