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
    LPCTSTR pFileName = _T("test_CanFdMessage64.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLCANFDMessage64 obj;
    memset(&obj, 0, sizeof(VBLCANFDMessage64));

    /* VBLCANFdExtFrameData */
    obj.mExtFrameData.mBTRExtArb = 0x11111111;
    obj.mExtFrameData.mBTRExtData = 0x22222222;

    /* VBLCANFDMessage64 */
    obj.mChannel = 0x11;
    obj.mDLC = 0x22;
    obj.mValidDataBytes = 64;
    obj.mTxCount = 0x44;
    obj.mID = 0x55555555;
    obj.mFrameLength = 0x66666666;
    obj.mFlags = 0x77777777;
    obj.mBtrCfgArb = 0x88888888;
    obj.mBtrCfgData = 0x99999999;
    obj.mTimeOffsetBrsNs = 0xAAAAAAAA;
    obj.mTimeOffsetCrcDelNs = 0xBBBBBBBB;
    obj.mBitCount = 0xCCCC;
    obj.mDir = 0xDD;
    obj.mExtDataOffset = 0x50;
    obj.mCRC = 0xFFFFFFFF;
    for (BYTE i = 0; i < 64; i++)
        obj.mData[i] = i;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLCANFDMessage64);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_CAN_FD_MESSAGE_64;

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
