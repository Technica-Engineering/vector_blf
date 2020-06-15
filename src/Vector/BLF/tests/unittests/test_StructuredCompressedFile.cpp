#define BOOST_TEST_MODULE StructuredCompressedFile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

BOOST_AUTO_TEST_CASE(ReadTest) {
    Vector::BLF::RawCompressedFile rawCompressedFile;
    Vector::BLF::StructuredCompressedFile structuredCompressedFile(rawCompressedFile);

    /* checks after initialize */
    BOOST_CHECK(!structuredCompressedFile.is_open());
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 0); // @todo should be -1
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 0); // @todo should be -1

    /* open file */
    structuredCompressedFile.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK(structuredCompressedFile.is_open());
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 0);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 0);

    /* read log container 0/2 */
    Vector::BLF::LogContainer * logContainer = structuredCompressedFile.read();
    BOOST_CHECK(logContainer);
    BOOST_CHECK(structuredCompressedFile.is_open());
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 1);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 0);
    delete logContainer;

    /* read log container 1/2 */
    logContainer = structuredCompressedFile.read();
    BOOST_CHECK(logContainer);
    BOOST_CHECK(structuredCompressedFile.is_open());
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 2);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 0);
    delete logContainer;

    /* read log container 2/2 */
    logContainer = structuredCompressedFile.read();
    BOOST_CHECK(!logContainer);
    BOOST_CHECK(structuredCompressedFile.is_open());
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 2);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 0);
    delete logContainer;

    /* rewind to beginning of file */
    structuredCompressedFile.seekg(0, std::ios_base::beg);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 0);

    /* close file */
    structuredCompressedFile.close();
    BOOST_CHECK(!structuredCompressedFile.is_open());
}
