#define BOOST_TEST_MODULE SerialEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* SERIAL_EVENT = 90 */
BOOST_AUTO_TEST_CASE(SerialEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_SerialEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);
    Vector::BLF::SerialEvent * obj = static_cast<Vector::BLF::SerialEvent *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 12315000000); // ns

    /* SerialEvent */
    BOOST_CHECK_EQUAL(obj->flags, ((uint32_t) (Vector::BLF::SerialEvent::Flags::KLineEvent) |
                                   (uint32_t) (Vector::BLF::SerialEvent::Flags::CompactByte)));
    BOOST_CHECK_EQUAL(obj->port, 2);
    BOOST_CHECK_EQUAL(obj->baudrate, 10400);
    // reserved
    BOOST_CHECK_EQUAL(obj->compact.compactLength, 7);
    BOOST_CHECK_EQUAL(obj->compact.compactData[0], 0x83);
    BOOST_CHECK_EQUAL(obj->compact.compactData[1], 0x11);
    BOOST_CHECK_EQUAL(obj->compact.compactData[2], 0x61);
    BOOST_CHECK_EQUAL(obj->compact.compactData[3], 0x7F);
    BOOST_CHECK_EQUAL(obj->compact.compactData[4], 0x1A);
    BOOST_CHECK_EQUAL(obj->compact.compactData[5], 0x78);
    BOOST_CHECK_EQUAL(obj->compact.compactData[6], 0x06);

    delete obj;

    file.close();
}
