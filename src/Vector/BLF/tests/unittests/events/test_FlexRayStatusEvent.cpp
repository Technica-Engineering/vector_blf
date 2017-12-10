#define BOOST_TEST_MODULE FlexRayStatusEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* FLEXRAY_STATUS = 45 */
#if 0
BOOST_AUTO_TEST_CASE(FlexRayStatusEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_FlexRayStatusEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayStatusEvent * flexRayStatusEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_STATUS);
    flexRayStatusEvent = static_cast<Vector::BLF::FlexRayStatusEvent *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif
