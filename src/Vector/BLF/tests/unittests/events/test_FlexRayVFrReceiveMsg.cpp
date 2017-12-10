#define BOOST_TEST_MODULE FlexRayVFrReceiveMsg
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* FR_RCVMESSAGE = 50 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRayVFrReceiveMsg)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_FlexRayVFrReceiveMsg.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayVFrReceiveMsg * flexRayVFrReceiveMsg;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FR_RCVMESSAGE);
    flexRayVFrReceiveMsg = static_cast<Vector::BLF::FlexRayVFrReceiveMsg *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif
