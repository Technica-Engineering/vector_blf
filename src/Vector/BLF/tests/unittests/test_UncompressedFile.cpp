#define BOOST_TEST_MODULE UncompressedFile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** Open a file, read/write on it, close it again. */
BOOST_AUTO_TEST_CASE(OpenWriteReadClose)
{
    Vector::BLF::UncompressedFile uncompressedFile;

    /* after initialization */
    BOOST_CHECK_EQUAL(uncompressedFile.gcount(), 0);
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), -1);
    BOOST_CHECK_EQUAL(uncompressedFile.tellp(), -1);
    BOOST_CHECK(uncompressedFile.good());
    BOOST_CHECK(!uncompressedFile.eof());
    BOOST_CHECK_EQUAL(uncompressedFile.size(), 0);

    /* open file */
    uncompressedFile.open();

    /* write data */
    uncompressedFile.write("test", 4);
    BOOST_CHECK_EQUAL(uncompressedFile.tellp(), 4);
    BOOST_CHECK_EQUAL(uncompressedFile.size(), 4);

    /* read data */
    char s1[3] = { 0, 0, 0 }; // including null termination
    uncompressedFile.read(s1, 2);
    BOOST_CHECK_EQUAL(s1, "te");
    BOOST_CHECK_EQUAL(uncompressedFile.gcount(), 2);
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), 2);
    BOOST_CHECK(uncompressedFile.good());
    BOOST_CHECK(!uncompressedFile.eof());
    BOOST_CHECK_EQUAL(uncompressedFile.size(), 2);

    /* read more data */
    char s2[3] = { 0, 0, 0 }; // including null termination
    uncompressedFile.read(s2, 2);
    BOOST_CHECK_EQUAL(s2, "st");
    BOOST_CHECK_EQUAL(uncompressedFile.gcount(), 2);
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), 4);
    BOOST_CHECK(uncompressedFile.good());
    BOOST_CHECK(!uncompressedFile.eof());
    BOOST_CHECK_EQUAL(uncompressedFile.size(), 0);

    /* read beyond eof */
    uncompressedFile.setFileSize(4);
    char s3[2] = { 0, 0 };
    uncompressedFile.read(s3, sizeof(s3));
    BOOST_CHECK_EQUAL(uncompressedFile.gcount(), 0);
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), 4);
    BOOST_CHECK(!uncompressedFile.good());
    BOOST_CHECK(uncompressedFile.eof());
    BOOST_CHECK_EQUAL(uncompressedFile.size(), 0);

    /* drop old data */
    uncompressedFile.dropOldData();

    /* close file */
    uncompressedFile.close();
}

/** test getter/setter for defaultContainerSize */
BOOST_AUTO_TEST_CASE(defaultContainerSize)
{
    Vector::BLF::UncompressedFile uncompressedFile;

    BOOST_CHECK_EQUAL(uncompressedFile.defaultLogContainerSize(), 0x20000);
    uncompressedFile.setDefaultLogContainerSize(0x30000);
    BOOST_CHECK_EQUAL(uncompressedFile.defaultLogContainerSize(), 0x30000);
}

/** Read more than available to test gcount limit. */
BOOST_AUTO_TEST_CASE(ReadMoreThanAvailable)
{
    /* setup logContainer */
    Vector::BLF::LogContainer * logContainer = new Vector::BLF::LogContainer;
    logContainer->uncompressedFile.resize(256);
    for(uint16_t i = 0; i < 256; i++) {
        logContainer->uncompressedFile[i] = i;
    }
    logContainer->uncompressedFileSize = 256;

    /* setup uncompressedFile and set eof */
    Vector::BLF::UncompressedFile uncompressedFile;
    uncompressedFile.open();
    uncompressedFile.write(logContainer);
    uncompressedFile.setFileSize(uncompressedFile.tellp());
    BOOST_CHECK_EQUAL(uncompressedFile.tellp(), 256);

    /* test read beyond eof */
    char data[512];
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), 0);
    uncompressedFile.read(data, sizeof(data));
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), 256);
    BOOST_CHECK_EQUAL(uncompressedFile.gcount(), 256);
}

/** Write data beyond one logContainer size. */
BOOST_AUTO_TEST_CASE(WriteMoreThanAvailable)
{
    /* setup uncompressedFile and set eof */
    Vector::BLF::UncompressedFile uncompressedFile;
    uncompressedFile.open();
    BOOST_CHECK_EQUAL(uncompressedFile.tellp(), 0);

    /* test read beyond eof */
    char data[0x30000];
    uncompressedFile.write(data, 0x30000);
    BOOST_CHECK_EQUAL(uncompressedFile.tellp(), 0x30000);
}

/** Seek before begin of file and try to read. */
BOOST_AUTO_TEST_CASE(SeekBeforeBeginOfFile)
{
    /* setup logContainer */
    Vector::BLF::LogContainer * logContainer = new Vector::BLF::LogContainer;
    logContainer->uncompressedFile.resize(256);
    for(uint16_t i = 0; i < 256; i++) {
        logContainer->uncompressedFile[i] = i;
    }
    logContainer->uncompressedFileSize = 256;

    /* setup uncompressedFile and set eof */
    Vector::BLF::UncompressedFile uncompressedFile;
    uncompressedFile.open();
    uncompressedFile.write(logContainer);
    BOOST_CHECK_EQUAL(uncompressedFile.tellp(), 256);
    uncompressedFile.setFileSize(uncompressedFile.tellp());

    /* seek in middle of the logContainer */
    uncompressedFile.seekg(-128, std::ios_base::cur);
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), -128);

    /* try to read -128..128 */
    char data[256];
    uncompressedFile.read(data, sizeof(data));
    BOOST_CHECK_EQUAL(uncompressedFile.gcount(), 0);
}
