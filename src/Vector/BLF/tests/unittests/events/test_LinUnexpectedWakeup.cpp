#define BOOST_TEST_MODULE LinUnexpectedWakeup
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_UNEXPECTED_WAKEUP = 87 */
BOOST_AUTO_TEST_CASE(LinUnexpectedWakeup)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinUnexpectedWakeup.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_UNEXPECTED_WAKEUP);
    Vector::BLF::LinUnexpectedWakeup * obj = static_cast<Vector::BLF::LinUnexpectedWakeup *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_UNEXPECTED_WAKEUP);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 0x1111111111111111);
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 0x22222222);
    BOOST_CHECK_EQUAL(obj->channel, 0x3333);
    BOOST_CHECK_EQUAL(obj->reservedLinBusEvent, 0x4444);

    /* LinUnexpectedWakeup */
    BOOST_CHECK_EQUAL(obj->width, 0x1111111111111111);
    BOOST_CHECK_EQUAL(obj->signal, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedLinUnexpectedWakeup1, 0x33);
    BOOST_CHECK_EQUAL(obj->reservedLinUnexpectedWakeup2, 0x3333);
    BOOST_CHECK_EQUAL(obj->reservedLinUnexpectedWakeup3, 0x33333333);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_UNEXPECTED_WAKEUP);

    delete ohb;

    file.close();
}
