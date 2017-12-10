#define BOOST_TEST_MODULE Most150MessageFragment
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_150_MESSAGE_FRAGMENT = 79 */
BOOST_AUTO_TEST_CASE(Most150MessageFragment)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most150MessageFragment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150MessageFragment * most150MessageFragment;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE_FRAGMENT);
    most150MessageFragment = static_cast<Vector::BLF::Most150MessageFragment *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150MessageFragment->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150MessageFragment->headerSize == most150MessageFragment->calculateHeaderSize());
    BOOST_CHECK(most150MessageFragment->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150MessageFragment->objectSize == most150MessageFragment->calculateObjectSize());
    BOOST_CHECK(most150MessageFragment->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE_FRAGMENT);
    /* ObjectHeader2 */
    BOOST_CHECK(most150MessageFragment->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150MessageFragment->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150MessageFragment->objectVersion == 0);
    BOOST_CHECK(most150MessageFragment->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most150MessageFragment->originalTimeStamp == 0);
    /* Most150MessageFragment */
    BOOST_CHECK(most150MessageFragment->channel == 1);
    // reserved
    BOOST_CHECK(most150MessageFragment->ackNack == 0x11); // NoResp | NAck
    BOOST_CHECK(most150MessageFragment->validMask == 0x01020304);
    BOOST_CHECK(most150MessageFragment->sourceAdr == 0x0172);
    BOOST_CHECK(most150MessageFragment->destAdr == 0x03C8);
    BOOST_CHECK(most150MessageFragment->pAck == 0x22);
    BOOST_CHECK(most150MessageFragment->cAck == 0x44);
    BOOST_CHECK(most150MessageFragment->priority == 1);
    BOOST_CHECK(most150MessageFragment->pIndex == 0x33);
    BOOST_CHECK(most150MessageFragment->crc == 0xAABB);
    BOOST_CHECK(most150MessageFragment->dataLen == 6);
    BOOST_CHECK(most150MessageFragment->dataLenAnnounced == 0x0210);
    BOOST_CHECK(most150MessageFragment->firstDataLen == 6);
    // reserved
    BOOST_CHECK(most150MessageFragment->firstData[0] == 0x01);
    BOOST_CHECK(most150MessageFragment->firstData[1] == 0x02);
    BOOST_CHECK(most150MessageFragment->firstData[2] == 0x03);
    BOOST_CHECK(most150MessageFragment->firstData[3] == 0x04);
    BOOST_CHECK(most150MessageFragment->firstData[4] == 0x05);
    BOOST_CHECK(most150MessageFragment->firstData[5] == 0x06);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
