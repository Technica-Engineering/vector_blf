#define BOOST_TEST_MODULE LinUnexpectedWakeup
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_UNEXPECTED_WAKEUP = 87 */
BOOST_AUTO_TEST_CASE(LinUnexpectedWakeup)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinUnexpectedWakeup.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinUnexpectedWakeup * linUnexpectedWakeup;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_UNEXPECTED_WAKEUP);
    linUnexpectedWakeup = static_cast<Vector::BLF::LinUnexpectedWakeup *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linUnexpectedWakeup->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linUnexpectedWakeup->headerSize == linUnexpectedWakeup->calculateHeaderSize());
    BOOST_CHECK(linUnexpectedWakeup->headerVersion == 1);
    BOOST_CHECK(linUnexpectedWakeup->objectSize == linUnexpectedWakeup->calculateObjectSize());
    BOOST_CHECK(linUnexpectedWakeup->objectType == Vector::BLF::ObjectType::LIN_UNEXPECTED_WAKEUP);
    /* ObjectHeader */
    BOOST_CHECK(linUnexpectedWakeup->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linUnexpectedWakeup->objectVersion == 0);
    BOOST_CHECK(linUnexpectedWakeup->objectTimeStamp == 892363000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linUnexpectedWakeup->sof == 891843000); // ns
    BOOST_CHECK(linUnexpectedWakeup->eventBaudrate == 19230);
    BOOST_CHECK(linUnexpectedWakeup->channel == 1);
    // reserved
    /* LinUnexpectedWakeup */
    BOOST_CHECK(linUnexpectedWakeup->width == 260000); // us
    BOOST_CHECK(linUnexpectedWakeup->signal == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
