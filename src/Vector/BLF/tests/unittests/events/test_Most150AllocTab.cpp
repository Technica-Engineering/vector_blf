#define BOOST_TEST_MODULE Most150AllocTab
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_150_ALLOCTAB = 83 */
BOOST_AUTO_TEST_CASE(Most150AllocTab)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most150AllocTab.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::Most150AllocTab * most150AllocTab;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    most150AllocTab = static_cast<Vector::BLF::Most150AllocTab *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150AllocTab->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150AllocTab->headerSize == most150AllocTab->calculateHeaderSize());
    BOOST_CHECK(most150AllocTab->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150AllocTab->objectSize == most150AllocTab->calculateObjectSize());
    BOOST_CHECK(most150AllocTab->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    /* ObjectHeader2 */
    BOOST_CHECK(most150AllocTab->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150AllocTab->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150AllocTab->objectVersion == 0);
    BOOST_CHECK(most150AllocTab->objectTimeStamp == 44814398000); // ns
    BOOST_CHECK(most150AllocTab->originalTimeStamp == 0);
    /* Most150AllocTab */
    BOOST_CHECK(most150AllocTab->channel == 1);
    BOOST_CHECK(most150AllocTab->eventModeFlags == 0);
    BOOST_CHECK(most150AllocTab->freeBytes == 0x2e);
    BOOST_CHECK(most150AllocTab->length == 8);
    BOOST_CHECK(most150AllocTab->tableData[0] == 0xc618);
    BOOST_CHECK(most150AllocTab->tableData[1] == 0x1937);
    BOOST_CHECK(most150AllocTab->tableData[2] == 0x0f98);
    BOOST_CHECK(most150AllocTab->tableData[3] == 0x0052);
    BOOST_CHECK(most150AllocTab->tableData[4] == 0x010b);
    BOOST_CHECK(most150AllocTab->tableData[5] == 0x0004);
    BOOST_CHECK(most150AllocTab->tableData[6] == 0x4151);
    BOOST_CHECK(most150AllocTab->tableData[7] == 0x0046);
    delete ohb;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    most150AllocTab = static_cast<Vector::BLF::Most150AllocTab *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(most150AllocTab->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(most150AllocTab->headerSize == most150AllocTab->calculateHeaderSize());
    BOOST_CHECK(most150AllocTab->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(most150AllocTab->objectSize == most150AllocTab->calculateObjectSize());
    BOOST_CHECK(most150AllocTab->objectType == Vector::BLF::ObjectType::MOST_150_ALLOCTAB);
    /* ObjectHeader2 */
    BOOST_CHECK(most150AllocTab->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(most150AllocTab->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(most150AllocTab->objectVersion == 0);
    BOOST_CHECK(most150AllocTab->objectTimeStamp == 50126855000); // ns
    BOOST_CHECK(most150AllocTab->originalTimeStamp == 0);
    /* Most150AllocTab */
    BOOST_CHECK(most150AllocTab->channel == 1);
    BOOST_CHECK(most150AllocTab->eventModeFlags == 0);
    BOOST_CHECK(most150AllocTab->freeBytes == 0x74);
    BOOST_CHECK(most150AllocTab->length == 8);
    BOOST_CHECK(most150AllocTab->tableData[0] == 0xc618);
    BOOST_CHECK(most150AllocTab->tableData[1] == 0x1937);
    BOOST_CHECK(most150AllocTab->tableData[2] == 0x346a);
    BOOST_CHECK(most150AllocTab->tableData[3] == 0x6d0d);
    BOOST_CHECK(most150AllocTab->tableData[4] == 0x010b);
    BOOST_CHECK(most150AllocTab->tableData[5] == 0x0004);
    BOOST_CHECK(most150AllocTab->tableData[6] == 0x8151);
    BOOST_CHECK(most150AllocTab->tableData[7] == 0x0046);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
