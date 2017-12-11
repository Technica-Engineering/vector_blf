#define BOOST_TEST_MODULE MostGenReg
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_GENREG = 36 */
BOOST_AUTO_TEST_CASE(MostGenReg)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostGenReg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_GENREG);
    Vector::BLF::MostGenReg * obj = static_cast<Vector::BLF::MostGenReg *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_GENREG);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1471300000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* MostGenReg */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->subType, 1);
    // reserved
    BOOST_CHECK_EQUAL(obj->handle, 0);
    BOOST_CHECK_EQUAL(obj->regId, 0x8A);
    // reserved
    BOOST_CHECK_EQUAL(obj->regValue, 0x0172);

    delete obj;

    file.close();
}
