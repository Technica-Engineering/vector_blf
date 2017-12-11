#define BOOST_TEST_MODULE GlobalMarker
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* GLOBAL_MARKER = 96 */
BOOST_AUTO_TEST_CASE(GlobalMarker)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_GlobalMarker.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);
    Vector::BLF::GlobalMarker * obj = static_cast<Vector::BLF::GlobalMarker *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 2200804000); // ns

    /* GlobalMarker */
    BOOST_CHECK_EQUAL(obj->commentedEventType, 0);
    BOOST_CHECK_EQUAL(obj->foregroundColor, 0);
    BOOST_CHECK_EQUAL(obj->backgroundColor, 16777215);
    BOOST_CHECK_EQUAL(obj->isRelocatable, 1);
    // reserved
    BOOST_CHECK_EQUAL(obj->groupNameLength, 0x83);
    BOOST_CHECK_EQUAL(obj->markerNameLength, 0x83);
    BOOST_CHECK_EQUAL(obj->descriptionLength, 0x105);
    BOOST_CHECK_EQUAL(obj->groupName, "Marker Group");
    BOOST_CHECK_EQUAL(obj->markerName, "[1]");
    BOOST_CHECK_EQUAL(obj->description, "description");

    delete obj;

    file.close();
}
