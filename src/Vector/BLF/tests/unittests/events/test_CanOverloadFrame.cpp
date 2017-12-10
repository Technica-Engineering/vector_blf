#define BOOST_TEST_MODULE CanOverloadFrame
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_OVERLOAD = 3 */
#if 0
BOOST_AUTO_TEST_CASE(CanOverloadFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanOverloadFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanOverloadFrame * canOverloadFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_OVERLOAD);
    canOverloadFrame = static_cast<Vector::BLF::CanOverloadFrame *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif
