#define BOOST_TEST_MODULE LinChecksumInfo
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_CHECKSUM_INFO = 42 */
BOOST_AUTO_TEST_CASE(LinChecksumInfo)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinChecksumInfo.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinChecksumInfo * linChecksumInfo;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_CHECKSUM_INFO);
    linChecksumInfo = static_cast<Vector::BLF::LinChecksumInfo *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linChecksumInfo->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linChecksumInfo->headerSize == linChecksumInfo->calculateHeaderSize());
    BOOST_CHECK(linChecksumInfo->headerVersion == 1);
    BOOST_CHECK(linChecksumInfo->objectSize == linChecksumInfo->calculateObjectSize());
    BOOST_CHECK(linChecksumInfo->objectType == Vector::BLF::ObjectType::LIN_CHECKSUM_INFO);
    /* ObjectHeader */
    BOOST_CHECK(linChecksumInfo->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linChecksumInfo->objectVersion == 0);
    BOOST_CHECK(linChecksumInfo->objectTimeStamp == 20100000); // ns
    /* LinChecksumInfo */
    BOOST_CHECK(linChecksumInfo->channel == 1);
    BOOST_CHECK(linChecksumInfo->id == 22);
    BOOST_CHECK(linChecksumInfo->checksumModel == 0); // classic
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
