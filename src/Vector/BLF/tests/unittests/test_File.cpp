#define BOOST_TEST_MODULE File
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** Open file (includes indexing) and do some simple read/seekg tests. */
BOOST_AUTO_TEST_CASE(Test1) {
    /* open file */
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK_EQUAL(file.tellg(), 0x90); // as FileStatistics was read already
    BOOST_CHECK_EQUAL(file.tellp(), 0); // file opened for reading, not writing
    BOOST_CHECK_EQUAL(file.compressedSize(), 420);
    BOOST_CHECK_EQUAL(file.uncompressedSize(), 356);
    BOOST_CHECK_EQUAL(file.uncompressedStatisticsSize(), 420);
    BOOST_CHECK_EQUAL(file.objectCount(), 0); // increased on writing

    /* test file statistics */
    file.seekg(0);
    Vector::BLF::FileStatistics fileStatistics;
    std::vector<uint8_t> data1(fileStatistics.statisticsSize);
    file.read(data1.data(), data1.size());
    fileStatistics.fromData(data1.begin());
    BOOST_CHECK_EQUAL(fileStatistics.signature, Vector::BLF::FileSignature);
    BOOST_CHECK_EQUAL(fileStatistics.statisticsSize, 0x90);
    BOOST_CHECK_EQUAL(fileStatistics.applicationId, 0xd4);
    BOOST_CHECK_EQUAL(fileStatistics.applicationMajor, 0x1a);
    BOOST_CHECK_EQUAL(fileStatistics.applicationMinor, 0x3e);
    BOOST_CHECK_EQUAL(fileStatistics.applicationBuild, 0);
    BOOST_CHECK_EQUAL(fileStatistics.apiMajor, 0);
    BOOST_CHECK_EQUAL(fileStatistics.apiMinor, 0);
    BOOST_CHECK_EQUAL(fileStatistics.apiBuild, 0);
    BOOST_CHECK_EQUAL(fileStatistics.apiPatch, 0);
    BOOST_CHECK_EQUAL(fileStatistics.fileSize, 420);
    BOOST_CHECK_EQUAL(fileStatistics.uncompressedFileSize, 420);
    BOOST_CHECK_EQUAL(fileStatistics.objectCount, 2);
    BOOST_CHECK_EQUAL(fileStatistics.objectsRead, 0);
    //BOOST_CHECK_EQUAL(fileStatistics.measurementStartTime, 0);
    //BOOST_CHECK_EQUAL(fileStatistics.lastObjectTime, 0);
    BOOST_CHECK_EQUAL(fileStatistics.fileSizeWithoutUnknown115, 272);
    //BOOST_CHECK_EQUAL(fileStatistics.reservedFileStatistics, 0);
    BOOST_CHECK_EQUAL(file.tellg(), fileStatistics.statisticsSize);

    /* test reading an object */
    Vector::BLF::CanMessage canMessage;
    std::vector<uint8_t> data2(96); // 96 is the known size of the object
    BOOST_CHECK_EQUAL(file.read(data2.data(), data2.size()), 96);
    canMessage.fromData(data2.begin());
    BOOST_CHECK_EQUAL(canMessage.signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(canMessage.objectSize, canMessage.calculateObjectSize());
    BOOST_CHECK(canMessage.objectType == Vector::BLF::ObjectType::CAN_MESSAGE);

    /* seek to end */
    file.seekg(0, std::ios_base::end);
    BOOST_CHECK_EQUAL(file.tellg(), 356);

    /* seek to begin */
    file.seekg(0, std::ios_base::beg);
    BOOST_CHECK_EQUAL(file.tellg(), 0);

    /* read raw data */
    char signature[5] = { 0, 0, 0, 0, 0 }; // including null termination
    BOOST_CHECK_EQUAL(file.read(reinterpret_cast<uint8_t *>(&signature), 4), 4);
    BOOST_CHECK_EQUAL(signature, "LOGG");
    BOOST_CHECK_EQUAL(file.tellg(), 4);

    /* rewind to beginning of file */
    file.seekg(0);
    BOOST_CHECK_EQUAL(file.tellg(), 0);

    /* write nullptr shouldn't do anything */
    file.write(nullptr);

    /* close file */
    file.close();
    BOOST_CHECK(!file.is_open());
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

/** test getters/setters */
BOOST_AUTO_TEST_CASE(getterSetter) {
    Vector::BLF::File file;

    /* default log container size */
    BOOST_CHECK_EQUAL(file.defaultLogContainerSize(), 0x20000); // default
    file.setDefaultLogContainerSize(0x30000);
    BOOST_CHECK_EQUAL(file.defaultLogContainerSize(), 0x30000);

    /* compression method */
    BOOST_CHECK_EQUAL(file.compressionMethod(), 2); // default (zlib)
    file.setCompressionMethod(0); // no compression
    BOOST_CHECK_EQUAL(file.compressionMethod(), 0);

    /* compression level */
    BOOST_CHECK_EQUAL(file.compressionLevel(), 6); // default
    file.setCompressionLevel(9); // 9 = Z_BEST_COMPRESSION, in case of zlib
    BOOST_CHECK_EQUAL(file.compressionLevel(), 9);
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

    /* No further messages */
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
