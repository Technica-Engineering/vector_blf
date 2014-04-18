#define BOOST_TEST_MODULE Logfile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <boost/filesystem.hpp>

#include "Vector/BLF/File.h"

#define SUCCEEDED(code) ((int)(code) >= 0)
#define WARNED(code) ((int)(code) & 0x40000000)
#define FAILED(code) ((int)(code) < 0)

BOOST_AUTO_TEST_CASE(Logfile)
{
    Vector::BLF::File infile;
    Vector::BLF::File outfile;

    /* load database */
    boost::filesystem::path infile(CMAKE_CURRENT_SOURCE_DIR "/data/logfile.blf");
    std::string infilename = infile.string();
    infile.open(infilename);

    /* create output directory */
    boost::filesystem::path outdir(CMAKE_CURRENT_BINARY_DIR "/data/");
    if (!exists(outdir)) {
        BOOST_REQUIRE(create_directory(outdir));
    }

    /* save database */
    boost::filesystem::path outfile(CMAKE_CURRENT_BINARY_DIR "/data/logfile.blf");
    std::string outfilename = outfile.string();
    outfile.open(outfilename);

    /* go through all records */
    outfile.fileStatistics = infile.fileStatistics;
    while(!infile.eof()) {
        Vector::BLF::ObjectHeaderBase * obj = file.read();
        if (obj == nullptr)
            continue;

        outfile.write(obj);
    }

    /* loaded and saved file should be equivalent */
    std::ifstream ifs1(infile.c_str());
    std::ifstream ifs2(outfile.c_str());
    std::istream_iterator<char> b1(ifs1), e1;
    std::istream_iterator<char> b2(ifs2), e2;
    BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}
