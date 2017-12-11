#define BOOST_TEST_MODULE LinSyncError2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_SYN_ERROR2 = 59 */
BOOST_AUTO_TEST_CASE(LinSyncError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinSyncError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SYN_ERROR2);
    Vector::BLF::LinSyncError2 * obj = static_cast<Vector::BLF::LinSyncError2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_SYN_ERROR2);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 2022336000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 2021077000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 19230);
    BOOST_CHECK_EQUAL(obj->channel, 2);
    // reserved

    /* LinSynchFieldEvent */
    BOOST_CHECK_EQUAL(obj->synchBreakLength, 937125);
    BOOST_CHECK_EQUAL(obj->synchDelLength, 113312);

    /* LinSyncError2 */
    BOOST_CHECK_EQUAL(obj->timeDiff[0], 208);
    BOOST_CHECK_EQUAL(obj->timeDiff[1], 0);
    BOOST_CHECK_EQUAL(obj->timeDiff[2], 0);
    BOOST_CHECK_EQUAL(obj->timeDiff[3], 0);

    delete obj;

    file.close();
}
