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

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    Vector::BLF::LinLongDomSignalEvent2 * obj = static_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 8976802000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 8971798000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 9615);
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved

    /* LinLongDomSignalEvent2 */
    BOOST_CHECK_EQUAL(obj->type, 0); // Signal just detected
    // reserved
    BOOST_CHECK_EQUAL(obj->length, 5003000); // us

    delete obj;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);
    obj = static_cast<Vector::BLF::LinLongDomSignalEvent2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG2);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 8977000000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 8971798000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 9615);
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved

    /* LinLongDomSignalEvent2 */
    BOOST_CHECK_EQUAL(obj->type, 2); // Signal continuation
    // reserved
    BOOST_CHECK_EQUAL(obj->length, 5201000); // us

    delete obj;

    file.close();
}
