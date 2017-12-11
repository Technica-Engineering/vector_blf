#define BOOST_TEST_MODULE Most50Message
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_50_MESSAGE = 84 */
BOOST_AUTO_TEST_CASE(Most50Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most50Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);
    Vector::BLF::Most50Message * obj = static_cast<Vector::BLF::Most50Message *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_50_MESSAGE);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 200000000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* Most50Message */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->dir, 0); // Rx
    // reserved
    BOOST_CHECK_EQUAL(obj->sourceAdr, 0xEF00);
    BOOST_CHECK_EQUAL(obj->destAdr, 0x0101);
    BOOST_CHECK_EQUAL(obj->transferType, 2); // Spy
    BOOST_CHECK_EQUAL(obj->state, 0x01); // bus active
    BOOST_CHECK_EQUAL(obj->ackNack, 0x00);
    // reserved
    BOOST_CHECK_EQUAL(obj->crc, 0x5678);
    // reserved
    BOOST_CHECK_EQUAL(obj->priority, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->msgLen, 9);
    // reserved
    BOOST_CHECK_EQUAL(obj->msg[0], 0x11);
    BOOST_CHECK_EQUAL(obj->msg[1], 0x01);
    BOOST_CHECK_EQUAL(obj->msg[2], 0x22);
    BOOST_CHECK_EQUAL(obj->msg[3], 0x23);
    BOOST_CHECK_EQUAL(obj->msg[4], 0x04);
    BOOST_CHECK_EQUAL(obj->msg[5], 0x11);
    BOOST_CHECK_EQUAL(obj->msg[6], 0x22);
    BOOST_CHECK_EQUAL(obj->msg[7], 0x33);
    BOOST_CHECK_EQUAL(obj->msg[8], 0x44);

    delete obj;

    file.close();
}
