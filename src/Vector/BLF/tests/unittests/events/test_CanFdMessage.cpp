#define BOOST_TEST_MODULE CanFdMessage
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* CAN_FD_MESSAGE = 100 */
BOOST_AUTO_TEST_CASE(CanFdMessage)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_CanFdMessage.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::CanFdMessage * canFdMessage;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_FD_MESSAGE);
    canFdMessage = static_cast<Vector::BLF::CanFdMessage *>(ohb);
    // @todo test implementation
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
