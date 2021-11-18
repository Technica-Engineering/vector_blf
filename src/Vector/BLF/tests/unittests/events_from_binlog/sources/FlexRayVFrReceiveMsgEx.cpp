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
    LPCTSTR pFileName = _T("test_FlexRayVFrReceiveMsgEx.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLFLEXRAYVFrReceiveMsgEx obj;
    memset(&obj, 0, sizeof(VBLFLEXRAYVFrReceiveMsgEx));

    /* VBLFLEXRAYVFrReceiveMsgEx */
    obj.mChannel = 0x1111;
    obj.mVersion = 0x2222;
    obj.mChannelMask = 0x3333;
    obj.mDir = 0x4444;
    obj.mClientIndex = 0x55555555;
    obj.mClusterNo = 0x66666666;
    obj.mFrameId = 0x7777;
    obj.mHeaderCRC1 = 0x8888;
    obj.mHeaderCRC2 = 0x9999;
    obj.mByteCount = 0xAAAA;
    obj.mDataCount = 254;
    obj.mCycle = 0xCCCC;
    obj.mTag = 0xDDDDDDDD;
    obj.mData = 0xEEEEEEEE;
    obj.mFrameFlags = 0xFFFFFFFF;
    obj.mAppParameter = 0x11111111;
    obj.mFrameCRC = 0x22222222;
    obj.mFrameLengthNS = 0x33333333;
    obj.mFrameId1 = 0x4444;
    obj.mPDUOffset = 0x5555;
    obj.mBlfLogMask = 0x6666;
    obj.mReservedW = 0x7777;
    obj.mReserved[0] = 0x88888888;
    obj.mReserved[1] = 0x99999999;
    obj.mReserved[2] = 0xAAAAAAAA;
    obj.mReserved[3] = 0xBBBBBBBB;
    obj.mReserved[4] = 0xCCCCCCCC;
    obj.mReserved[5] = 0xDDDDDDDD;
    for (BYTE i = 0; i < 254; i++)
        obj.mDataBytes[i] = i;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLFLEXRAYVFrReceiveMsgEx) - 6; // @todo Why does this need to be decremented by 6?
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_FR_RCVMESSAGE_EX;

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
