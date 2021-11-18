// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE ObjectQueue
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** insert and remove some elements and check state of queue */
BOOST_AUTO_TEST_CASE(SimpleTest) {
    Vector::BLF::ObjectQueue<Vector::BLF::ObjectHeaderBase> objectQueue;

    /* open queue and empty checks */
    BOOST_CHECK_EQUAL(objectQueue.tellg(), 0);
    BOOST_CHECK_EQUAL(objectQueue.tellp(), 0);
    BOOST_CHECK(!objectQueue.eof());

    /* add some objects */
    objectQueue.write(new Vector::BLF::CanMessage);
    objectQueue.write(new Vector::BLF::LinMessage);
    objectQueue.write(new Vector::BLF::J1708Message);
    BOOST_CHECK_EQUAL(objectQueue.tellg(), 0);
    BOOST_CHECK_EQUAL(objectQueue.tellp(), 3);
    BOOST_CHECK(!objectQueue.eof());

    /* check eof */
    objectQueue.setFileSize(3);
    BOOST_CHECK(!objectQueue.eof());

    /* remove some objects */
    Vector::BLF::ObjectHeaderBase * ohb;

    ohb = objectQueue.read();
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::CAN_MESSAGE);
    delete ohb;

    BOOST_CHECK_EQUAL(objectQueue.tellg(), 1);
    BOOST_CHECK(!objectQueue.eof());

    ohb = objectQueue.read();
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::LIN_MESSAGE);
    delete ohb;

    BOOST_CHECK_EQUAL(objectQueue.tellg(), 2);
    BOOST_CHECK(!objectQueue.eof());

    ohb = objectQueue.read();
    BOOST_CHECK(ohb->objectType == Vector::BLF::ObjectType::J1708_MESSAGE);
    delete ohb;

    BOOST_CHECK_EQUAL(objectQueue.tellg(), 3);
    BOOST_CHECK(!objectQueue.eof());

    /* remove one more to trigger eof */
    ohb = objectQueue.read();
    BOOST_CHECK(ohb == nullptr);
    BOOST_CHECK_EQUAL(objectQueue.tellg(), 3);
    BOOST_CHECK(objectQueue.eof());

    /* close */
    objectQueue.abort();

    /* check clear on open */
    objectQueue.write(new Vector::BLF::CanMessage);
    objectQueue.write(new Vector::BLF::LinMessage);
    objectQueue.write(new Vector::BLF::J1708Message);
}
