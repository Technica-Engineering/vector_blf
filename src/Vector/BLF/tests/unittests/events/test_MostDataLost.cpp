#define BOOST_TEST_MODULE MostDataLost
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_DATALOST = 38 */
BOOST_AUTO_TEST_CASE(MostDataLost)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostDataLost.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_DATALOST);
    Vector::BLF::MostDataLost * obj = static_cast<Vector::BLF::MostDataLost *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_DATALOST);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 1303700000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* MostDataLost */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved
    BOOST_CHECK_EQUAL(obj->info, 0x05);
    BOOST_CHECK_EQUAL(obj->lostMsgsCtrl, 0x003F);
    BOOST_CHECK_EQUAL(obj->lostMsgsAsync, 0x000D);
    BOOST_CHECK_EQUAL(obj->lastGoodTimeStampNs, 101303690000); // ns
    BOOST_CHECK_EQUAL(obj->nextGoodTimeStampNs, 2223525920000); // ns

    delete obj;

    file.close();
}
