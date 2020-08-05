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
    {
        std::fstream file;
        file.open(CMAKE_CURRENT_BINARY_DIR "/test_FileStatistics.blf", std::ios_base::out);
        Vector::BLF::FileStatistics fileStatistics1;
        std::vector<uint8_t> data;
        fileStatistics1.toData(data);
        file.write(reinterpret_cast<char *>(data.data()), data.size());
    }

    /* read fileStatistics */
    {
        std::fstream file;
        file.open(CMAKE_CURRENT_BINARY_DIR "/test_FileStatistics.blf", std::ios_base::in);
        Vector::BLF::FileStatistics fileStatistics2;
        std::vector<uint8_t> data(fileStatistics2.statisticsSize);
        file.read(reinterpret_cast<char *>(data.data()), data.size());
        fileStatistics2.fromData(std::begin(data));
    }
}

/** test throw on wrong file signature */
BOOST_AUTO_TEST_CASE(WrongFileSignature) {
    /* open file and write in fileStatistics */
    {
        std::fstream file;
        file.open(CMAKE_CURRENT_BINARY_DIR "/test_FileStatistics.blf", std::ios_base::out);
        Vector::BLF::FileStatistics fileStatistics1;
        fileStatistics1.signature--;
        std::vector<uint8_t> data;
        fileStatistics1.toData(data);
        file.write(reinterpret_cast<char *>(data.data()), data.size());
    }

    /* read fileStatistics */
    {
        std::fstream file;
        file.open(CMAKE_CURRENT_BINARY_DIR "/test_FileStatistics.blf", std::ios_base::in);
        Vector::BLF::FileStatistics fileStatistics2;
        std::vector<uint8_t> data(fileStatistics2.statisticsSize);
        file.read(reinterpret_cast<char *>(data.data()), data.size());
        BOOST_CHECK_THROW(fileStatistics2.fromData(std::begin(data)), Vector::BLF::Exception);
    }
}
