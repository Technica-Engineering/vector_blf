#define BOOST_TEST_MODULE AllLogfiles
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <Vector/BLF.h>

/** copy file statistics */
static void copyFileStatistics(Vector::BLF::File & filein, Vector::BLF::File & fileout) {
    /* copy non-generated filein statistics to fileout statistics */
    Vector::BLF::FileStatistics fileStatisticsIn;
    fileStatisticsIn = filein.statistics();
    Vector::BLF::FileStatistics fileStatisticsOut;
    fileStatisticsOut.applicationId = fileStatisticsIn.applicationId;
    fileStatisticsOut.applicationMajor = fileStatisticsIn.applicationMajor;
    fileStatisticsOut.applicationMinor = fileStatisticsIn.applicationMinor;
    fileStatisticsOut.applicationBuild = fileStatisticsIn.applicationBuild;
    fileStatisticsOut.apiMajor = fileStatisticsIn.apiMajor;
    fileStatisticsOut.apiMinor = fileStatisticsIn.apiMinor;
    fileStatisticsOut.apiBuild = fileStatisticsIn.apiBuild;
    fileStatisticsOut.apiPatch = fileStatisticsIn.apiPatch;
    fileStatisticsOut.objectsRead = fileStatisticsIn.objectsRead;
    // @todo fileout.setStatistics(fileStatisticsOut);
    fileout.setApplication(
                fileStatisticsIn.applicationId,
                fileStatisticsIn.applicationMajor,
                fileStatisticsIn.applicationMinor,
                fileStatisticsIn.applicationBuild);
    // all others should be set on close
}

/** copy objects and close files */
static void copyObjects(Vector::BLF::File & filein, Vector::BLF::File & fileout) {
    /* read all objects from input file */
    std::vector<Vector::BLF::ObjectHeaderBase *> objects;
    for(;;) {
        Vector::BLF::ObjectHeaderBase * ohb = filein.read();
        if (!ohb) {
            break;
        }

        if (ohb->objectType != Vector::BLF::ObjectType::Unknown115) {
            objects.push_back(ohb);
        }
    }
    filein.close();

    /* write all objects into output file */
    for(Vector::BLF::ObjectHeaderBase * ohb: objects) {
        fileout.write(ohb);
    }
    fileout.close();
}

/** compare files */
static bool compareFiles(const char * infileName, const char * outfileName, uint64_t startPos, uint64_t lastPos) {
    /* open file */
    std::ifstream ifs1;
    std::ifstream ifs2;
    ifs1.open(infileName);
    BOOST_REQUIRE(ifs1.is_open());
    ifs2.open(outfileName);
    BOOST_REQUIRE(ifs2.is_open());

    /* seek to start position */
    ifs1.seekg(static_cast<std::streamoff>(startPos));
    ifs2.seekg(static_cast<std::streamoff>(startPos));

    /* check till end position */
    bool sameFile = true;
    while (ifs1.good() && ifs2.good() &&
            ((lastPos == 0) || (static_cast<uint64_t>(ifs1.tellg()) < lastPos))) {
        char c1 = static_cast<char>(ifs1.get());
        char c2 = static_cast<char>(ifs2.get());
        if (c1 != c2) {
            sameFile = false;
            break;
        }
    }

    /* close file */
    ifs1.close();
    BOOST_REQUIRE(!ifs1.is_open());
    ifs2.close();
    BOOST_REQUIRE(!ifs2.is_open());
    return sameFile;
}

/** Test with uncompressedFiles with Unknown115 ending */
BOOST_AUTO_TEST_CASE(AllBinlogLogfiles) {
    /* input directory */
    boost::filesystem::path indir(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/");



    /* output directory */
    boost::filesystem::path outdir(CMAKE_CURRENT_BINARY_DIR "/events_from_binlog/");
    if (!exists(outdir))
        BOOST_REQUIRE(create_directory(outdir));

    /* loop over all blfs */
    for (boost::filesystem::directory_entry & x : boost::filesystem::directory_iterator(indir)) {
        if (!boost::filesystem::is_regular_file(x))
            continue;
        std::string eventFile = x.path().filename().string();

        /* open input file */
        Vector::BLF::File filein;
        boost::filesystem::path infile(indir.string() + eventFile);
        filein.open(infile.string(), std::ios_base::in);
        BOOST_REQUIRE(filein.is_open());

        /* open output file */
        Vector::BLF::File fileout;
        fileout.setCompressionLevel(0);
        boost::filesystem::path outfile(outdir.string() + eventFile);
        fileout.open(outfile.string(), std::ios_base::out);
        BOOST_REQUIRE(fileout.is_open());

        /* copy file statistics */
        copyFileStatistics(filein, fileout);

        /* copy objects */
        copyObjects(filein, fileout);

        /* compare files */
        BOOST_REQUIRE_MESSAGE(
            compareFiles(
                infile.c_str(), outfile.c_str(),
                static_cast<uint64_t>(fileout.statistics().statisticsSize),
                fileout.statistics().fileSizeWithoutUnknown115),
            eventFile + " is different");
    }
}

/** Test with compressedFiles without Unknown115 ending */
BOOST_AUTO_TEST_CASE(AllConvertedLogfiles) {
    /* input directory */
    boost::filesystem::path indir(CMAKE_CURRENT_SOURCE_DIR "/events_from_converter/");

    /* output directory */
    boost::filesystem::path outdir(CMAKE_CURRENT_BINARY_DIR "/events_from_converter/");
    if (!exists(outdir))
        BOOST_REQUIRE(create_directory(outdir));

    /* loop over all blfs */
    for (boost::filesystem::directory_entry & x : boost::filesystem::directory_iterator(indir)) {
        if (!boost::filesystem::is_regular_file(x))
            continue;
        std::string eventFile = x.path().filename().string();

        /* open input file */
        Vector::BLF::File filein;
        boost::filesystem::path infile(indir.string() + eventFile);
        filein.open(infile.string(), std::ios_base::in);
        BOOST_REQUIRE(filein.is_open());

        /* open output file */
        Vector::BLF::File fileout;
        // @todo fileout.writeUnknown115 = false;
        boost::filesystem::path outfile(outdir.string() + eventFile);
        fileout.open(outfile.string(), std::ios_base::out);
        BOOST_REQUIRE(fileout.is_open());

        /* copy file statistics */
        copyFileStatistics(filein, fileout);

        /* copy objects */
        copyObjects(filein, fileout);

        // Vector bug: sizeof(EventComment) + ...
        if (eventFile == "test_GlobalMarker.blf")
            continue;

        /* compare files */
        BOOST_CHECK_MESSAGE(
            compareFiles(
                infile.c_str(), outfile.c_str(),
                static_cast<uint64_t>(fileout.statistics().statisticsSize),
                fileout.statistics().fileSizeWithoutUnknown115),
            eventFile + " is different");
    }
}
