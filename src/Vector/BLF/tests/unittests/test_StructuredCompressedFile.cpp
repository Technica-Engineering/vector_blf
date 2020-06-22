#define BOOST_TEST_MODULE StructuredCompressedFile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

BOOST_AUTO_TEST_CASE(ReadTest) {
    Vector::BLF::StructuredCompressedFile structuredCompressedFile;

    /* checks after initialize */
    BOOST_CHECK(!structuredCompressedFile.is_open());
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), -1);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), -1);
    BOOST_CHECK_EQUAL(structuredCompressedFile.size(), 0);

    /* open file */
    structuredCompressedFile.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK(structuredCompressedFile.is_open());
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 0);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 2);
    BOOST_CHECK_EQUAL(structuredCompressedFile.size(), 2);

    /* read log container 0/2 */
    Vector::BLF::ObjectHeaderBase * objectHeaderBase;
    BOOST_CHECK_EQUAL(structuredCompressedFile.read(&objectHeaderBase), 1);
    Vector::BLF::LogContainer * logContainer = dynamic_cast<Vector::BLF::LogContainer *>(objectHeaderBase);
    BOOST_CHECK(logContainer);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 1);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 2);
    delete logContainer;

    /* read log container 1/2 */
    BOOST_CHECK_EQUAL(structuredCompressedFile.read(&objectHeaderBase), 1);
    logContainer = dynamic_cast<Vector::BLF::LogContainer *>(objectHeaderBase);
    BOOST_CHECK(logContainer);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 2);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 2);
    delete logContainer;

    /* read log container 2/2 (not existing) */
    BOOST_CHECK_EQUAL(structuredCompressedFile.read(&objectHeaderBase), 0);
    logContainer = dynamic_cast<Vector::BLF::LogContainer *>(objectHeaderBase);
    BOOST_CHECK(!logContainer);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 2);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 2);

    /* rewind to beginning of file */
    structuredCompressedFile.seekg(0, std::ios_base::beg);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 0);

    /* read log container 0/2 again */
    BOOST_CHECK_EQUAL(structuredCompressedFile.read(&objectHeaderBase), 1);
    logContainer = dynamic_cast<Vector::BLF::LogContainer *>(objectHeaderBase);
    BOOST_CHECK(logContainer);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellg(), 1);
    BOOST_CHECK_EQUAL(structuredCompressedFile.tellp(), 2);
    delete logContainer;

    /* close file */
    structuredCompressedFile.close();
    BOOST_CHECK(!structuredCompressedFile.is_open());
}
