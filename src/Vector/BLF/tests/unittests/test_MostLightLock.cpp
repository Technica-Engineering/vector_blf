#define BOOST_TEST_MODULE MostLightLock
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* MOST_LIGHTLOCK = 24 */
BOOST_AUTO_TEST_CASE(MostLightLock_1) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_MostLightLock.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);
    auto * obj = dynamic_cast<Vector::BLF::MostLightLock *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* MostLightLock */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->state, 0x2222);
    BOOST_CHECK_EQUAL(obj->reservedMostLightLock, 0);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);

    delete ohb;

    /* read last */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::Unknown115);

    delete ohb;

    /* read last */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::Unknown115);

    delete ohb;

    /* read eof */
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    file.close();
}

BOOST_AUTO_TEST_CASE(MostLightLock_2) {
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/test_MostLightLock.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);
    auto * obj = dynamic_cast<Vector::BLF::MostLightLock *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 8638000); // ns

    /* MostLightLock */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->state, 1); // Signal On + Lock
    // reserved

    delete ohb;

    /* read eof */
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    file.close();
}
