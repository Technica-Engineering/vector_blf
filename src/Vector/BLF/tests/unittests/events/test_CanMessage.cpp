#define BOOST_TEST_MODULE CanMessage
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_MESSAGE = 1 */
BOOST_AUTO_TEST_CASE(CanMessage)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanMessage * canMessage;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    canMessage = static_cast<Vector::BLF::CanMessage *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canMessage->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canMessage->headerSize == canMessage->calculateHeaderSize());
    BOOST_CHECK(canMessage->headerVersion == 1);
    BOOST_CHECK(canMessage->objectSize == canMessage->calculateObjectSize());
    BOOST_CHECK(canMessage->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    /* ObjectHeader */
    BOOST_CHECK(canMessage->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canMessage->objectVersion == 0);
    BOOST_CHECK(canMessage->objectTimeStamp == 4876870000); // ns
    /* CanMessage */
    BOOST_CHECK(canMessage->channel == 1);
    BOOST_CHECK(canMessage->flags == 1); // TX
    BOOST_CHECK(canMessage->dlc == 8);
    BOOST_CHECK(canMessage->id == 0x854c5638); // 54C5638x
    BOOST_CHECK(canMessage->data[0] == 0);
    BOOST_CHECK(canMessage->data[1] == 0);
    BOOST_CHECK(canMessage->data[2] == 0);
    BOOST_CHECK(canMessage->data[3] == 0);
    BOOST_CHECK(canMessage->data[4] == 0);
    BOOST_CHECK(canMessage->data[5] == 0);
    BOOST_CHECK(canMessage->data[6] == 0);
    BOOST_CHECK(canMessage->data[7] == 0);
    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    canMessage = static_cast<Vector::BLF::CanMessage *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canMessage->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canMessage->headerSize == canMessage->calculateHeaderSize());
    // reserved
    BOOST_CHECK(canMessage->headerVersion == 1);
    BOOST_CHECK(canMessage->objectSize == canMessage->calculateObjectSize());
    BOOST_CHECK(canMessage->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    /* ObjectHeader */
    BOOST_CHECK(canMessage->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canMessage->objectVersion == 0);
    BOOST_CHECK(canMessage->objectTimeStamp == 2501000000); // ns
    /* CanMessage */
    BOOST_CHECK(canMessage->channel == 2);
    BOOST_CHECK(canMessage->flags == 0); // RX
    BOOST_CHECK(canMessage->dlc == 8);
    BOOST_CHECK(canMessage->id == 0x800000c8); // C8x
    BOOST_CHECK(canMessage->data[0] == 9);
    BOOST_CHECK(canMessage->data[1] == 8);
    BOOST_CHECK(canMessage->data[2] == 7);
    BOOST_CHECK(canMessage->data[3] == 6);
    BOOST_CHECK(canMessage->data[4] == 5);
    BOOST_CHECK(canMessage->data[5] == 4);
    BOOST_CHECK(canMessage->data[6] == 3);
    BOOST_CHECK(canMessage->data[7] == 2);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
