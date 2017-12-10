#define BOOST_TEST_MODULE Most150Pkt
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_150_PKT = 77 */
BOOST_AUTO_TEST_CASE(Most150Pkt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most150Pkt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150Pkt * most150Pkt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_PKT);
    most150Pkt = static_cast<Vector::BLF::Most150Pkt *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150Pkt->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150Pkt->headerSize == most150Pkt->calculateHeaderSize());
    BOOST_CHECK(most150Pkt->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150Pkt->objectSize == most150Pkt->calculateObjectSize());
    BOOST_CHECK(most150Pkt->objectType == Vector::BLF::ObjectType::MOST_150_PKT);
    /* ObjectHeader2 */
    BOOST_CHECK(most150Pkt->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150Pkt->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150Pkt->objectVersion == 0);
    BOOST_CHECK(most150Pkt->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most150Pkt->originalTimeStamp == 0);
    /* Most150Pkt */
    BOOST_CHECK(most150Pkt->channel == 1);
    BOOST_CHECK(most150Pkt->dir == 1); // Tx
    // reserved
    BOOST_CHECK(most150Pkt->sourceAdr == 0x0172);
    BOOST_CHECK(most150Pkt->destAdr == 0x03C8);
    BOOST_CHECK(most150Pkt->transferType == 1); // Node
    BOOST_CHECK(most150Pkt->state == 0x02);
    BOOST_CHECK(most150Pkt->ackNack == 0x11); // Ack|Valid
    // reserved
    BOOST_CHECK(most150Pkt->crc == 0xAABB);
    BOOST_CHECK(most150Pkt->pAck == 0x00); // No Response
    BOOST_CHECK(most150Pkt->cAck == 0x44); // OK
    BOOST_CHECK(most150Pkt->priority == 0x00);
    BOOST_CHECK(most150Pkt->pIndex == 0x33);
    BOOST_CHECK(most150Pkt->pktDataLength == 8);
    // reserved
    BOOST_CHECK(most150Pkt->pktData[0] == 0x11);
    BOOST_CHECK(most150Pkt->pktData[1] == 0x22);
    BOOST_CHECK(most150Pkt->pktData[2] == 0x33);
    BOOST_CHECK(most150Pkt->pktData[3] == 0x34);
    BOOST_CHECK(most150Pkt->pktData[4] == 0x00);
    BOOST_CHECK(most150Pkt->pktData[5] == 0x02);
    BOOST_CHECK(most150Pkt->pktData[6] == 0x11);
    BOOST_CHECK(most150Pkt->pktData[7] == 0x22);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
