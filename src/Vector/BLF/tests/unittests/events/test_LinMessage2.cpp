#define BOOST_TEST_MODULE LinMessage2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_MESSAGE2 = 57 */
BOOST_AUTO_TEST_CASE(LinMessage2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinMessage2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);
    Vector::BLF::LinMessage2 * obj = static_cast<Vector::BLF::LinMessage2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_MESSAGE2);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 73973000); // ns

    /* LinMessage2 */
    BOOST_CHECK_EQUAL(obj->data[0], 0x00);
    BOOST_CHECK_EQUAL(obj->data[1], 0xf0);
    BOOST_CHECK_EQUAL(obj->data[2], 0xf0);
    BOOST_CHECK_EQUAL(obj->data[3], 0xff);
    BOOST_CHECK_EQUAL(obj->data[4], 0xff);
    BOOST_CHECK_EQUAL(obj->data[5], 0xff);
    BOOST_CHECK_EQUAL(obj->data[6], 0xff);
    BOOST_CHECK_EQUAL(obj->data[7], 0xff);
    BOOST_CHECK_EQUAL(obj->crc, 0x70);
    BOOST_CHECK_EQUAL(obj->dir, 1); // Tx
    BOOST_CHECK_EQUAL(obj->simulated, 1);
    BOOST_CHECK_EQUAL(obj->isEtf, 0);
    BOOST_CHECK_EQUAL(obj->etfAssocIndex, 0);
    BOOST_CHECK_EQUAL(obj->etfAssocEtfId, 0xff);
    BOOST_CHECK_EQUAL(obj->fsmId, 0xff);
    BOOST_CHECK_EQUAL(obj->fsmState, 0xff);
    // reserved
    BOOST_CHECK_EQUAL(obj->respBaudrate, 19231);
    BOOST_CHECK_EQUAL(obj->exactHeaderBaudrate, 19230.769231);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffset, 26000);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffsetResponse, 26000);

    delete obj;

    file.close();
}
