#define BOOST_TEST_MODULE LinShortOrSlowResponse
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_SHORT_OR_SLOW_RESPONSE = 88 */
BOOST_AUTO_TEST_CASE(LinShortOrSlowResponse)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinShortOrSlowResponse.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb;
    Vector::BLF::LinShortOrSlowResponse * linShortOrSlowResponse;

    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE);
    linShortOrSlowResponse = static_cast<Vector::BLF::LinShortOrSlowResponse *>(ohb);
    /* ObjectHeaderBase */
    BOOST_CHECK(linShortOrSlowResponse->signature == Vector::BLF::ObjectSignature);
    BOOST_CHECK(linShortOrSlowResponse->headerSize == linShortOrSlowResponse->calculateHeaderSize());
    BOOST_CHECK(linShortOrSlowResponse->headerVersion == 1);
    BOOST_CHECK(linShortOrSlowResponse->objectSize == linShortOrSlowResponse->calculateObjectSize());
    BOOST_CHECK(linShortOrSlowResponse->objectType == Vector::BLF::ObjectType::LIN_SHORT_OR_SLOW_RESPONSE);
    /* ObjectHeader */
    BOOST_CHECK(linShortOrSlowResponse->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    // reserved
    BOOST_CHECK(linShortOrSlowResponse->objectVersion == 0);
    BOOST_CHECK(linShortOrSlowResponse->objectTimeStamp == 1298765000); // ns
    /* LinBusEvent */
    BOOST_CHECK(linShortOrSlowResponse->sof == 1279516000); // ns
    BOOST_CHECK(linShortOrSlowResponse->eventBaudrate == 19230);
    BOOST_CHECK(linShortOrSlowResponse->channel == 1);
    // reserved
    /* LinSynchFieldEvent */
    BOOST_CHECK(linShortOrSlowResponse->synchBreakLength == 937250);
    BOOST_CHECK(linShortOrSlowResponse->synchDelLength == 102625);
    /* LinMessageDescriptor */
    BOOST_CHECK(linShortOrSlowResponse->supplierId == 0);
    BOOST_CHECK(linShortOrSlowResponse->messageId == 0);
    BOOST_CHECK(linShortOrSlowResponse->nad == 0);
    BOOST_CHECK(linShortOrSlowResponse->id == 1);
    BOOST_CHECK(linShortOrSlowResponse->dlc == 8);
    BOOST_CHECK(linShortOrSlowResponse->checksumModel == 0xff);
    /* LinDatabyteTimestampEvent */
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[0] == 1281570000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[1] == 1283679000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[2] == 1285759000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[3] == 1287839000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[4] == 1289927000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[5] == 1292007000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[6] == 1294087000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[7] == 1296167000); // ns
    BOOST_CHECK(linShortOrSlowResponse->databyteTimestamps[8] == 1298244000); // ns
    /* LinShortOrSlowResponse */
    BOOST_CHECK(linShortOrSlowResponse->numberOfRespBytes == 9);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[0] == 0x11);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[1] == 0x12);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[2] == 0x13);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[3] == 0x14);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[4] == 0x15);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[5] == 0x16);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[6] == 0x17);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[7] == 0x18);
    BOOST_CHECK(linShortOrSlowResponse->respBytes[8] == 0x99);
    BOOST_CHECK(linShortOrSlowResponse->slowResponse == 1);
    BOOST_CHECK(linShortOrSlowResponse->interruptedByBreak == 0);
    // reserved
    delete ohb;

    BOOST_CHECK(file.eof());
    file.close();
}
