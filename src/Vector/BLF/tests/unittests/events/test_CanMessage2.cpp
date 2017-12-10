#define BOOST_TEST_MODULE CanMessage2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_MESSAGE2 = 86 */
BOOST_AUTO_TEST_CASE(CanMessage2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanMessage2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanMessage2 * canMessage2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE2);
    canMessage2 = static_cast<Vector::BLF::CanMessage2 *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
