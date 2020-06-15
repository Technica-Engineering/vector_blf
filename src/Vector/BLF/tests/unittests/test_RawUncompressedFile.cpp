#define BOOST_TEST_MODULE RawUncompressedFile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** Test read operations on a blf file. */
BOOST_AUTO_TEST_CASE(ReadTest) {
    Vector::BLF::RawCompressedFile rawCompressedFile;
    Vector::BLF::StructuredCompressedFile structuredCompressedFile(rawCompressedFile);
    Vector::BLF::RawUncompressedFile rawUncompressedFile(structuredCompressedFile);

    /* checks after initialize */
    BOOST_CHECK(!rawUncompressedFile.is_open());
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 0); // @todo should be -1
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellp(), 0); // @todo should be -1

    /* open file */
    rawUncompressedFile.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK(rawUncompressedFile.is_open());
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 0);
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellp(), 0);

    /* read some data */
    char signature[5] = { 0, 0, 0, 0, 0 }; // including null termination
    BOOST_CHECK_EQUAL(rawUncompressedFile.read(signature, 4), 4);
    BOOST_CHECK_EQUAL(signature, "LOBJ");
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 4);

    /* rewind to beginning of file */
    rawUncompressedFile.seekg(0, std::ios_base::beg);
    BOOST_CHECK_EQUAL(rawUncompressedFile.tellg(), 0);

    /* close file */
    rawUncompressedFile.close();
    BOOST_CHECK(!rawUncompressedFile.is_open());
}
