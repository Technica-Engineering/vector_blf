#define BOOST_TEST_MODULE MostEthernetPktFragment
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_ETHERNET_PKT_FRAGMENT = 81 */
BOOST_AUTO_TEST_CASE(MostEthernetPktFragment)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostEthernetPktFragment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostEthernetPktFragment * mostEthernetPktFragment;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT);
    mostEthernetPktFragment = static_cast<Vector::BLF::MostEthernetPktFragment *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostEthernetPktFragment->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostEthernetPktFragment->headerSize == mostEthernetPktFragment->calculateHeaderSize());
    BOOST_CHECK(mostEthernetPktFragment->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostEthernetPktFragment->objectSize == mostEthernetPktFragment->calculateObjectSize());
    BOOST_CHECK(mostEthernetPktFragment->objectType == Vector::BLF::ObjectType::MOST_ETHERNET_PKT_FRAGMENT);
    /* ObjectHeader2 */
    BOOST_CHECK(mostEthernetPktFragment->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostEthernetPktFragment->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostEthernetPktFragment->objectVersion == 0);
    BOOST_CHECK(mostEthernetPktFragment->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(mostEthernetPktFragment->originalTimeStamp == 0);
    /* MostEthernetPktFragment */
    BOOST_CHECK(mostEthernetPktFragment->channel == 1);
    // reserved
    BOOST_CHECK(mostEthernetPktFragment->ackNack == 0x11); // Ack|NoResp
    BOOST_CHECK(mostEthernetPktFragment->validMask == 0x01020304);
    BOOST_CHECK(mostEthernetPktFragment->sourceMacAdr == 0x010203040506);
    BOOST_CHECK(mostEthernetPktFragment->destMacAdr == 0x112233445566);
    BOOST_CHECK(mostEthernetPktFragment->pAck == 0x01); // Buffer full
    BOOST_CHECK(mostEthernetPktFragment->cAck == 0x44); // OK
    // reserved
    BOOST_CHECK(mostEthernetPktFragment->crc == 0xAABBCCDD);
    BOOST_CHECK(mostEthernetPktFragment->dataLen == 0x0006);
    BOOST_CHECK(mostEthernetPktFragment->dataLenAnnounced == 0x0210);
    BOOST_CHECK(mostEthernetPktFragment->firstDataLen == 0x0006);
    // reserved
    BOOST_CHECK(mostEthernetPktFragment->firstData[0] == 0x01);
    BOOST_CHECK(mostEthernetPktFragment->firstData[1] == 0x02);
    BOOST_CHECK(mostEthernetPktFragment->firstData[2] == 0x03);
    BOOST_CHECK(mostEthernetPktFragment->firstData[3] == 0x04);
    BOOST_CHECK(mostEthernetPktFragment->firstData[4] == 0x05);
    BOOST_CHECK(mostEthernetPktFragment->firstData[5] == 0x06);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
