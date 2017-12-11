#define BOOST_TEST_MODULE LinSendError2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_SND_ERROR2 = 58 */
BOOST_AUTO_TEST_CASE(LinSendError2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinSendError2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SND_ERROR2);
    Vector::BLF::LinSendError2 * obj = static_cast<Vector::BLF::LinSendError2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_SND_ERROR2);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 424674000); // ns

    /* LinBusEvent */
    BOOST_CHECK_EQUAL(obj->sof, 416054000); // ns
    BOOST_CHECK_EQUAL(obj->eventBaudrate, 19230);
    BOOST_CHECK_EQUAL(obj->channel, 1);
    // reserved

    /* LinSynchFieldEvent */
    BOOST_CHECK_EQUAL(obj->synchBreakLength, 937187);
    BOOST_CHECK_EQUAL(obj->synchDelLength, 113250);

    /* LinMessageDescriptor */
    BOOST_CHECK_EQUAL(obj->supplierId, 0);
    BOOST_CHECK_EQUAL(obj->messageId, 0);
    BOOST_CHECK_EQUAL(obj->nad, 0);
    BOOST_CHECK_EQUAL(obj->id, 0x21); // 33
    BOOST_CHECK_EQUAL(obj->dlc, 4);
    BOOST_CHECK_EQUAL(obj->checksumModel, 1); // enhanced

    /* LinSendError2 */
    BOOST_CHECK_EQUAL(obj->eoh, 418122000); // ns
    BOOST_CHECK_EQUAL(obj->isEtf, 0);
    BOOST_CHECK_EQUAL(obj->fsmId, 0xff);
    BOOST_CHECK_EQUAL(obj->fsmState, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->exactHeaderBaudrate, 19230.769231);
    BOOST_CHECK_EQUAL(obj->earlyStopbitOffset, 26000);
    // reserved

    delete obj;

    file.close();
}
