#define BOOST_TEST_MODULE CanDriverError
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_DRIVER_ERROR = 31 */
BOOST_AUTO_TEST_CASE(CanDriverError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanDriverError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanDriverError * canDriverError;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR);
    canDriverError = static_cast<Vector::BLF::CanDriverError *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(canDriverError->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(canDriverError->headerSize == canDriverError->calculateHeaderSize());
    BOOST_CHECK(canDriverError->headerVersion == 1);
    BOOST_CHECK(canDriverError->objectSize == canDriverError->calculateObjectSize());
    BOOST_CHECK(canDriverError->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR);
    /* ObjectHeader */
    BOOST_CHECK(canDriverError->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(canDriverError->objectVersion == 0);
    BOOST_CHECK(canDriverError->objectTimeStamp == 15282297); // ns
    /* CanDriverError */
    BOOST_CHECK(canDriverError->channel == 1);
    BOOST_CHECK(canDriverError->txErrors == 0);
    BOOST_CHECK(canDriverError->rxErrors == 0);
    BOOST_CHECK(canDriverError->errorCode == 0x68);
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
