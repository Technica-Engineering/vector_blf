// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <stdio.h>
#define STRICT
#include <windows.h>

#include "binlog.h"

int main(int argc, char ** argv) {
    /* create file */
    LPCTSTR pFileName = _T("test_LinReceiveError2.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLLINReceiveError2 obj;
    memset(&obj, 0, sizeof(VBLLINReceiveError2));

    /* VBLLINReceiveError2 */
    obj.mData[0] = 0x11;
    obj.mData[1] = 0x22;
    obj.mData[2] = 0x33;
    obj.mData[3] = 0x44;
    obj.mData[4] = 0x55;
    obj.mData[5] = 0x66;
    obj.mData[6] = 0x77;
    obj.mData[7] = 0x88;
    obj.mFSMId = 0x99;
    obj.mFSMState = 0xAA;
    obj.mStateReason = 0xBB;
    obj.mOffendingByte = 0xCC;
    obj.mShortError = 0xDD;
    obj.mTimeoutDuringDlcDetection = 0xEE;
    obj.mIsETF = 0xFF;
    obj.mHasDatabytes = 0x11;
    obj.mRespBaudrate = 0x22222222;
    obj.mReserved[0] = 0x33;
    obj.mReserved[1] = 0x33;
    obj.mReserved[2] = 0x33;
    obj.mReserved[3] = 0x33;
    obj.mExactHeaderBaudrate = 4.0;
    obj.mEarlyStopbitOffset = 0x55555555;
    obj.mEarlyStopbitOffsetResponse = 0x66666666;

    /* VBLLINDatabyteTimestampEvent */
    obj.mLinTimestampEvent.mDatabyteTimestamps[0] = 0x1111111111111111;
    obj.mLinTimestampEvent.mDatabyteTimestamps[1] = 0x2222222222222222;
    obj.mLinTimestampEvent.mDatabyteTimestamps[2] = 0x3333333333333333;
    obj.mLinTimestampEvent.mDatabyteTimestamps[3] = 0x4444444444444444;
    obj.mLinTimestampEvent.mDatabyteTimestamps[4] = 0x5555555555555555;
    obj.mLinTimestampEvent.mDatabyteTimestamps[5] = 0x6666666666666666;
    obj.mLinTimestampEvent.mDatabyteTimestamps[6] = 0x7777777777777777;
    obj.mLinTimestampEvent.mDatabyteTimestamps[7] = 0x8888888888888888;
    obj.mLinTimestampEvent.mDatabyteTimestamps[8] = 0x9999999999999999;

    /* VBLLINMessageDescriptor */
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mSupplierID = 0x1111;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mMessageID = 0x2222;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mNAD = 0x33;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mID = 0x44;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mDLC = 0x55;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mChecksumModel = 0x66;

    /* VBLLINSynchFieldEvent */
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mSynchBreakLength = 0x1111111111111111;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mSynchDelLength = 0x2222222222222222;

    /* VBLINBusEvent */
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mLinBusEvent.mSOF = 0x1111111111111111;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mLinBusEvent.mEventBaudrate = 0x22222222;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mLinBusEvent.mChannel = 0x3333;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mLinBusEvent.mReserved[0] = 0x44;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mLinBusEvent.mReserved[1] = 0x44;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLLINReceiveError2);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_LIN_RCV_ERROR2;

    /* write object */
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write object again */
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* close handle */
    if (!BLCloseHandle(hFile))
        return -1;

    return 0;
}
