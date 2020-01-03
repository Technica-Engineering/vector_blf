#define BOOST_TEST_MODULE SingleByteSerialEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

BOOST_AUTO_TEST_CASE(SimpleTest) {
    Vector::BLF::SingleByteSerialEvent obj;
    BOOST_CHECK_EQUAL(obj.calculateObjectSize(), 1);
}
