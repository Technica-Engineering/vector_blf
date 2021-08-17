// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE GeneralSerialEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

BOOST_AUTO_TEST_CASE(SimpleTest) {
    Vector::BLF::GeneralSerialEvent obj;
    BOOST_CHECK_EQUAL(obj.calculateObjectSize(), 0x10);
    obj.data.resize(32);
    BOOST_CHECK_EQUAL(obj.calculateObjectSize(), 0x10);
}
