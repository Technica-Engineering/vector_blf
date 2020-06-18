#define BOOST_TEST_MODULE CanFdMessage64
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_FD_MESSAGE_64 = 101 */
BOOST_AUTO_TEST_CASE(CanFdMessage64) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanFdMessage64.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_MESSAGE_64);
    auto * obj = dynamic_cast<Vector::BLF::CanFdMessage64 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_FD_MESSAGE_64);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* CanFdMessage64 */
    BOOST_CHECK_EQUAL(obj->channel, 0x11);
    BOOST_CHECK_EQUAL(obj->dlc, 0x22);
    BOOST_CHECK_EQUAL(obj->validDataBytes, 64);
    BOOST_CHECK_EQUAL(obj->txCount, 0x44);
    BOOST_CHECK_EQUAL(obj->id, 0x55555555);
    BOOST_CHECK_EQUAL(obj->frameLength, 0x66666666);
    BOOST_CHECK_EQUAL(obj->flags, 0x77777777);
    BOOST_CHECK_EQUAL(obj->btrCfgArb, 0x88888888);
    BOOST_CHECK_EQUAL(obj->btrCfgData, 0x99999999);
    BOOST_CHECK_EQUAL(obj->timeOffsetBrsNs, 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->timeOffsetCrcDelNs, 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->bitCount, 0xCCCC);
    BOOST_CHECK_EQUAL(obj->dir, 0xDD);
    BOOST_CHECK_EQUAL(obj->extDataOffset, 0x50);
    BOOST_CHECK_EQUAL(obj->crc, 0xFFFFFFFF);
    for (uint8_t i = 0; i < 64; i++)
        BOOST_CHECK_EQUAL(obj->data[i], i);
    BOOST_CHECK_EQUAL(obj->btrExtArb, 0x11111111);
    BOOST_CHECK_EQUAL(obj->btrExtData, 0x22222222);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_MESSAGE_64);

    delete ohb;

    /* read last */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::Unknown115);

    delete ohb;

    /* read last */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::Unknown115);

    delete ohb;

    /* read eof */
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    file.close();
}
