#define BOOST_TEST_MODULE CanFdErrorFrame64
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_FD_ERROR_64 = 104 */
BOOST_AUTO_TEST_CASE(CanFdErrorFrame64)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanFdErrorFrame64.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanFdErrorFrame64 * canFdErrorFrame64;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_ERROR_64);
    canFdErrorFrame64 = static_cast<Vector::BLF::CanFdErrorFrame64 *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
