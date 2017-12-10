#define BOOST_TEST_MODULE CanErrorFrame
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_ERROR = 2 */
BOOST_AUTO_TEST_CASE(CanErrorFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanErrorFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanErrorFrame * canErrorFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR);
    canErrorFrame = static_cast<Vector::BLF::CanErrorFrame *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canErrorFrame->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canErrorFrame->headerSize == canErrorFrame->calculateHeaderSize());
    BOOST_CHECK(canErrorFrame->headerVersion == 1);
    BOOST_CHECK(canErrorFrame->objectSize == canErrorFrame->calculateObjectSize());
    BOOST_CHECK(canErrorFrame->objectType == Vector::BLF::ObjectType::CAN_ERROR);
    /* ObjectHeader */
    BOOST_CHECK(canErrorFrame->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canErrorFrame->objectVersion == 0);
    BOOST_CHECK(canErrorFrame->objectTimeStamp == 2501000000); // ns
    /* CanErrorFrame */
    BOOST_CHECK(canErrorFrame->channel == 1);
    BOOST_CHECK(canErrorFrame->length == 6);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
