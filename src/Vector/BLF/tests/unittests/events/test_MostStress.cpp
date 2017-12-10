#define BOOST_TEST_MODULE MostStress
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_STRESS = 70 */
BOOST_AUTO_TEST_CASE(MostStress)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostStress.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostStress * mostStress;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_STRESS);
    mostStress = static_cast<Vector::BLF::MostStress *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostStress->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostStress->headerSize == mostStress->calculateHeaderSize());
    BOOST_CHECK(mostStress->headerVersion == 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK(mostStress->objectSize == mostStress->calculateObjectSize());
    BOOST_CHECK(mostStress->objectType == Vector::BLF::ObjectType::MOST_STRESS);
    /* ObjectHeader2 */
    BOOST_CHECK(mostStress->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostStress->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostStress->objectVersion == 0);
    BOOST_CHECK(mostStress->objectTimeStamp == 1793083000); // ns
    BOOST_CHECK(mostStress->originalTimeStamp == 0);
    /* MostStress */
    BOOST_CHECK(mostStress->channel == 1);
    BOOST_CHECK(mostStress->state == 1); // started
    BOOST_CHECK(mostStress->mode == 2); // Lock
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
