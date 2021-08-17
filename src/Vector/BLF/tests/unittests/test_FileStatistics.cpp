// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE FileStatistics
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** test throw on wrong file signature */
BOOST_AUTO_TEST_CASE(CorrectFileSignature) {
    /* open file and write in fileStatistics */
    Vector::BLF::UncompressedFile file;
    Vector::BLF::FileStatistics fileStatistics1;
    fileStatistics1.write(file);

    /* read fileStatistics */
    Vector::BLF::FileStatistics fileStatistics2;
    fileStatistics2.read(file);
}

/** test throw on wrong file signature */
BOOST_AUTO_TEST_CASE(WrongFileSignature) {
    /* open file and write in fileStatistics */
    Vector::BLF::UncompressedFile file;
    Vector::BLF::FileStatistics fileStatistics1;
    fileStatistics1.signature--;
    fileStatistics1.write(file);

    /* read fileStatistics */
    Vector::BLF::FileStatistics fileStatistics2;
    BOOST_CHECK_THROW(fileStatistics2.read(file), Vector::BLF::Exception);
}
