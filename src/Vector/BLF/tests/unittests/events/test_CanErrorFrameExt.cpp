#define BOOST_TEST_MODULE CanErrorFrameExt
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_ERROR_EXT = 73 */
BOOST_AUTO_TEST_CASE(CanErrorFrameExt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanErrorFrameExt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanErrorFrameExt * canErrorFrameExt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);
    canErrorFrameExt = static_cast<Vector::BLF::CanErrorFrameExt *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canErrorFrameExt->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canErrorFrameExt->headerSize == canErrorFrameExt->calculateHeaderSize());
    BOOST_CHECK(canErrorFrameExt->headerVersion == 1);
    BOOST_CHECK(canErrorFrameExt->objectSize == canErrorFrameExt->calculateObjectSize());
    BOOST_CHECK(canErrorFrameExt->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);
    /* ObjectHeader */
    BOOST_CHECK(canErrorFrameExt->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(canErrorFrameExt->objectVersion == 0);
    BOOST_CHECK(canErrorFrameExt->objectTimeStamp == 1592186000); // ns
    /* CanErrorFrameExt */
    BOOST_CHECK(canErrorFrameExt->channel == 1);
    BOOST_CHECK(canErrorFrameExt->length == 6);
    BOOST_CHECK(canErrorFrameExt->flags == 1); // SJA 1000
    BOOST_CHECK(canErrorFrameExt->ecc == 0xa2);
    BOOST_CHECK(canErrorFrameExt->position == 0);
    BOOST_CHECK(canErrorFrameExt->dlc == 0);
    // reserved
    BOOST_CHECK(canErrorFrameExt->frameLengthInNs == 0);
    BOOST_CHECK(canErrorFrameExt->id == 0xffffffff);
    BOOST_CHECK(canErrorFrameExt->flagsExt == 0x20a2);
    // reserved
    //BOOST_CHECK(canErrorFrameExt->data[0] == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
