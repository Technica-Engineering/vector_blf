#define BOOST_TEST_MODULE ObjectHeaderBase
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF/Exceptions.h>
#include <Vector/BLF/ObjectHeaderBase.h>

/** check if it throws on wrong signature */
BOOST_AUTO_TEST_CASE(WrongSignature) {
    /* create bad data */
    Vector::BLF::ObjectHeaderBase ohb1(0, Vector::BLF::ObjectType::UNKNOWN);
    ohb1.signature = Vector::BLF::ObjectSignature - 1; // alter signature
    std::vector<uint8_t> data;
    ohb1.toData(data);

    /* read back data, should throw an exception already during indexing */
    Vector::BLF::ObjectHeaderBase ohb2(0, Vector::BLF::ObjectType::UNKNOWN);
    BOOST_CHECK_THROW(ohb2.fromData(data.begin()), Vector::BLF::Exception);
}
