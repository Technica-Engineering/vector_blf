// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define BOOST_TEST_MODULE CompressedFile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** Test read operations on a blf file. */
BOOST_AUTO_TEST_CASE(ReadTest) {
    Vector::BLF::CompressedFile compressedFile;

    /* checks after initialize */
    BOOST_CHECK_EQUAL(compressedFile.gcount(), 0);
    BOOST_CHECK_EQUAL(compressedFile.tellg(), -1);
    BOOST_CHECK_EQUAL(compressedFile.tellp(), -1);
    BOOST_CHECK(!compressedFile.eof());
    BOOST_CHECK(!compressedFile.is_open());

    /* open file */
    compressedFile.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanMessage.blf", std::ios_base::in);
    BOOST_CHECK_EQUAL(compressedFile.tellg(), 0);
    BOOST_CHECK(compressedFile.is_open());

    /* read some data */
    char signature[5] = { 0, 0, 0, 0, 0 }; // including null termination
    compressedFile.read(signature, 4);
    BOOST_CHECK_EQUAL(signature, "LOGG");
    BOOST_CHECK_EQUAL(compressedFile.tellg(), 4);
    BOOST_CHECK_EQUAL(compressedFile.gcount(), 4);

    /* rewind to beginning of file */
    compressedFile.seekg(0, std::ios_base::beg);
    BOOST_CHECK_EQUAL(compressedFile.tellg(), 0);
    compressedFile.seekp(4);
    BOOST_CHECK_EQUAL(compressedFile.tellp(), 4);

    /* close file */
    compressedFile.close();
    BOOST_CHECK(!compressedFile.is_open());
}
