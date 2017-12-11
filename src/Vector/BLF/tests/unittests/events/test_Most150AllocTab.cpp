#define BOOST_TEST_MODULE Most150AllocTab
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_150_ALLOCTAB = 83 */
BOOST_AUTO_TEST_CASE(Most150AllocTab)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most150AllocTab.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    Vector::BLF::Most150AllocTab * obj = static_cast<Vector::BLF::Most150AllocTab *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 44814398000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* Most150AllocTab */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->eventModeFlags, 0);
    BOOST_CHECK_EQUAL(obj->freeBytes, 0x2e);
    BOOST_CHECK_EQUAL(obj->length, 8);
    BOOST_CHECK_EQUAL(obj->tableData[0], 0xc618);
    BOOST_CHECK_EQUAL(obj->tableData[1], 0x1937);
    BOOST_CHECK_EQUAL(obj->tableData[2], 0x0f98);
    BOOST_CHECK_EQUAL(obj->tableData[3], 0x0052);
    BOOST_CHECK_EQUAL(obj->tableData[4], 0x010b);
    BOOST_CHECK_EQUAL(obj->tableData[5], 0x0004);
    BOOST_CHECK_EQUAL(obj->tableData[6], 0x4151);
    BOOST_CHECK_EQUAL(obj->tableData[7], 0x0046);

    delete obj;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    obj = static_cast<Vector::BLF::Most150AllocTab *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 50126855000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* Most150AllocTab */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->eventModeFlags, 0);
    BOOST_CHECK_EQUAL(obj->freeBytes, 0x74);
    BOOST_CHECK_EQUAL(obj->length, 8);
    BOOST_CHECK_EQUAL(obj->tableData[0], 0xc618);
    BOOST_CHECK_EQUAL(obj->tableData[1], 0x1937);
    BOOST_CHECK_EQUAL(obj->tableData[2], 0x346a);
    BOOST_CHECK_EQUAL(obj->tableData[3], 0x6d0d);
    BOOST_CHECK_EQUAL(obj->tableData[4], 0x010b);
    BOOST_CHECK_EQUAL(obj->tableData[5], 0x0004);
    BOOST_CHECK_EQUAL(obj->tableData[6], 0x8151);
    BOOST_CHECK_EQUAL(obj->tableData[7], 0x0046);

    delete obj;

    file.close();
}
