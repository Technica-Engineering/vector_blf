#define BOOST_TEST_MODULE RawCompressedFile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/**
 * Test read operations on RawCompressedFile.
 *
 * Actually this is a just a wrapper for std::fstream, so it should behave
 * the same and is kind of a role model for the other File classes.
 */
BOOST_AUTO_TEST_CASE(ReadTest) {
    Vector::BLF::RawCompressedFile rawCompressedFile;

    /* checks after initialize */
    BOOST_CHECK(!rawCompressedFile.is_open());
    BOOST_CHECK_EQUAL(rawCompressedFile.tellg(), -1);
    BOOST_CHECK_EQUAL(rawCompressedFile.tellp(), -1);
    BOOST_CHECK_EQUAL(rawCompressedFile.size(), 0);

    /* open file */
    rawCompressedFile.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK(rawCompressedFile.is_open());
    BOOST_CHECK_EQUAL(rawCompressedFile.tellg(), 0x90); // as FileStatistics was read already
    BOOST_CHECK_EQUAL(rawCompressedFile.size(), 420);

    /* check file statistics */
    Vector::BLF::FileStatistics fileStatistics = rawCompressedFile.statistics();
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

    /* seek back */
    rawCompressedFile.seekg(0);
    BOOST_CHECK_EQUAL(rawCompressedFile.tellg(), 0);

    /* read some data */
    char signature[5] = { 0, 0, 0, 0, 0 }; // including null termination
    BOOST_CHECK_EQUAL(rawCompressedFile.read(signature, 4), 4);
    BOOST_CHECK_EQUAL(signature, "LOGG");
    BOOST_CHECK_EQUAL(rawCompressedFile.tellg(), 4);

    /* rewind to beginning of file */
    rawCompressedFile.seekg(0, std::ios_base::beg);
    BOOST_CHECK_EQUAL(rawCompressedFile.tellg(), 0);
    rawCompressedFile.seekp(0);
    BOOST_CHECK_EQUAL(rawCompressedFile.tellp(), 0);

    /* close file */
    rawCompressedFile.close();
    BOOST_CHECK(!rawCompressedFile.is_open());
}
