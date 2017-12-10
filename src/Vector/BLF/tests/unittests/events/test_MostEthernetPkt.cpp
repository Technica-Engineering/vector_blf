#define BOOST_TEST_MODULE MostEthernetPkt
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_ETHERNET_PKT = 78 */
BOOST_AUTO_TEST_CASE(MostEthernetPkt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostEthernetPkt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostEthernetPkt * mostEthernetPkt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT);
    mostEthernetPkt = static_cast<Vector::BLF::MostEthernetPkt *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostEthernetPkt->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostEthernetPkt->headerSize == mostEthernetPkt->calculateHeaderSize());
    BOOST_CHECK(mostEthernetPkt->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostEthernetPkt->objectSize == mostEthernetPkt->calculateObjectSize());
    BOOST_CHECK(mostEthernetPkt->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT);
    /* ObjectHeader2 */
    BOOST_CHECK(mostEthernetPkt->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostEthernetPkt->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostEthernetPkt->objectVersion == 0);
    BOOST_CHECK(mostEthernetPkt->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(mostEthernetPkt->originalTimeStamp == 0);
    /* MostEthernetPkt */
    BOOST_CHECK(mostEthernetPkt->channel == 1);
    BOOST_CHECK(mostEthernetPkt->dir == 1); // Tx
    // reserved
    BOOST_CHECK(mostEthernetPkt->sourceMacAdr == 0x010203040506);
    BOOST_CHECK(mostEthernetPkt->destMacAdr == 0x112233445566);
    BOOST_CHECK(mostEthernetPkt->transferType == 1); // Node
    BOOST_CHECK(mostEthernetPkt->state == 0x02); // ???
    BOOST_CHECK(mostEthernetPkt->ackNack == 0x11); // Valid | Ack
    // reserved
    BOOST_CHECK(mostEthernetPkt->crc == 0xAABBCCDD);
    BOOST_CHECK(mostEthernetPkt->pAck == 0x22);
    BOOST_CHECK(mostEthernetPkt->cAck == 0x44);
    // reserved
    BOOST_CHECK(mostEthernetPkt->pktDataLength == 8);
    // reserved
    BOOST_CHECK(mostEthernetPkt->pktData[0] == 0x11);
    BOOST_CHECK(mostEthernetPkt->pktData[1] == 0x22);
    BOOST_CHECK(mostEthernetPkt->pktData[2] == 0x33);
    BOOST_CHECK(mostEthernetPkt->pktData[3] == 0x34);
    BOOST_CHECK(mostEthernetPkt->pktData[4] == 0x00);
    BOOST_CHECK(mostEthernetPkt->pktData[5] == 0x02);
    BOOST_CHECK(mostEthernetPkt->pktData[6] == 0x11);
    BOOST_CHECK(mostEthernetPkt->pktData[7] == 0x22);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
