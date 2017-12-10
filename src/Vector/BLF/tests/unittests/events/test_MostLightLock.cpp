#define BOOST_TEST_MODULE MostLightLock
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_LIGHTLOCK = 24 */
BOOST_AUTO_TEST_CASE(MostLightLock)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostLightLock.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostLightLock * mostLightLock;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);
    mostLightLock = static_cast<Vector::BLF::MostLightLock *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostLightLock->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostLightLock->headerSize == mostLightLock->calculateHeaderSize());
    BOOST_CHECK(mostLightLock->headerVersion == 1);
    BOOST_CHECK(mostLightLock->objectSize == mostLightLock->calculateObjectSize());
    BOOST_CHECK(mostLightLock->objectType == Vector::BLF::ObjectType::MOST_LIGHTLOCK);
    /* ObjectHeader */
    BOOST_CHECK(mostLightLock->objectFlags == Vector::BLF::ObjectHeader::TimeOneNans);
    // reserved
    BOOST_CHECK(mostLightLock->objectVersion == 0);
    BOOST_CHECK(mostLightLock->objectTimeStamp == 8638000); // ns
    /* MostLightLock */
    BOOST_CHECK(mostLightLock->channel == 1);
    BOOST_CHECK(mostLightLock->state == 1); // Signal On + Lock
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
