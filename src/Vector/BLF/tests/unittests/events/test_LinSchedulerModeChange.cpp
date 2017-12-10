#define BOOST_TEST_MODULE LinSchedulerModeChange
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_SCHED_MODCH = 17 */
BOOST_AUTO_TEST_CASE(LinSchedulerModeChange)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinSchedulerModeChange.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSchedulerModeChange * linSchedulerModeChange;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SCHED_MODCH);
    linSchedulerModeChange = static_cast<Vector::BLF::LinSchedulerModeChange *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSchedulerModeChange->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSchedulerModeChange->headerSize == linSchedulerModeChange->calculateHeaderSize());
    BOOST_CHECK(linSchedulerModeChange->headerVersion == 1);
    BOOST_CHECK(linSchedulerModeChange->objectSize == linSchedulerModeChange->calculateObjectSize());
    BOOST_CHECK(linSchedulerModeChange->objectType == Vector::BLF::ObjectType::LIN_SCHED_MODCH);
    /* ObjectHeader */
    BOOST_CHECK(linSchedulerModeChange->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(linSchedulerModeChange->objectVersion == 0);
    BOOST_CHECK(linSchedulerModeChange->objectTimeStamp == 100000000); // ns
    /* LinSchedulerModeChange */
    BOOST_CHECK(linSchedulerModeChange->channel == 1);
    BOOST_CHECK(linSchedulerModeChange->oldMode == 2);
    BOOST_CHECK(linSchedulerModeChange->newMode == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
