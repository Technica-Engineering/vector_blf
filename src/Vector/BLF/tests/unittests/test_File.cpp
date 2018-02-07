#define BOOST_TEST_MODULE File
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** check error conditions in open */
BOOST_AUTO_TEST_CASE(OpenErrors)
{
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
BOOST_AUTO_TEST_CASE(createUnknownObjects)
{
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
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::LOG_CONTAINER);
}
