#define BOOST_TEST_MODULE Most150PktFragment
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_150_PKT_FRAGMENT = 80 */
BOOST_AUTO_TEST_CASE(Most150PktFragment)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most150PktFragment.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_PKT_FRAGMENT);
    Vector::BLF::Most150PktFragment * obj = static_cast<Vector::BLF::Most150PktFragment *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_150_PKT_FRAGMENT);

    /* ObjectHeader2 */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedObjectHeader2, 0x33);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x4444444444444444);
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0x5555555555555555);

    /* Most150PktFragment */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->reservedMost150PktFragment1, 0x22);
    BOOST_CHECK_EQUAL(obj->ackNack, 0x33);
    BOOST_CHECK_EQUAL(obj->validMask, 0x44444444);
    BOOST_CHECK_EQUAL(obj->sourceAdr, 0x55555555);
    BOOST_CHECK_EQUAL(obj->destAdr, 0x66666666);
    BOOST_CHECK_EQUAL(obj->pAck, 0x77);
    BOOST_CHECK_EQUAL(obj->cAck, 0x88);
    BOOST_CHECK_EQUAL(obj->priority, 0x99);
    BOOST_CHECK_EQUAL(obj->pIndex, 0xAA);
    BOOST_CHECK_EQUAL(obj->crc, 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->dataLen, 0xCCCCCCCC);
    BOOST_CHECK_EQUAL(obj->dataLenAnnounced, 0xDDDDDDDD);
    BOOST_CHECK_EQUAL(obj->firstDataLen, 3);
    BOOST_CHECK_EQUAL(obj->reservedMost150PktFragment2, 0);
    BOOST_CHECK_EQUAL(obj->firstData[0], 4);
    BOOST_CHECK_EQUAL(obj->firstData[1], 5);
    BOOST_CHECK_EQUAL(obj->firstData[2], 6);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_PKT_FRAGMENT);

    delete ohb;

    file.close();
}
