#define BOOST_TEST_MODULE Most50Pkt
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_50_PKT = 85 */
BOOST_AUTO_TEST_CASE(Most50Pkt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most50Pkt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most50Pkt * most50Pkt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_50_PKT);
    most50Pkt = static_cast<Vector::BLF::Most50Pkt *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most50Pkt->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most50Pkt->headerSize == most50Pkt->calculateHeaderSize());
    BOOST_CHECK(most50Pkt->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most50Pkt->objectSize == most50Pkt->calculateObjectSize());
    BOOST_CHECK(most50Pkt->objectType == Vector::BLF::ObjectType::MOST_50_PKT);
    /* ObjectHeader2 */
    BOOST_CHECK(most50Pkt->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most50Pkt->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most50Pkt->objectVersion == 0);
    BOOST_CHECK(most50Pkt->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most50Pkt->originalTimeStamp == 0);
    /* Most50Pkt */
    BOOST_CHECK(most50Pkt->channel == 1);
    BOOST_CHECK(most50Pkt->dir == 1); // Tx
    // reserved
    BOOST_CHECK(most50Pkt->sourceAdr == 0x0172);
    BOOST_CHECK(most50Pkt->destAdr == 0x03C8);
    BOOST_CHECK(most50Pkt->transferType == 1); // Node
    BOOST_CHECK(most50Pkt->state == 2); // ???
    BOOST_CHECK(most50Pkt->ackNack == 0x11); // Valid | Ack
    // reserved
    BOOST_CHECK(most50Pkt->crc == 0xAABB);
    // reserved
    BOOST_CHECK(most50Pkt->priority == 0);
    BOOST_CHECK(most50Pkt->pktDataLength == 8);
    BOOST_CHECK(most50Pkt->pktData[0] == 0x11);
    BOOST_CHECK(most50Pkt->pktData[1] == 0x22);
    BOOST_CHECK(most50Pkt->pktData[2] == 0x33);
    BOOST_CHECK(most50Pkt->pktData[3] == 0x34);
    BOOST_CHECK(most50Pkt->pktData[4] == 0x00);
    BOOST_CHECK(most50Pkt->pktData[5] == 0x02);
    BOOST_CHECK(most50Pkt->pktData[6] == 0x11);
    BOOST_CHECK(most50Pkt->pktData[7] == 0x22);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
