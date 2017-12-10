#define BOOST_TEST_MODULE WlanFrame
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* WLAN_FRAME = 93 */
BOOST_AUTO_TEST_CASE(WlanFrame)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_WlanFrame.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::WlanFrame * wlanFrame;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::WLAN_FRAME);
    wlanFrame = static_cast<Vector::BLF::WlanFrame *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
