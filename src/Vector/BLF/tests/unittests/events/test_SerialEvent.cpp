#define BOOST_TEST_MODULE SerialEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* SERIAL_EVENT = 90 */
BOOST_AUTO_TEST_CASE(SerialEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_SerialEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::SerialEvent * serialEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);
    serialEvent = static_cast<Vector::BLF::SerialEvent *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(serialEvent->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(serialEvent->headerSize == serialEvent->calculateHeaderSize());
    BOOST_CHECK(serialEvent->headerVersion == 1);
    BOOST_CHECK(serialEvent->objectSize == serialEvent->calculateObjectSize());
    BOOST_CHECK(serialEvent->objectType == Vector::BLF::ObjectType::SERIAL_EVENT);
    /* ObjectHeader */
    BOOST_CHECK(serialEvent->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(serialEvent->objectVersion == 0);
    BOOST_CHECK(serialEvent->objectTimeStamp == 12315000000); // ns
    /* SerialEvent */
    BOOST_CHECK(serialEvent->flags == ((uint32_t) (Vector::BLF::SerialEvent::Flags::KLineEvent) |
                                       (uint32_t) (Vector::BLF::SerialEvent::Flags::CompactByte)));
    BOOST_CHECK(serialEvent->port == 2);
    BOOST_CHECK(serialEvent->baudrate == 10400);
    // reserved
    BOOST_CHECK(serialEvent->compact.compactLength == 7);
    BOOST_CHECK(serialEvent->compact.compactData[0] == 0x83);
    BOOST_CHECK(serialEvent->compact.compactData[1] == 0x11);
    BOOST_CHECK(serialEvent->compact.compactData[2] == 0x61);
    BOOST_CHECK(serialEvent->compact.compactData[3] == 0x7F);
    BOOST_CHECK(serialEvent->compact.compactData[4] == 0x1A);
    BOOST_CHECK(serialEvent->compact.compactData[5] == 0x78);
    BOOST_CHECK(serialEvent->compact.compactData[6] == 0x06);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
