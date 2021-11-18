// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE Exceptions
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** trigger an exception and see if it throws */
BOOST_AUTO_TEST_CASE(Test) {
    Vector::BLF::Exception exception("Something happened.");
    BOOST_CHECK_EQUAL(exception.what(), "Something happened.");
    BOOST_CHECK_THROW(throw exception, Vector::BLF::Exception);
}
