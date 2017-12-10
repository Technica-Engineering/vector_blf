#define BOOST_TEST_MODULE Most50Message
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_50_MESSAGE = 84 */
BOOST_AUTO_TEST_CASE(Most50Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most50Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most50Message * most50Message;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);
    most50Message = static_cast<Vector::BLF::Most50Message *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most50Message->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most50Message->headerSize == most50Message->calculateHeaderSize());
    BOOST_CHECK(most50Message->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most50Message->objectSize == most50Message->calculateObjectSize());
    BOOST_CHECK(most50Message->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);
    /* ObjectHeader2 */
    BOOST_CHECK(most50Message->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most50Message->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most50Message->objectVersion == 0);
    BOOST_CHECK(most50Message->objectTimeStamp == 200000000); // ns
    BOOST_CHECK(most50Message->originalTimeStamp == 0);
    /* Most50Message */
    BOOST_CHECK(most50Message->channel == 1);
    BOOST_CHECK(most50Message->dir == 0); // Rx
    // reserved
    BOOST_CHECK(most50Message->sourceAdr == 0xEF00);
    BOOST_CHECK(most50Message->destAdr == 0x0101);
    BOOST_CHECK(most50Message->transferType == 2); // Spy
    BOOST_CHECK(most50Message->state == 0x01); // bus active
    BOOST_CHECK(most50Message->ackNack == 0x00);
    // reserved
    BOOST_CHECK(most50Message->crc == 0x5678);
    // reserved
    BOOST_CHECK(most50Message->priority == 0);
    // reserved
    BOOST_CHECK(most50Message->msgLen == 9);
    // reserved
    BOOST_CHECK(most50Message->msg[0] == 0x11);
    BOOST_CHECK(most50Message->msg[1] == 0x01);
    BOOST_CHECK(most50Message->msg[2] == 0x22);
    BOOST_CHECK(most50Message->msg[3] == 0x23);
    BOOST_CHECK(most50Message->msg[4] == 0x04);
    BOOST_CHECK(most50Message->msg[5] == 0x11);
    BOOST_CHECK(most50Message->msg[6] == 0x22);
    BOOST_CHECK(most50Message->msg[7] == 0x33);
    BOOST_CHECK(most50Message->msg[8] == 0x44);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
