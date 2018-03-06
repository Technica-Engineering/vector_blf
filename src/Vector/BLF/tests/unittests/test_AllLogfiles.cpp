#define BOOST_TEST_MODULE AllLogfiles
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iterator>
#include <string>

#include <Vector/BLF.h>

/** copy file statistics */
static void copyFileStatistics(Vector::BLF::File & filein, Vector::BLF::File & fileout)
{
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
}

/** copy objects and close files */
static void copyObjects(Vector::BLF::File & filein, Vector::BLF::File & fileout)
{
    /* read all objects from input file */
    Vector::BLF::ObjectQueue<Vector::BLF::ObjectHeaderBase> objectQueue;
    while (!filein.eof()) {
        Vector::BLF::ObjectHeaderBase * ohb = filein.read();
        if (ohb == nullptr) {
            break;
        }
        if (ohb->objectType != Vector::BLF::ObjectType::Unknown115) {
            objectQueue.write(ohb);
        }
    }
    filein.close();

    /* write all objects into output file */
    objectQueue.setFileSize(objectQueue.tellp());
    while (!objectQueue.eof()) {
        Vector::BLF::ObjectHeaderBase * ohb = objectQueue.read();
        if (ohb != nullptr) {
            fileout.write(ohb);
        }
    }
    fileout.close();
}

/** compare files */
static bool compareFiles(const char * infileName, const char * outfileName, uint64_t fileSizeWithoutUnknown115)
{
    std::ifstream ifs1;
    std::ifstream ifs2;
    ifs1.open(infileName);
    BOOST_REQUIRE(ifs1.is_open());
    ifs2.open(outfileName);
    BOOST_REQUIRE(ifs2.is_open());
    bool sameFile = true;
    while (ifs1.good() && ifs2.good() &&
            ((fileSizeWithoutUnknown115 == 0) || (static_cast<uint64_t>(ifs1.tellg()) < fileSizeWithoutUnknown115))) {
        char c1 = static_cast<char>(ifs1.get());
        char c2 = static_cast<char>(ifs2.get());
        if (c1 != c2) {
            sameFile = false;
            break;
        }
    }
    ifs1.close();
    BOOST_REQUIRE(!ifs1.is_open());
    ifs2.close();
    BOOST_REQUIRE(!ifs2.is_open());
    return sameFile;
}

/** Test with uncompressedFiles with Unknown115 ending */
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

        /* copy file statistics */
        copyFileStatistics(filein, fileout);

        /* copy objects */
        copyObjects(filein, fileout);

        /* compare files */
        BOOST_REQUIRE_MESSAGE(
            compareFiles(infile.c_str(), outfile.c_str(), fileout.fileStatistics.fileSizeWithoutUnknown115),
            eventFile + " is different");
    }
}

/** Test with compressedFiles without Unknown115 ending */
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

        /* copy file statistics */
        copyFileStatistics(filein, fileout);

        /* copy objects */
        copyObjects(filein, fileout);

        // Vector bug: sizeof(EventComment) + ...
        if (eventFile == "test_GlobalMarker.blf") {
            continue;
        }

        /* compare files */
        BOOST_CHECK_MESSAGE(
            compareFiles(infile.c_str(), outfile.c_str(), fileout.fileStatistics.fileSizeWithoutUnknown115),
            eventFile + " is different");
    }
}
