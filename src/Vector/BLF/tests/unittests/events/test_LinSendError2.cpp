#define BOOST_TEST_MODULE LinSendError2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

static bool isEqual(double a, double b)
{
    return ((a - b) < 0.000001) && ((b - a) < 0.000001);
}

/* LIN_SND_ERROR2 = 58 */
BOOST_AUTO_TEST_CASE(LinSendError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinSendError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinSendError2 * linSendError2;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SND_ERROR2);
    linSendError2 = static_cast<Vector::BLF::LinSendError2 *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linSendError2->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linSendError2->headerSize == linSendError2->calculateHeaderSize());
    BOOST_CHECK(linSendError2->headerVersion == 1);
    BOOST_CHECK(linSendError2->objectSize == linSendError2->calculateObjectSize());
    BOOST_CHECK(linSendError2->objectType == Vector::BLF::ObjectType::LIN_SND_ERROR2);
    /* ObjectHeader */
    BOOST_CHECK(linSendError2->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linSendError2->objectVersion == 1);
    BOOST_CHECK(linSendError2->objectTimeStamp == 424674000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linSendError2->sof == 416054000); // ns
    BOOST_CHECK(linSendError2->eventBaudrate == 19230);
    BOOST_CHECK(linSendError2->channel == 1);
    // reserved
    /* LinSynchFieldEvent */
    BOOST_CHECK(linSendError2->synchBreakLength == 937187);
    BOOST_CHECK(linSendError2->synchDelLength == 113250);
    /* LinMessageDescriptor */
    BOOST_CHECK(linSendError2->supplierId == 0);
    BOOST_CHECK(linSendError2->messageId == 0);
    BOOST_CHECK(linSendError2->nad == 0);
    BOOST_CHECK(linSendError2->id == 0x21); // 33
    BOOST_CHECK(linSendError2->dlc == 4);
    BOOST_CHECK(linSendError2->checksumModel == 1); // enhanced
    /* LinSendError2 */
    BOOST_CHECK(linSendError2->eoh == 418122000); // ns
    BOOST_CHECK(linSendError2->isEtf == 0);
    BOOST_CHECK(linSendError2->fsmId == 0xff);
    BOOST_CHECK(linSendError2->fsmState == 0);
    // reserved
    BOOST_CHECK(isEqual(linSendError2->exactHeaderBaudrate, 19230.769231));
    BOOST_CHECK(linSendError2->earlyStopbitOffset == 26000);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
