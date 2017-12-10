#define BOOST_TEST_MODULE GlobalMarker
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* GLOBAL_MARKER = 96 */
BOOST_AUTO_TEST_CASE(GlobalMarker)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_GlobalMarker.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::GlobalMarker * globalMarker;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);
    globalMarker = static_cast<Vector::BLF::GlobalMarker *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(globalMarker->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(globalMarker->headerSize == globalMarker->calculateHeaderSize());
    BOOST_CHECK(globalMarker->headerVersion == 1);
    BOOST_CHECK(globalMarker->objectSize == globalMarker->calculateObjectSize());
    BOOST_CHECK(globalMarker->objectType == Vector::BLF::ObjectType::GLOBAL_MARKER);
    /* ObjectHeader */
    BOOST_CHECK(globalMarker->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(globalMarker->objectVersion == 0);
    BOOST_CHECK(globalMarker->objectTimeStamp == 2200804000); // ns
    /* GlobalMarker */
    BOOST_CHECK(globalMarker->commentedEventType == 0);
    BOOST_CHECK(globalMarker->foregroundColor == 0);
    BOOST_CHECK(globalMarker->backgroundColor == 16777215);
    BOOST_CHECK(globalMarker->isRelocatable == 1);
    // reserved
    BOOST_CHECK(globalMarker->groupNameLength == 0x83);
    BOOST_CHECK(globalMarker->markerNameLength == 0x83);
    BOOST_CHECK(globalMarker->descriptionLength == 0x105);
    BOOST_CHECK(globalMarker->groupName == "Marker Group");
    BOOST_CHECK(globalMarker->markerName == "[1]");
    BOOST_CHECK(globalMarker->description == "description");
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
