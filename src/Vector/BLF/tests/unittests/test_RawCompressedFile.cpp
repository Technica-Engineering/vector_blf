#define BOOST_TEST_MODULE RawCompressedFile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** Test read operations on a blf file. */
BOOST_AUTO_TEST_CASE(ReadTest) {
    Vector::BLF::RawCompressedFile rawCompressedFile;

    /* checks after initialize */
    BOOST_CHECK_EQUAL(rawCompressedFile.gcount(), 0);
    BOOST_CHECK_EQUAL(rawCompressedFile.tellg(), -1);
    BOOST_CHECK_EQUAL(rawCompressedFile.tellp(), -1);
    BOOST_CHECK(!rawCompressedFile.eof());
    BOOST_CHECK(!rawCompressedFile.is_open());

    /* open file */
    rawCompressedFile.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK_EQUAL(rawCompressedFile.tellg(), 0);
    BOOST_CHECK(rawCompressedFile.is_open());

    /* read some data */
    char signature[5] = { 0, 0, 0, 0, 0 }; // including null termination
    rawCompressedFile.read(signature, 4);
    BOOST_CHECK_EQUAL(signature, "LOGG");
    BOOST_CHECK_EQUAL(rawCompressedFile.tellg(), 4);
    BOOST_CHECK_EQUAL(rawCompressedFile.gcount(), 4);

    /* rewind to beginning of file */
    rawCompressedFile.seekg(0, std::ios_base::beg);
    BOOST_CHECK_EQUAL(rawCompressedFile.tellg(), 0);
    rawCompressedFile.seekp(0);
    BOOST_CHECK_EQUAL(rawCompressedFile.tellp(), 0);

    /* close file */
    rawCompressedFile.close();
    BOOST_CHECK(!rawCompressedFile.is_open());
}
