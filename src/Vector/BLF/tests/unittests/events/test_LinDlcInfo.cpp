#define BOOST_TEST_MODULE LinDlcInfo
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_DLC_INFO = 13 */
BOOST_AUTO_TEST_CASE(LinDlcInfo)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinDlcInfo.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinDlcInfo * linDlcInfo;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_DLC_INFO);
    linDlcInfo = static_cast<Vector::BLF::LinDlcInfo *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linDlcInfo->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linDlcInfo->headerSize == linDlcInfo->calculateHeaderSize());
    BOOST_CHECK(linDlcInfo->headerVersion == 1);
    BOOST_CHECK(linDlcInfo->objectSize == linDlcInfo->calculateObjectSize());
    BOOST_CHECK(linDlcInfo->objectType == Vector::BLF::ObjectType::LIN_DLC_INFO);
    /* ObjectHeader */
    BOOST_CHECK(linDlcInfo->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linDlcInfo->objectVersion == 0);
    BOOST_CHECK(linDlcInfo->objectTimeStamp == 12637500000); // ns
    /* LinDlcInfo */
    BOOST_CHECK(linDlcInfo->channel == 1);
    BOOST_CHECK(linDlcInfo->id == 20);
    BOOST_CHECK(linDlcInfo->dlc == 4);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
