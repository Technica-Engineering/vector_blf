#define BOOST_TEST_MODULE CanDriverErrorExt
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_DRIVER_ERROR_EXT = 74 */
BOOST_AUTO_TEST_CASE(CanDriverErrorExt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanDriverErrorExt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanDriverErrorExt * canDriverErrorExt;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT);
    canDriverErrorExt = static_cast<Vector::BLF::CanDriverErrorExt *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
