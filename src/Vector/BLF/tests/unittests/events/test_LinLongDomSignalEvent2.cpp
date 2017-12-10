#define BOOST_TEST_MODULE LinLongDomSignalEvent2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_LONG_DOM_SIG2 = 75 */
BOOST_AUTO_TEST_CASE(LinLongDomSignalEvent2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinLongDomSignalEvent2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinLongDomSignalEvent2 * linLongDomSignalEvent2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    linLongDomSignalEvent2 = static_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linLongDomSignalEvent2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linLongDomSignalEvent2->headerSize == linLongDomSignalEvent2->calculateHeaderSize());
    BOOST_CHECK(linLongDomSignalEvent2->headerVersion == 1);
    BOOST_CHECK(linLongDomSignalEvent2->objectSize == linLongDomSignalEvent2->calculateObjectSize());
    BOOST_CHECK(linLongDomSignalEvent2->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    /* ObjectHeader */
    BOOST_CHECK(linLongDomSignalEvent2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linLongDomSignalEvent2->objectVersion == 0);
    BOOST_CHECK(linLongDomSignalEvent2->objectTimeStamp == 8976802000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linLongDomSignalEvent2->sof == 8971798000); // ns
    BOOST_CHECK(linLongDomSignalEvent2->eventBaudrate == 9615);
    BOOST_CHECK(linLongDomSignalEvent2->channel == 1);
    // reserved
    /* LinLongDomSignalEvent2 */
    BOOST_CHECK(linLongDomSignalEvent2->type == 0); // Signal just detected
    // reserved
    BOOST_CHECK(linLongDomSignalEvent2->length == 5003000); // us
    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    linLongDomSignalEvent2 = static_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linLongDomSignalEvent2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linLongDomSignalEvent2->headerSize == linLongDomSignalEvent2->calculateHeaderSize());
    BOOST_CHECK(linLongDomSignalEvent2->headerVersion == 1);
    BOOST_CHECK(linLongDomSignalEvent2->objectSize == linLongDomSignalEvent2->calculateObjectSize());
    BOOST_CHECK(linLongDomSignalEvent2->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    /* ObjectHeader */
    BOOST_CHECK(linLongDomSignalEvent2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linLongDomSignalEvent2->objectVersion == 0);
    BOOST_CHECK(linLongDomSignalEvent2->objectTimeStamp == 8977000000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linLongDomSignalEvent2->sof == 8971798000); // ns
    BOOST_CHECK(linLongDomSignalEvent2->eventBaudrate == 9615);
    BOOST_CHECK(linLongDomSignalEvent2->channel == 1);
    // reserved
    /* LinLongDomSignalEvent2 */
    BOOST_CHECK(linLongDomSignalEvent2->type == 2); // Signal continuation
    // reserved
    BOOST_CHECK(linLongDomSignalEvent2->length == 5201000); // us
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
