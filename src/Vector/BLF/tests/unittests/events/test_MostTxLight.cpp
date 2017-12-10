#define BOOST_TEST_MODULE MostTxLight
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_TXLIGHT = 68 */
BOOST_AUTO_TEST_CASE(MostTxLight)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostTxLight.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::MostTxLight * mostTxLight;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_TXLIGHT);
    mostTxLight = static_cast<Vector::BLF::MostTxLight *>(ohb);
    BOOST_CHECK(mostTxLight->channel == 1);
    BOOST_CHECK(mostTxLight->state == 1); // enable
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
