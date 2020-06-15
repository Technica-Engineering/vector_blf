#define BOOST_TEST_MODULE LogContainer
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** Make some basic tests. */
BOOST_AUTO_TEST_CASE(SimpleTest) {
    Vector::BLF::LogContainer logContainer;

    logContainer.compressedFile.resize(0x00);
    BOOST_CHECK_EQUAL(logContainer.calculateObjectSize(), 0x20);

    logContainer.compressedFile.resize(0x10);
    BOOST_CHECK_EQUAL(logContainer.calculateObjectSize(), 0x30);
}

/** compress a LogContainer, manipulate the uncompressedSize and see if it throws on uncompress */
BOOST_AUTO_TEST_CASE(LogContainerUnexpectedUncompressedSizeException) {
    Vector::BLF::LogContainer logContainer;
    std::vector<char> uncompressedFile;

    /* put in some uncompressedData */
    uncompressedFile.resize(256);
    for (uint16_t i = 0; i < 256; i++)
        uncompressedFile[i] = i;
    logContainer.uncompressedFileSize = 256;

    /* compress LogContainer */
    logContainer.compress(uncompressedFile, 2, 6); // ZLib compression with default compressionLevel

    /* manipulate uncompressedFileSize */
    logContainer.uncompressedFileSize++;

    /* uncompress LogContainer */
    BOOST_CHECK_THROW(logContainer.uncompress(uncompressedFile), Vector::BLF::Exception);
}

/** compress a LogContainer, manipulate the compressedFile and see if it throws on uncompress */
BOOST_AUTO_TEST_CASE(LogContainerUncompressErrorException) {
    Vector::BLF::LogContainer logContainer;
    std::vector<char> uncompressedFile;

    /* put in some uncompressedData */
    uncompressedFile.resize(256);
    for (uint16_t i = 0; i < 256; i++)
        uncompressedFile[i] = i;
    logContainer.uncompressedFileSize = 256;

    /* compress LogContainer */
    logContainer.compress(uncompressedFile, 2, 6); // ZLib compression with default compressionLevel

    /* manipulate uncompressedFile */
    logContainer.compressedFile[1] = 123;

    /* uncompress LogContainer */
    BOOST_CHECK_THROW(logContainer.uncompress(uncompressedFile), Vector::BLF::Exception);
}

/** compress a LogContainer, manipulate the compressionMethod and see if it throws on uncompress */
BOOST_AUTO_TEST_CASE(LogContainerUnknownCompressionMethod) {
    Vector::BLF::LogContainer logContainer;
    std::vector<char> uncompressedFile;

    /* put in some uncompressedData */
    uncompressedFile.resize(256);
    for (uint16_t i = 0; i < 256; i++)
        uncompressedFile[i] = i;
    logContainer.uncompressedFileSize = 256;

    /* compress LogContainer */
    logContainer.compress(uncompressedFile, 2, 6); // ZLib compression with default compressionLevel

    /* manipulate compressionMethod */
    logContainer.compressionMethod = 123;

    /* uncompress LogContainer */
    BOOST_CHECK_THROW(logContainer.uncompress(uncompressedFile), Vector::BLF::Exception);
}

/** compress a LogContainer with wrong compressionMethod or -Level and see if it throws */
BOOST_AUTO_TEST_CASE(LogContainerCompressedWithWrongCompresionMethodOrLevel) {
    Vector::BLF::LogContainer logContainer;
    std::vector<char> uncompressedFile;

    /* put in some uncompressedData */
    uncompressedFile.resize(256);
    for (uint16_t i = 0; i < 256; i++)
        uncompressedFile[i] = i;
    logContainer.uncompressedFileSize = 256;

    /* compress LogContainer */
    BOOST_CHECK_THROW(logContainer.compress(uncompressedFile, 1, 0), Vector::BLF::Exception); // undefined compressionMethod

    /* compress LogContainer */
    BOOST_CHECK_THROW(logContainer.compress(uncompressedFile, 2, 10), Vector::BLF::Exception); // ZLib with undefined compressionLevel
}
