#define BOOST_TEST_MODULE CanMessage
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_MESSAGE = 1 */
BOOST_AUTO_TEST_CASE(CanMessage)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    Vector::BLF::CanMessage * obj = static_cast<Vector::BLF::CanMessage *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 4876870000); // ns

    /* CanMessage */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->flags, 1); // TX
    BOOST_CHECK_EQUAL(obj->dlc, 8);
    BOOST_CHECK_EQUAL(obj->id, 0x854c5638); // 54C5638x
    BOOST_CHECK_EQUAL(obj->data[0], 0);
    BOOST_CHECK_EQUAL(obj->data[1], 0);
    BOOST_CHECK_EQUAL(obj->data[2], 0);
    BOOST_CHECK_EQUAL(obj->data[3], 0);
    BOOST_CHECK_EQUAL(obj->data[4], 0);
    BOOST_CHECK_EQUAL(obj->data[5], 0);
    BOOST_CHECK_EQUAL(obj->data[6], 0);
    BOOST_CHECK_EQUAL(obj->data[7], 0);

    delete obj;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    obj = static_cast<Vector::BLF::CanMessage *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 2501000000);

    /* CanMessage */
    BOOST_CHECK_EQUAL(obj->channel, 2);
    BOOST_CHECK_EQUAL(obj->flags, 0); // RX
    BOOST_CHECK_EQUAL(obj->dlc, 8);
    BOOST_CHECK_EQUAL(obj->id, 0x800000c8); // C8x
    BOOST_CHECK_EQUAL(obj->data[0], 9);
    BOOST_CHECK_EQUAL(obj->data[1], 8);
    BOOST_CHECK_EQUAL(obj->data[2], 7);
    BOOST_CHECK_EQUAL(obj->data[3], 6);
    BOOST_CHECK_EQUAL(obj->data[4], 5);
    BOOST_CHECK_EQUAL(obj->data[5], 4);
    BOOST_CHECK_EQUAL(obj->data[6], 3);
    BOOST_CHECK_EQUAL(obj->data[7], 2);

    delete obj;

    file.close();
}
