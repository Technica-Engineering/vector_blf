#define BOOST_TEST_MODULE ObjectQueue
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** insert and remove some elements and check state of queue */
BOOST_AUTO_TEST_CASE(SimpleTest)
{
    Vector::BLF::ObjectQueue objectQueue;

    /* open queue and empty checks */
    objectQueue.open();
    BOOST_CHECK_EQUAL(objectQueue.tellg(), 0);
    BOOST_CHECK_EQUAL(objectQueue.tellp(), 0);
    BOOST_CHECK(!objectQueue.eof());
    BOOST_CHECK(!objectQueue.atEof());
    BOOST_CHECK_EQUAL(objectQueue.size(), 0);

    /* add some objects */
    objectQueue.write(new Vector::BLF::CanMessage);
    objectQueue.write(new Vector::BLF::LinMessage);
    objectQueue.write(new Vector::BLF::J1708Message);
    BOOST_CHECK_EQUAL(objectQueue.tellg(), 0);
    BOOST_CHECK_EQUAL(objectQueue.tellp(), 3);
    BOOST_CHECK(!objectQueue.eof());
    BOOST_CHECK(!objectQueue.atEof());
    BOOST_CHECK_EQUAL(objectQueue.size(), 3);

    /* check eof */
    objectQueue.setTotalObjectCount(3);
    BOOST_CHECK(!objectQueue.eof());
    BOOST_CHECK(!objectQueue.atEof());

    /* remove some objects */
    Vector::BLF::ObjectHeaderBase * ohb;

    ohb = objectQueue.read();
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    delete ohb;

    BOOST_CHECK_EQUAL(objectQueue.tellg(), 1);
    BOOST_CHECK_EQUAL(objectQueue.size(), 2);
    BOOST_CHECK(!objectQueue.eof());
    BOOST_CHECK(!objectQueue.atEof());

    ohb = objectQueue.read();
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE);
    delete ohb;

    BOOST_CHECK_EQUAL(objectQueue.tellg(), 2);
    BOOST_CHECK_EQUAL(objectQueue.size(), 1);
    BOOST_CHECK(!objectQueue.eof());
    BOOST_CHECK(!objectQueue.atEof());

    ohb = objectQueue.read();
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::J1708_MESSAGE);
    delete ohb;

    BOOST_CHECK_EQUAL(objectQueue.tellg(), 3);
    BOOST_CHECK_EQUAL(objectQueue.size(), 0);
    BOOST_CHECK(!objectQueue.eof());
    BOOST_CHECK(objectQueue.atEof()); // next read will result in eof

    /* remove one more to trigger eof */
    ohb = objectQueue.read();
    BOOST_CHECK(ohb == nullptr);
    BOOST_CHECK_EQUAL(objectQueue.tellg(), 3);
    BOOST_CHECK_EQUAL(objectQueue.size(), 0);
    BOOST_CHECK(objectQueue.eof());
    BOOST_CHECK(objectQueue.atEof());

    /* close */
    objectQueue.close();

    /* check clear on open */
    objectQueue.write(new Vector::BLF::CanMessage);
    objectQueue.write(new Vector::BLF::LinMessage);
    objectQueue.write(new Vector::BLF::J1708Message);
    BOOST_CHECK_EQUAL(objectQueue.size(), 3);
    objectQueue.open();
    BOOST_CHECK_EQUAL(objectQueue.size(), 0);
}
