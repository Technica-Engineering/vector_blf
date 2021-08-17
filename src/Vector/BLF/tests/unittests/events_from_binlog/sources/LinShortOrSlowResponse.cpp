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
    LPCTSTR pFileName = _T("test_LinShortOrSlowResponse.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLLINShortOrSlowResponse obj;
    memset(&obj, 0, sizeof(VBLLINShortOrSlowResponse));

    /* VBLLINShortOrSlowResponse */
    obj.mNumberOfRespBytes = 0x11111111;
    for (BYTE i = 0; i < 9; i++)
        obj.mRespBytes[i] = i;
    obj.mSlowResponse = 0x22;
    obj.mInterruptedByBreak = 0x33;
    obj.mReserved[0] = 0x44;

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
    obj.mHeader.mBase.mObjectSize = sizeof(VBLLINShortOrSlowResponse);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_LIN_SHORT_OR_SLOW_RESPONSE;

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
