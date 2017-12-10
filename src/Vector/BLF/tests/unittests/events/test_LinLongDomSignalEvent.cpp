#define BOOST_TEST_MODULE LinLongDomSignalEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_LONG_DOM_SIG = 64 */
BOOST_AUTO_TEST_CASE(LinLongDomSignalEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinLongDomSignalEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinLongDomSignalEvent * linLongDomSignalEvent;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_LONG_DOM_SIG);
    linLongDomSignalEvent = static_cast<Vector::BLF::LinLongDomSignalEvent *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
