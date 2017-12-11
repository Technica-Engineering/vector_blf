#define BOOST_TEST_MODULE LinSpikeEvent2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_SPIKE_EVENT2 = 63 */
BOOST_AUTO_TEST_CASE(LinSpikeEvent2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinSpikeEvent2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SPIKE_EVENT2);
    Vector::BLF::LinSpikeEvent2 * obj = static_cast<Vector::BLF::LinSpikeEvent2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_SPIKE_EVENT2);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 5990958000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 5990902000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 9615);
    BOOST_CHECK_EQUAL(obj->channel, 2);

    /* LinSpikeEvent2 */
    BOOST_CHECK_EQUAL(obj->width, 56);
    BOOST_CHECK_EQUAL(obj->internal, 0); // real event
    // reserved

    delete obj;

    file.close();
}
