#define BOOST_TEST_MODULE LogContainer
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** just a simple test to have this class instantiated */
BOOST_AUTO_TEST_CASE(SimpleTest)
{
    Vector::BLF::LogContainer logContainer;

    logContainer.compressedFile.resize(0x00);
    BOOST_CHECK_EQUAL(logContainer.calculateObjectSize(), 0x20);

    logContainer.compressedFile.resize(0x10);
    BOOST_CHECK_EQUAL(logContainer.calculateObjectSize(), 0x30);
}
