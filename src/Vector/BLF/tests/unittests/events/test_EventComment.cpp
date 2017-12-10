#define BOOST_TEST_MODULE EventComment
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* EVENT_COMMENT = 92 */
BOOST_AUTO_TEST_CASE(EventComment)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_EventComment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::EventComment * eventComment;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::EVENT_COMMENT);
    eventComment = static_cast<Vector::BLF::EventComment *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(eventComment->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(eventComment->headerSize == eventComment->calculateHeaderSize());
    BOOST_CHECK(eventComment->headerVersion == 1);
    BOOST_CHECK(eventComment->objectSize == eventComment->calculateObjectSize());
    BOOST_CHECK(eventComment->objectType == Vector::BLF::ObjectType::EVENT_COMMENT);
    /* ObjectHeader */
    BOOST_CHECK(eventComment->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(eventComment->objectVersion == 0);
    BOOST_CHECK(eventComment->objectTimeStamp == 1593770000); // ns
    /* EventComment */
    BOOST_CHECK(eventComment->commentedEventType == 105);
    BOOST_CHECK(eventComment->textLength == 261);
    BOOST_CHECK(eventComment->text == "testComment");
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
