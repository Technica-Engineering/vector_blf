#define BOOST_TEST_MODULE MostReg
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_REG = 35 */
BOOST_AUTO_TEST_CASE(MostReg)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostReg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_REG);
    Vector::BLF::MostReg * obj = static_cast<Vector::BLF::MostReg *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_REG);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedObjectHeader2, 0x33);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x4444444444444444);
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0x5555555555555555);

    /* MostReg */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->subType, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedMostReg, 0x33);
    BOOST_CHECK_EQUAL(obj->handle, 0x44444444);
    BOOST_CHECK_EQUAL(obj->offset, 0x55555555);
    BOOST_CHECK_EQUAL(obj->chip, 0x6666);
    BOOST_CHECK_EQUAL(obj->regDataLen, 0x7777);
    for (uint8_t i = 0; i < 16; i++) {
        BOOST_CHECK_EQUAL(obj->regData[i], i);
    }

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_REG);

    delete ohb;

    file.close();
}
