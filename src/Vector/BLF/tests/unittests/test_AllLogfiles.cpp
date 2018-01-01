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

#include <Vector/BLF.h>

BOOST_AUTO_TEST_CASE(AllBinlogLogfiles)
{
    /* input directory */
    boost::filesystem::path indir(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/");

    /* output directory */
    boost::filesystem::path outdir(CMAKE_CURRENT_BINARY_DIR "/events_from_binlog/");
    if (!exists(outdir)) {
        BOOST_REQUIRE(create_directory(outdir));
    }

    /* loop over all blfs */
    for (boost::filesystem::directory_entry & x : boost::filesystem::directory_iterator(indir)) {
        if (!boost::filesystem::is_regular_file(x)) {
            continue;
        }
        std::string eventFile = x.path().filename().string();
        std::cout << eventFile << std::endl;

        /* open input file */
        Vector::BLF::File filein;
        boost::filesystem::path infile(indir.string() + eventFile);
        filein.open(infile.string(), std::ios_base::in);
        BOOST_REQUIRE(filein.is_open());

        /* open output file */
        Vector::BLF::File fileout;
        fileout.compressionLevel = 0;
        boost::filesystem::path outfile(outdir.string() + eventFile);
        fileout.open(outfile.string(), std::ios_base::out);
        BOOST_REQUIRE(fileout.is_open());

        /* check filein statistics */
        BOOST_REQUIRE_EQUAL(filein.fileStatistics.signature, Vector::BLF::FileSignature);

        /* copy non-generated filein statistics to fileout statistics */
        fileout.fileStatistics.applicationId = filein.fileStatistics.applicationId;
        fileout.fileStatistics.applicationMajor = filein.fileStatistics.applicationMajor;
        fileout.fileStatistics.applicationMinor = filein.fileStatistics.applicationMinor;
        fileout.fileStatistics.applicationBuild = filein.fileStatistics.applicationBuild;
        fileout.fileStatistics.apiMajor = filein.fileStatistics.apiMajor;
        fileout.fileStatistics.apiMinor = filein.fileStatistics.apiMinor;
        fileout.fileStatistics.apiBuild = filein.fileStatistics.apiBuild;
        fileout.fileStatistics.apiPatch = filein.fileStatistics.apiPatch;
        fileout.fileStatistics.objectsRead = filein.fileStatistics.objectsRead;
        // all others should be set on close

        while (!filein.eof()) {
            Vector::BLF::ObjectHeaderBase * ohb;
            ohb = filein.read();
            BOOST_REQUIRE(ohb != nullptr);
            if (ohb->objectType != Vector::BLF::ObjectType::Unknown115) {
                fileout.write(ohb);
            }
            delete ohb;
        }

        /* close files */
        filein.close();
        fileout.close();

        /* compare files */
        // @todo Compare complete file as soon as fields in Unknown115 are understood.
        std::ifstream ifs1;
        std::ifstream ifs2;
        ifs1.open(infile.c_str());
        BOOST_REQUIRE(ifs1.is_open());
        ifs2.open(outfile.c_str());
        BOOST_REQUIRE(ifs2.is_open());
        char c1 = static_cast<char>(ifs1.get());
        char c2 = static_cast<char>(ifs2.get());
        bool sameFile = true;
        while (ifs1.good() && ifs2.good() && (static_cast<uint64_t>(ifs1.tellg()) <= fileout.fileStatistics.fileSizeWithoutUnknown115)) {
            sameFile &= (c1 == c2);
            c1 = static_cast<char>(ifs1.get());
            c2 = static_cast<char>(ifs2.get());
        }
        ifs1.close();
        ifs2.close();
        BOOST_CHECK(sameFile);
    }
}

BOOST_AUTO_TEST_CASE(AllConvertedLogfiles)
{
    /* input directory */
    boost::filesystem::path indir(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/");

    /* output directory */
    boost::filesystem::path outdir(CMAKE_CURRENT_BINARY_DIR "/events_from_converter/");
    if (!exists(outdir)) {
        BOOST_REQUIRE(create_directory(outdir));
    }

    /* loop over all blfs */
    for (boost::filesystem::directory_entry & x : boost::filesystem::directory_iterator(indir)) {
        if (!boost::filesystem::is_regular_file(x)) {
            continue;
        }
        std::string eventFile = x.path().filename().string();
        std::cout << eventFile << std::endl;

        /* open input file */
        Vector::BLF::File filein;
        boost::filesystem::path infile(indir.string() + eventFile);
        filein.open(infile.string(), std::ios_base::in);
        BOOST_REQUIRE(filein.is_open());

        /* open output file */
        Vector::BLF::File fileout;
        fileout.writeUnknown115 = false;
        boost::filesystem::path outfile(outdir.string() + eventFile);
        fileout.open(outfile.string(), std::ios_base::out);
        BOOST_REQUIRE(fileout.is_open());

        /* check filein statistics */
        BOOST_REQUIRE_EQUAL(filein.fileStatistics.signature, Vector::BLF::FileSignature);

        /* copy non-generated filein statistics to fileout statistics */
        fileout.fileStatistics.applicationId = filein.fileStatistics.applicationId;
        fileout.fileStatistics.applicationMajor = filein.fileStatistics.applicationMajor;
        fileout.fileStatistics.applicationMinor = filein.fileStatistics.applicationMinor;
        fileout.fileStatistics.applicationBuild = filein.fileStatistics.applicationBuild;
        fileout.fileStatistics.apiMajor = filein.fileStatistics.apiMajor;
        fileout.fileStatistics.apiMinor = filein.fileStatistics.apiMinor;
        fileout.fileStatistics.apiBuild = filein.fileStatistics.apiBuild;
        fileout.fileStatistics.apiPatch = filein.fileStatistics.apiPatch;
        fileout.fileStatistics.objectsRead = filein.fileStatistics.objectsRead;
        // all others should be set on close

        while (!filein.eof()) {
            Vector::BLF::ObjectHeaderBase * ohb;
            ohb = filein.read();
            BOOST_REQUIRE(ohb != nullptr);
            if (ohb->objectType != Vector::BLF::ObjectType::Unknown115) {
                fileout.write(ohb);
            }
            delete ohb;
        }

        /* close files */
        filein.close();
        fileout.close();

        /* compare files */
        // @todo Compare complete file as soon as fields in Unknown115 are understood.
        std::ifstream ifs1;
        std::ifstream ifs2;
        ifs1.open(infile.c_str());
        BOOST_REQUIRE(ifs1.is_open());
        ifs2.open(outfile.c_str());
        BOOST_REQUIRE(ifs2.is_open());
        char c1 = static_cast<char>(ifs1.get());
        char c2 = static_cast<char>(ifs2.get());
        bool sameFile = true;
        while (ifs1.good() && ifs2.good() && (static_cast<uint64_t>(ifs1.tellg()) <= fileout.fileStatistics.fileSizeWithoutUnknown115)) {
            sameFile &= (c1 == c2);
            c1 = static_cast<char>(ifs1.get());
            c2 = static_cast<char>(ifs2.get());
        }
        ifs1.close();
        ifs2.close();
        BOOST_CHECK(sameFile);
    }
}
