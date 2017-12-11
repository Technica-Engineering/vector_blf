#define BOOST_TEST_MODULE MostStress
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_STRESS = 70 */
BOOST_AUTO_TEST_CASE(MostStress)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostStress.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_STRESS);
    Vector::BLF::MostStress * obj = static_cast<Vector::BLF::MostStress *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_STRESS);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1793083000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* MostStress */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->state, 1); // started
    BOOST_CHECK_EQUAL(obj->mode, 2); // Lock
    // reserved

    delete obj;

    file.close();
}
