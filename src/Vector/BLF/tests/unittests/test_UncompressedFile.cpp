#define BOOST_TEST_MODULE UncompressedFile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** Open a file, read/write on it, close it again. */
BOOST_AUTO_TEST_CASE(SimpleTest)
{
    Vector::BLF::UncompressedFile uncompressedFile;

    /* after initialization */
    BOOST_CHECK_EQUAL(uncompressedFile.gcount(), 0);
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), 0);
    BOOST_CHECK_EQUAL(uncompressedFile.tellp(), 0);
    BOOST_CHECK(!uncompressedFile.eof());
    BOOST_CHECK(!uncompressedFile.atEof());
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
    BOOST_CHECK(!uncompressedFile.eof());
    BOOST_CHECK(!uncompressedFile.atEof());
    BOOST_CHECK_EQUAL(uncompressedFile.size(), 2);

    /* read more data */
    char s2[3] = { 0, 0, 0 }; // including null termination
    uncompressedFile.read(s2, 2);
    BOOST_CHECK_EQUAL(s2, "st");
    BOOST_CHECK_EQUAL(uncompressedFile.gcount(), 2);
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), 4);
    BOOST_CHECK(!uncompressedFile.eof());
    BOOST_CHECK_EQUAL(uncompressedFile.size(), 0);

    /* read beyond eof */
    uncompressedFile.setFileSize(4);
    BOOST_CHECK(uncompressedFile.atEof());
    char s3[2] = { 0, 0 };
    uncompressedFile.read(s3, sizeof(s3));
    BOOST_CHECK_EQUAL(uncompressedFile.gcount(), 0);
    BOOST_CHECK_EQUAL(uncompressedFile.tellg(), 4);
    BOOST_CHECK(uncompressedFile.eof());
    BOOST_CHECK(uncompressedFile.atEof());
    BOOST_CHECK_EQUAL(uncompressedFile.size(), 0);

    /* drop old data */
    uncompressedFile.dropOldData();

    /* close file */
    uncompressedFile.close();
}
