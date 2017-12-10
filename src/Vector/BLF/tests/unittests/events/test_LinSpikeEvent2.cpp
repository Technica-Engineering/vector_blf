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

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSpikeEvent2 * linSpikeEvent2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SPIKE_EVENT2);
    linSpikeEvent2 = static_cast<Vector::BLF::LinSpikeEvent2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSpikeEvent2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSpikeEvent2->headerSize == linSpikeEvent2->calculateHeaderSize());
    BOOST_CHECK(linSpikeEvent2->headerVersion == 1);
    BOOST_CHECK(linSpikeEvent2->objectSize == linSpikeEvent2->calculateObjectSize());
    BOOST_CHECK(linSpikeEvent2->objectType == Vector::BLF::ObjectType::LIN_SPIKE_EVENT2);
    /* ObjectHeader */
    BOOST_CHECK(linSpikeEvent2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linSpikeEvent2->objectVersion == 0);
    BOOST_CHECK(linSpikeEvent2->objectTimeStamp == 5990958000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linSpikeEvent2->sof == 5990902000); // ns
    BOOST_CHECK(linSpikeEvent2->eventBaudrate == 9615);
    BOOST_CHECK(linSpikeEvent2->channel == 2);
    /* LinSpikeEvent2 */
    BOOST_CHECK(linSpikeEvent2->width == 56);
    BOOST_CHECK(linSpikeEvent2->internal == 0); // real event
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
