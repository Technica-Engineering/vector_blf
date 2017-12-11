#define BOOST_TEST_MODULE MostHwMode
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_HWMODE = 34 */
BOOST_AUTO_TEST_CASE(MostHwMode)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostHwMode.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_HWMODE);
    Vector::BLF::MostHwMode * obj = static_cast<Vector::BLF::MostHwMode *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_HWMODE);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 3560000000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* MostHwMode */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved
    BOOST_CHECK_EQUAL(obj->hwMode, 0x01); // active
    BOOST_CHECK_EQUAL(obj->hwModeMask, 0x01); // ByPass

    delete obj;

    file.close();
}
