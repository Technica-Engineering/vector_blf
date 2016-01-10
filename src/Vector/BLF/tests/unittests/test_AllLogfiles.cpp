#define BOOST_TEST_MODULE AllLogfiles
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "Vector/BLF.h"

BOOST_AUTO_TEST_CASE(AllLogfiles)
{
    /* input directory */
    boost::filesystem::path indir(CMAKE_CURRENT_SOURCE_DIR "/data/");

    /* output directory */
    boost::filesystem::path outdir(CMAKE_CURRENT_BINARY_DIR "/data/");
    if (!exists(outdir)) {
        BOOST_REQUIRE(create_directory(outdir));
    }

    for(boost::filesystem::directory_entry & x : boost::filesystem::directory_iterator(indir))
    {
        //std::string eventFile = "CANSystem_A.blf";
        std::string eventFile = x.path().filename().string();
        std::cout << eventFile << std::endl;

        /* open input file */
        Vector::BLF::File filein;
        boost::filesystem::path infile(CMAKE_CURRENT_SOURCE_DIR "/data/" + eventFile);
        filein.open(infile.string(), Vector::BLF::File::OpenMode::Read);
        BOOST_REQUIRE(filein.is_open());

        /* open output file */
        Vector::BLF::File fileout;
        boost::filesystem::path outfile(CMAKE_CURRENT_BINARY_DIR "/data/" + eventFile);
        fileout.open(outfile.string(), Vector::BLF::File::OpenMode::Write);
        BOOST_REQUIRE(fileout.is_open());

        /* check filein statistics */
        BOOST_REQUIRE(filein.fileStatistics.signature == Vector::BLF::FileSignature);

        /* copy some filein to fileout statistics */
        fileout.fileStatistics.applicationId = filein.fileStatistics.applicationId;
        fileout.fileStatistics.applicationMajor = filein.fileStatistics.applicationMajor;
        fileout.fileStatistics.applicationMinor = filein.fileStatistics.applicationMinor;
        fileout.fileStatistics.applicationBuild = filein.fileStatistics.applicationBuild;
        fileout.fileStatistics.apiMajor = filein.fileStatistics.apiMajor;
        fileout.fileStatistics.apiMinor = filein.fileStatistics.apiMinor;
        fileout.fileStatistics.apiBuild = filein.fileStatistics.apiBuild;
        fileout.fileStatistics.apiPatch = filein.fileStatistics.apiPatch;
        // all others should be set on close

        while(!filein.eof()) {
            Vector::BLF::ObjectHeaderBase * ohb;
            ohb = filein.read();
            BOOST_CHECK((ohb != nullptr) || filein.eof());
            if (ohb != nullptr) {
                fileout.write(ohb);
                delete ohb;
            } else {
                break;
            }
        }

        /* close files */
        filein.close();
        fileout.close();

#if 0
        /* compare files */
        std::ifstream ifs1(infile.c_str());
        std::ifstream ifs2(outfile.c_str());
        std::istream_iterator<char> b1(ifs1), e1;
        std::istream_iterator<char> b2(ifs2), e2;
        BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
#endif
    }
}
