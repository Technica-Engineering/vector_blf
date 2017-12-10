#define BOOST_TEST_MODULE LinSyncError2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_SYN_ERROR2 = 59 */
BOOST_AUTO_TEST_CASE(LinSyncError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinSyncError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSyncError2 * linSyncError2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SYN_ERROR2);
    linSyncError2 = static_cast<Vector::BLF::LinSyncError2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSyncError2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSyncError2->headerSize == linSyncError2->calculateHeaderSize());
    BOOST_CHECK(linSyncError2->headerVersion == 1);
    BOOST_CHECK(linSyncError2->objectSize == linSyncError2->calculateObjectSize());
    BOOST_CHECK(linSyncError2->objectType == Vector::BLF::ObjectType::LIN_SYN_ERROR2);
    /* ObjectHeader */
    BOOST_CHECK(linSyncError2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linSyncError2->objectVersion == 0);
    BOOST_CHECK(linSyncError2->objectTimeStamp == 2022336000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linSyncError2->sof == 2021077000); // ns
    BOOST_CHECK(linSyncError2->eventBaudrate == 19230);
    BOOST_CHECK(linSyncError2->channel == 2);
    // reserved
    /* LinSynchFieldEvent */
    BOOST_CHECK(linSyncError2->synchBreakLength == 937125);
    BOOST_CHECK(linSyncError2->synchDelLength == 113312);
    /* LinSyncError2 */
    BOOST_CHECK(linSyncError2->timeDiff[0] == 208);
    BOOST_CHECK(linSyncError2->timeDiff[1] == 0);
    BOOST_CHECK(linSyncError2->timeDiff[2] == 0);
    BOOST_CHECK(linSyncError2->timeDiff[3] == 0);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
