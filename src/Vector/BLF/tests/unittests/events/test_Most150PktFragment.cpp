#define BOOST_TEST_MODULE Most150PktFragment
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_150_PKT_FRAGMENT = 80 */
BOOST_AUTO_TEST_CASE(Most150PktFragment)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most150PktFragment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150PktFragment * most150PktFragment;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_PKT_FRAGMENT);
    most150PktFragment = static_cast<Vector::BLF::Most150PktFragment *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150PktFragment->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150PktFragment->headerSize == most150PktFragment->calculateHeaderSize());
    BOOST_CHECK(most150PktFragment->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150PktFragment->objectSize == most150PktFragment->calculateObjectSize());
    BOOST_CHECK(most150PktFragment->objectType == Vector::BLF::ObjectType::MOST_150_PKT_FRAGMENT);
    /* ObjectHeader2 */
    BOOST_CHECK(most150PktFragment->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150PktFragment->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150PktFragment->objectVersion == 0);
    BOOST_CHECK(most150PktFragment->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most150PktFragment->originalTimeStamp == 0);
    /* Most150PktFragment */
    BOOST_CHECK(most150PktFragment->channel == 1);
    // reserved
    BOOST_CHECK(most150PktFragment->ackNack == 0x11); // NoResp | NAck
    BOOST_CHECK(most150PktFragment->validMask == 0x01020304);
    BOOST_CHECK(most150PktFragment->sourceAdr == 0x0172);
    BOOST_CHECK(most150PktFragment->destAdr == 0x03C8);
    BOOST_CHECK(most150PktFragment->pAck == 0x22);
    BOOST_CHECK(most150PktFragment->cAck == 0x44);
    BOOST_CHECK(most150PktFragment->priority == 1);
    BOOST_CHECK(most150PktFragment->pIndex == 0x33);
    BOOST_CHECK(most150PktFragment->crc == 0xAABB);
    BOOST_CHECK(most150PktFragment->dataLen == 6);
    BOOST_CHECK(most150PktFragment->dataLenAnnounced == 0x0210);
    BOOST_CHECK(most150PktFragment->firstDataLen == 6);
    // reserved
    BOOST_CHECK(most150PktFragment->firstData[0] == 0x01);
    BOOST_CHECK(most150PktFragment->firstData[1] == 0x02);
    BOOST_CHECK(most150PktFragment->firstData[2] == 0x03);
    BOOST_CHECK(most150PktFragment->firstData[3] == 0x04);
    BOOST_CHECK(most150PktFragment->firstData[4] == 0x05);
    BOOST_CHECK(most150PktFragment->firstData[5] == 0x06);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
