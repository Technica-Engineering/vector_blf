#define BOOST_TEST_MODULE FlexRayV6StartCycleEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* FLEXRAY_CYCLE = 40 */
BOOST_AUTO_TEST_CASE(FlexRayV6StartCycleEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_FlexRayV6StartCycleEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::FlexRayV6StartCycleEvent * flexRayV6StartCycleEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_CYCLE);
    flexRayV6StartCycleEvent = static_cast<Vector::BLF::FlexRayV6StartCycleEvent *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
