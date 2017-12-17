#define BOOST_TEST_MODULE MostSystemEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_SYSTEM_EVENT = 82 */
BOOST_AUTO_TEST_CASE(MostSystemEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostSystemEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_SYSTEM_EVENT);
    Vector::BLF::MostSystemEvent * obj = static_cast<Vector::BLF::MostSystemEvent *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_SYSTEM_EVENT);

    /* ObjectHeader2 */
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedObjectHeader2, 0x33);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x4444444444444444);
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0x5555555555555555);

    /* MostSystemEvent */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->id, 0x2222);
    BOOST_CHECK_EQUAL(obj->value, 0x33333333);
    BOOST_CHECK_EQUAL(obj->valueOld, 0x44444444);
    BOOST_CHECK_EQUAL(obj->reservedMostSystemEvent, 0);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_SYSTEM_EVENT);

    delete ohb;

    file.close();
}
