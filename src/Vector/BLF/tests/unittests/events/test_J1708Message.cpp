#define BOOST_TEST_MODULE J1708Message
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* J1708_MESSAGE = 55 */
/* J1708_VIRTUAL_MSG = 56 */
#if 0
BOOST_AUTO_TEST_CASE(J1708Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_J1708Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::J1708Message * j1708Message;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::J1708_MESSAGE);
    j1708Message = static_cast<Vector::BLF::J1708Message *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
#endif
