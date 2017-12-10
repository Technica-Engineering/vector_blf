#define BOOST_TEST_MODULE MostPkt2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_PKT2 = 33 */
BOOST_AUTO_TEST_CASE(MostPkt2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostPkt2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostPkt2 * mostPkt2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_PKT2);
    mostPkt2 = static_cast<Vector::BLF::MostPkt2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostPkt2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostPkt2->headerSize == mostPkt2->calculateHeaderSize());
    BOOST_CHECK(mostPkt2->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostPkt2->objectSize == mostPkt2->calculateObjectSize());
    BOOST_CHECK(mostPkt2->objectType == Vector::BLF::ObjectType::MOST_PKT2);
    /* ObjectHeader2 */
    BOOST_CHECK(mostPkt2->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostPkt2->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostPkt2->objectVersion == 0);
    BOOST_CHECK(mostPkt2->objectTimeStamp == 4445080000); // ns
    BOOST_CHECK(mostPkt2->originalTimeStamp == 0);
    /* MostPkt2 */
    BOOST_CHECK(mostPkt2->channel == 1);
    BOOST_CHECK(mostPkt2->dir == 0); // Rx
    // reserved
    BOOST_CHECK(mostPkt2->sourceAdr == 0x0101);
    BOOST_CHECK(mostPkt2->destAdr == 0x0100);
    BOOST_CHECK(mostPkt2->arbitration == 0x03);
    BOOST_CHECK(mostPkt2->timeRes == 0);
    BOOST_CHECK(mostPkt2->quadsToFollow == 0);
    // reserved
    BOOST_CHECK(mostPkt2->crc == 0x0000);
    BOOST_CHECK(mostPkt2->priority == 0);
    BOOST_CHECK(mostPkt2->transferType == 1); // Node
    BOOST_CHECK(mostPkt2->state == 0); // Rx
    // reserved
    BOOST_CHECK(mostPkt2->pktDataLength == 0x0A);
    // reserved
    BOOST_CHECK(mostPkt2->pktData[0] == 0x52);
    BOOST_CHECK(mostPkt2->pktData[1] == 0x01);
    BOOST_CHECK(mostPkt2->pktData[2] == 0xE0);
    BOOST_CHECK(mostPkt2->pktData[3] == 0x3C);
    BOOST_CHECK(mostPkt2->pktData[4] == 0x90);
    BOOST_CHECK(mostPkt2->pktData[5] == 0x01);
    BOOST_CHECK(mostPkt2->pktData[6] == 0xFD);
    BOOST_CHECK(mostPkt2->pktData[7] == 0x00);
    BOOST_CHECK(mostPkt2->pktData[8] == 0x00);
    BOOST_CHECK(mostPkt2->pktData[9] == 0x00);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
