#define BOOST_TEST_MODULE ObjectHeaderBase
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/** check if it throws on wrong signature */
BOOST_AUTO_TEST_CASE(WrongSignature)
{
    /* open uncompressedFile */
    Vector::BLF::UncompressedFile file;
    file.open();

    /* write bad data */
    Vector::BLF::ObjectHeaderBase ohb1;
    ohb1.signature = Vector::BLF::ObjectSignature - 1;
    ohb1.write(file);

    /* read back data */
    Vector::BLF::ObjectHeaderBase ohb2;
    BOOST_CHECK_THROW(ohb2.read(file), Vector::BLF::Exception);
}
