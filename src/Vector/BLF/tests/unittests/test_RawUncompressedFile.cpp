#define BOOST_TEST_MODULE RawUncompressedFile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** Test read operations on a blf file. */
BOOST_AUTO_TEST_CASE(ReadTest) {
    Vector::BLF::RawUncompressedFile rawUncompressedFile;

    /* checks after initialize */
    BOOST_CHECK(!rawUncompressedFile.is_open());
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), -1);
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellp(), -1);
    BOOST_CHECK_EQUAL(rawUncompressedFile.size(), 0);

    /* open file */
    rawUncompressedFile.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK(rawUncompressedFile.is_open());
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 0);
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellp(), 0);
    BOOST_CHECK_EQUAL(rawUncompressedFile.size(), 212);

    /* read some data */
    char signature[5] = { 0, 0, 0, 0, 0 }; // including null termination
    BOOST_CHECK_EQUAL(rawUncompressedFile.read(signature, 4), 4);
    BOOST_CHECK_EQUAL(signature, "LOBJ");
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 4);

    /* rewind to beginning of file */
    rawUncompressedFile.seekg(0, std::ios_base::beg);
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 0);

    /* read data again */
    BOOST_CHECK_EQUAL(rawUncompressedFile.read(signature, 4), 4);
    BOOST_CHECK_EQUAL(signature, "LOBJ");
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 4);

    /* read further on */
    Vector::BLF::WORD headerSize;
    BOOST_CHECK_EQUAL(rawUncompressedFile.read(reinterpret_cast<char *>(&headerSize), sizeof(headerSize)), sizeof(headerSize));
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 6);
    Vector::BLF::WORD headerVersion;
    BOOST_CHECK_EQUAL(rawUncompressedFile.read(reinterpret_cast<char *>(&headerVersion), sizeof(headerVersion)), sizeof(headerVersion));
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 8);
    Vector::BLF::DWORD objectSize;
    BOOST_CHECK_EQUAL(rawUncompressedFile.read(reinterpret_cast<char *>(&objectSize), sizeof(objectSize)), sizeof(objectSize));
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 12);
    Vector::BLF::ObjectType objectType;
    BOOST_CHECK_EQUAL(rawUncompressedFile.read(reinterpret_cast<char *>(&objectType), sizeof(objectType)), sizeof(objectType));
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 16);

    /* close file */
    rawUncompressedFile.close();
    BOOST_CHECK(!rawUncompressedFile.is_open());
}
