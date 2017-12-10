#define BOOST_TEST_MODULE LinSlaveTimeout
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_SLV_TIMEOUT = 16 */
BOOST_AUTO_TEST_CASE(LinSlaveTimeout)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinSlaveTimeout.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSlaveTimeout * linSlaveTimeout;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SLV_TIMEOUT);
    linSlaveTimeout = static_cast<Vector::BLF::LinSlaveTimeout *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSlaveTimeout->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSlaveTimeout->headerSize == linSlaveTimeout->calculateHeaderSize());
    BOOST_CHECK(linSlaveTimeout->headerVersion == 1);
    BOOST_CHECK(linSlaveTimeout->objectSize == linSlaveTimeout->calculateObjectSize());
    BOOST_CHECK(linSlaveTimeout->objectType == Vector::BLF::ObjectType::LIN_SLV_TIMEOUT);
    /* ObjectHeader */
    BOOST_CHECK(linSlaveTimeout->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linSlaveTimeout->objectVersion == 0);
    BOOST_CHECK(linSlaveTimeout->objectTimeStamp == 1001200000); // ns
    /* LinDlcInfo */
    BOOST_CHECK(linSlaveTimeout->channel == 1);
    BOOST_CHECK(linSlaveTimeout->slaveId == 0);
    BOOST_CHECK(linSlaveTimeout->stateId == 0);
    BOOST_CHECK(linSlaveTimeout->followStateId == 1);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
