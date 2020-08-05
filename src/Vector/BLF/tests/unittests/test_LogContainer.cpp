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
    /* put in some uncompressedData */
    std::vector<uint8_t> uncompressedFile(256);
    for (uint16_t i = 0; i < 256; i++)
        uncompressedFile[i] = i;

    /* compress LogContainer */
    Vector::BLF::LogContainer logContainer;
    logContainer.compress(uncompressedFile, 2, 6); // ZLib compression with default compressionLevel
    BOOST_CHECK_EQUAL(logContainer.uncompressedFileSize, 256);

    /* manipulate uncompressedFileSize */
    logContainer.uncompressedFileSize++;

    /* uncompress LogContainer */
    BOOST_CHECK_THROW(logContainer.uncompress(uncompressedFile), Vector::BLF::Exception);
}

/** compress a LogContainer, manipulate the compressedFile and see if it throws on uncompress */
BOOST_AUTO_TEST_CASE(LogContainerUncompressErrorException) {
    /* put in some uncompressedData */
    std::vector<uint8_t> uncompressedFile(256);
    for (uint16_t i = 0; i < 256; i++)
        uncompressedFile[i] = i;

    /* compress LogContainer */
    Vector::BLF::LogContainer logContainer;
    logContainer.compress(uncompressedFile, 2, 6); // ZLib compression with default compressionLevel
    BOOST_CHECK_EQUAL(logContainer.uncompressedFileSize, 256);

    /* manipulate uncompressedFile */
    logContainer.compressedFile[1] = 123;

    /* uncompress LogContainer */
    BOOST_CHECK_THROW(logContainer.uncompress(uncompressedFile), Vector::BLF::Exception);
}

/** compress a LogContainer, manipulate the compressionMethod and see if it throws on uncompress */
BOOST_AUTO_TEST_CASE(LogContainerUnknownCompressionMethod) {
    /* put in some uncompressedData */
    std::vector<uint8_t> uncompressedFile(256);
    for (uint16_t i = 0; i < 256; i++)
        uncompressedFile[i] = i;

    /* compress LogContainer */
    Vector::BLF::LogContainer logContainer;
    logContainer.compress(uncompressedFile, 2, 6); // ZLib compression with default compressionLevel
    BOOST_CHECK_EQUAL(logContainer.uncompressedFileSize, 256);

    /* manipulate compressionMethod */
    logContainer.compressionMethod = 123;

    /* uncompress LogContainer */
    BOOST_CHECK_THROW(logContainer.uncompress(uncompressedFile), Vector::BLF::Exception);
}

/** compress a LogContainer with wrong compressionMethod or -Level and see if it throws */
BOOST_AUTO_TEST_CASE(LogContainerCompressedWithWrongCompresionMethodOrLevel) {
    /* put in some uncompressedData */
    std::vector<uint8_t> uncompressedFile(256);
    for (uint16_t i = 0; i < 256; i++)
        uncompressedFile[i] = i;

    /* compress LogContainer */
    Vector::BLF::LogContainer logContainer;
    BOOST_CHECK_THROW(logContainer.compress(uncompressedFile, 1, 0), Vector::BLF::Exception); // undefined compressionMethod

    /* compress LogContainer */
    BOOST_CHECK_THROW(logContainer.compress(uncompressedFile, 2, 10), Vector::BLF::Exception); // ZLib with undefined compressionLevel
}
