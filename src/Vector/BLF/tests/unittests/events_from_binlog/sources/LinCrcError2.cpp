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
    LPCTSTR pFileName = _T("test_LinCrcError2.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLLINCRCError2 obj;
    memset(&obj, 0, sizeof(VBLLINCRCError2));

    /* VBLLINCRCError2 */
    obj.mData[0] = 0x11;
    obj.mData[1] = 0x22;
    obj.mData[2] = 0x33;
    obj.mData[3] = 0x44;
    obj.mData[4] = 0x55;
    obj.mData[5] = 0x66;
    obj.mData[6] = 0x77;
    obj.mData[7] = 0x88;
    obj.mCRC = 0x9999;
    obj.mDir = 0xAA;
    obj.mFSMId = 0xBB;
    obj.mFSMState = 0xCC;
    obj.mSimulated = 0xDD;
    obj.mReserved[0] = 0xEE;
    obj.mReserved[1] = 0xEE;
    obj.mRespBaudrate = 0xFFFFFFFF;
    obj.mReserved2[0] = 0x11;
    obj.mReserved2[1] = 0x11;
    obj.mReserved2[2] = 0x11;
    obj.mReserved2[3] = 0x11;
    obj.mExactHeaderBaudrate = 2.0;
    obj.mEarlyStopbitOffset = 0x33333333;
    obj.mEarlyStopbitOffsetResponse = 0x44444444;

    /* VBLLINDatabyteTimestampEvent */
    for (ULONGLONG i = 0; i < 9; i++)
        obj.mLinTimestampEvent.mDatabyteTimestamps[i] = i;

    /* VBLLINMessageDescriptor */
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mSupplierID = 0x1111;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mMessageID = 0x2222;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mNAD = 0x33;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mID = 0x44;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mDLC = 0x55;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mChecksumModel = 0x66;

    /* VBLLINSynchFieldEvent */
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mSynchBreakLength = 0x11111111;
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mSynchDelLength = 0x22222222;

    /* VBLLinBusEvent */
    obj.mLinTimestampEvent.mLinMsgDescrEvent.mLinSynchFieldEvent.mLinBusEvent.mSOF = 0x11111111;
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
    obj.mHeader.mBase.mObjectSize = sizeof(VBLLINCRCError2);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_LIN_CRC_ERROR2;

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
