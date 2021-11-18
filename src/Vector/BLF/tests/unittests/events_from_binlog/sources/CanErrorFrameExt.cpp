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
    LPCTSTR pFileName = _T("test_CanErrorFrameExt.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLCANErrorFrameExt obj;
    memset(&obj, 0, sizeof(VBLCANErrorFrameExt));

    /* VBLCANErrorFrameExt */
    obj.mChannel = 0x1111;
    obj.mLength = 0x2222;
    obj.mFlags = 0x33333333;
    obj.mECC = 0x44;
    obj.mPosition = 0x55;
    obj.mDLC = 0x66;
    obj.mReserved1 = 0x77;
    obj.mFrameLengthInNS = 0x88888888;
    obj.mID = 0x99999999;
    obj.mFlagsExt = 0xAAAA;
    obj.mReserved2 = 0xBBBB;
    obj.mData[0] = 0xCC;
    obj.mData[1] = 0xDD;
    obj.mData[2] = 0xEE;
    obj.mData[3] = 0xFF;
    obj.mData[4] = 0x11;
    obj.mData[5] = 0x22;
    obj.mData[6] = 0x33;
    obj.mData[7] = 0x44;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLCANErrorFrameExt);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_CAN_ERROR_EXT;

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
