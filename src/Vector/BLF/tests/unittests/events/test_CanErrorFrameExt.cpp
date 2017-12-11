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

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);
    Vector::BLF::CanErrorFrameExt * obj = static_cast<Vector::BLF::CanErrorFrameExt *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_ERROR_EXT);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1592186000);

    /* CanErrorFrameExt */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->length, 6);
    BOOST_CHECK_EQUAL(obj->flags, 1); // SJA 1000
    BOOST_CHECK_EQUAL(obj->ecc, 0xa2);
    BOOST_CHECK_EQUAL(obj->position, 0);
    BOOST_CHECK_EQUAL(obj->dlc, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->frameLengthInNs, 0);
    BOOST_CHECK_EQUAL(obj->id, 0xffffffff);
    BOOST_CHECK_EQUAL(obj->flagsExt, 0x20a2);
    // reserved
    //BOOST_CHECK_EQUAL(canErrorFrameExt->data[0], 0);

    delete obj;

    file.close();
}
