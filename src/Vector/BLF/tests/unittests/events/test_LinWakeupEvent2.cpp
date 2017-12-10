#define BOOST_TEST_MODULE LinWakeupEvent2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_WAKEUP2 = 62 */
BOOST_AUTO_TEST_CASE(LinWakeupEvent2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinWakeupEvent2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinWakeupEvent2 * linWakeupEvent2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_WAKEUP2);
    linWakeupEvent2 = static_cast<Vector::BLF::LinWakeupEvent2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linWakeupEvent2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linWakeupEvent2->headerSize == linWakeupEvent2->calculateHeaderSize());
    BOOST_CHECK(linWakeupEvent2->headerVersion == 1);
    BOOST_CHECK(linWakeupEvent2->objectSize == linWakeupEvent2->calculateObjectSize());
    BOOST_CHECK(linWakeupEvent2->objectType == Vector::BLF::ObjectType::LIN_WAKEUP2);
    /* ObjectHeader */
    BOOST_CHECK(linWakeupEvent2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linWakeupEvent2->objectVersion == 0);
    BOOST_CHECK(linWakeupEvent2->objectTimeStamp == 2318672000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linWakeupEvent2->sof == 2317671000); // ns
    BOOST_CHECK(linWakeupEvent2->eventBaudrate == 19230);
    BOOST_CHECK(linWakeupEvent2->channel == 1);
    // reserved
    /* LinWakeupEvent2 */
    BOOST_CHECK(linWakeupEvent2->lengthInfo == 0); // OK
    BOOST_CHECK(linWakeupEvent2->signal == 0);
    BOOST_CHECK(linWakeupEvent2->external == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
