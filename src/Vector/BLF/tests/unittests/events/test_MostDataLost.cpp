#define BOOST_TEST_MODULE MostDataLost
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_DATALOST = 38 */
BOOST_AUTO_TEST_CASE(MostDataLost)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostDataLost.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostDataLost * mostDataLost;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_DATALOST);
    mostDataLost = static_cast<Vector::BLF::MostDataLost *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostDataLost->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostDataLost->headerSize == mostDataLost->calculateHeaderSize());
    BOOST_CHECK(mostDataLost->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostDataLost->objectSize == mostDataLost->calculateObjectSize());
    BOOST_CHECK(mostDataLost->objectType == Vector::BLF::ObjectType::MOST_DATALOST);
    /* ObjectHeader2 */
    BOOST_CHECK(mostDataLost->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostDataLost->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostDataLost->objectVersion == 0);
    BOOST_CHECK(mostDataLost->objectTimeStamp == 1303700000); // ns
    BOOST_CHECK(mostDataLost->originalTimeStamp == 0);
    /* MostDataLost */
    BOOST_CHECK(mostDataLost->channel == 1);
    // reserved
    BOOST_CHECK(mostDataLost->info == 0x05);
    BOOST_CHECK(mostDataLost->lostMsgsCtrl == 0x003F);
    BOOST_CHECK(mostDataLost->lostMsgsAsync == 0x000D);
    BOOST_CHECK(mostDataLost->lastGoodTimeStampNs == 101303690000); // ns
    BOOST_CHECK(mostDataLost->nextGoodTimeStampNs == 2223525920000); // ns
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
