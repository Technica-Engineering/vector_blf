#define BOOST_TEST_MODULE MostEcl
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_ECL = 95 */
BOOST_AUTO_TEST_CASE(MostEcl)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostEcl.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostEcl * mostEcl;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_ECL);
    mostEcl = static_cast<Vector::BLF::MostEcl *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(mostEcl->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(mostEcl->headerSize == mostEcl->calculateHeaderSize());
    BOOST_CHECK(mostEcl->headerVersion == 1);
    BOOST_CHECK(mostEcl->objectSize == mostEcl->calculateObjectSize());
    BOOST_CHECK(mostEcl->objectType == Vector::BLF::ObjectType::MOST_ECL);
    /* ObjectHeader2 */
    BOOST_CHECK(mostEcl->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK(mostEcl->timeStampStatus == 0);
    // reserved
    BOOST_CHECK(mostEcl->objectVersion == 0);
    BOOST_CHECK(mostEcl->objectTimeStamp == 9068000); // ns
    BOOST_CHECK(mostEcl->originalTimeStamp == 0);
    /* MostEcl */
    BOOST_CHECK(mostEcl->channel == 1);
    BOOST_CHECK(mostEcl->mode == 0); // discrete
    BOOST_CHECK(mostEcl->eclState == 1); // line high
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
