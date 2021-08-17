// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <stdio.h>
#define STRICT
#include <windows.h>
#include <stddef.h>

#include "binlog.h"

int main(int argc, char ** argv) {
    /* create file */
    LPCTSTR pFileName = _T("test_CanFdErrorFrame64.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLCANFDErrorFrame64 obj;
    memset(&obj, 0, sizeof(VBLCANFDErrorFrame64));

    /* VBLCANFdExtFrameData */
    obj.mExtFrameData.mBTRExtArb = 0x11111111;
    obj.mExtFrameData.mBTRExtData = 0x22222222;

    /* VBLCANFDErrorFrame64 */
    obj.mChannel = 0x11;
    obj.mDLC = 0x22;
    obj.mValidDataBytes = 64;
    obj.mECC = 0x44;
    obj.mFlags = 0x5555;
    obj.mErrorCodeExt = 0x6666;
    obj.mExtFlags = 0x7777;
    obj.mExtDataOffset = offsetof(VBLCANFDErrorFrame64, mExtFrameData);
    obj.reserved1 = 0x99;
    obj.mID = 0xAAAAAAAA;
    obj.mFrameLength = 0xBBBBBBBB;
    obj.mBtrCfgArb = 0xCCCCCCCC;
    obj.mBtrCfgData = 0xDDDDDDDD;
    obj.mTimeOffsetBrsNs = 0xEEEEEEEE;
    obj.mTimeOffsetCrcDelNs = 0xFFFFFFFF;
    obj.mCRC = 0x11111111;
    obj.mErrorPosition = 0x2222;
    obj.mReserved2 = 0x3333;
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
    obj.mHeader.mBase.mObjectSize = sizeof(VBLCANFDErrorFrame64);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_CAN_FD_ERROR_64;

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
