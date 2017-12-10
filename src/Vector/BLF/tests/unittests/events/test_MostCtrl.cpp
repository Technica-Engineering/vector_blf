#define BOOST_TEST_MODULE MostCtrl
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_CTRL = 23 */
BOOST_AUTO_TEST_CASE(MostCtrl)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostCtrl.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostCtrl * mostCtrl;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_CTRL);
    mostCtrl = static_cast<Vector::BLF::MostCtrl *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostCtrl->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostCtrl->headerSize == mostCtrl->calculateHeaderSize());
    BOOST_CHECK(mostCtrl->headerVersion == 1);
    BOOST_CHECK(mostCtrl->objectSize == mostCtrl->calculateObjectSize());
    BOOST_CHECK(mostCtrl->objectType == Vector::BLF::ObjectType::MOST_CTRL);
    /* ObjectHeader */
    BOOST_CHECK(mostCtrl->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(mostCtrl->objectVersion == 0);
    BOOST_CHECK(mostCtrl->objectTimeStamp == 111757000); // ns
    /* MostCtrl */
    BOOST_CHECK(mostCtrl->channel == 1);
    BOOST_CHECK(mostCtrl->dir == 1); // Tx
    // reserved
    BOOST_CHECK(mostCtrl->sourceAdr == 0x0100);
    BOOST_CHECK(mostCtrl->destAdr == 0x0401);
    BOOST_CHECK(mostCtrl->msg[ 0] == 0x01);
    BOOST_CHECK(mostCtrl->msg[ 1] == 0x01);
    BOOST_CHECK(mostCtrl->msg[ 2] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 3] == 0x01);
    BOOST_CHECK(mostCtrl->msg[ 4] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 5] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 6] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 7] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 8] == 0x00);
    BOOST_CHECK(mostCtrl->msg[ 9] == 0x00);
    BOOST_CHECK(mostCtrl->msg[10] == 0x00);
    BOOST_CHECK(mostCtrl->msg[11] == 0x00);
    BOOST_CHECK(mostCtrl->msg[12] == 0x00);
    BOOST_CHECK(mostCtrl->msg[13] == 0x00);
    BOOST_CHECK(mostCtrl->msg[14] == 0x00);
    BOOST_CHECK(mostCtrl->msg[15] == 0x00);
    BOOST_CHECK(mostCtrl->msg[16] == 0x00);
    // reserved
    BOOST_CHECK(mostCtrl->rTyp == 0); // Normal
    BOOST_CHECK(mostCtrl->rTypAdr == 0); // Device
    BOOST_CHECK(mostCtrl->state == 0x50); // TxF|Ack
    // reserved
    BOOST_CHECK(mostCtrl->ackNack == 0x12); // NoResp|NAck
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
