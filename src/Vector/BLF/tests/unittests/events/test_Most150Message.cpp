#define BOOST_TEST_MODULE Most150Message
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_150_MESSAGE = 76 */
BOOST_AUTO_TEST_CASE(Most150Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most150Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150Message * most150Message;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE);
    most150Message = static_cast<Vector::BLF::Most150Message *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150Message->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150Message->headerSize == most150Message->calculateHeaderSize());
    BOOST_CHECK(most150Message->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150Message->objectSize == most150Message->calculateObjectSize());
    BOOST_CHECK(most150Message->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE);
    /* ObjectHeader2 */
    BOOST_CHECK(most150Message->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150Message->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150Message->objectVersion == 0);
    BOOST_CHECK(most150Message->objectTimeStamp == 5708800000); // ns
    BOOST_CHECK(most150Message->originalTimeStamp == 0);
    /* Most150Message */
    BOOST_CHECK(most150Message->channel == 1);
    BOOST_CHECK(most150Message->dir == 1); // Tx
    // reserved
    BOOST_CHECK(most150Message->sourceAdr == 0x0172);
    BOOST_CHECK(most150Message->destAdr == 0x03C8);
    BOOST_CHECK(most150Message->transferType == 1); // Node
    BOOST_CHECK(most150Message->state == 0x02);
    BOOST_CHECK(most150Message->ackNack == 0x11); // Ack
    // reserved
    BOOST_CHECK(most150Message->crc == 0xAABB);
    BOOST_CHECK(most150Message->pAck == 0x22);
    BOOST_CHECK(most150Message->cAck == 0x44);
    BOOST_CHECK(most150Message->priority == 1);
    BOOST_CHECK(most150Message->pIndex == 0x33);
    BOOST_CHECK(most150Message->msgLen == 8);
    // reserved
    BOOST_CHECK(most150Message->msg[0] == 0x11);
    BOOST_CHECK(most150Message->msg[1] == 0x22);
    BOOST_CHECK(most150Message->msg[2] == 0x33);
    BOOST_CHECK(most150Message->msg[3] == 0x34);
    BOOST_CHECK(most150Message->msg[4] == 0x00);
    BOOST_CHECK(most150Message->msg[5] == 0x02);
    BOOST_CHECK(most150Message->msg[6] == 0x11);
    BOOST_CHECK(most150Message->msg[7] == 0x22);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
