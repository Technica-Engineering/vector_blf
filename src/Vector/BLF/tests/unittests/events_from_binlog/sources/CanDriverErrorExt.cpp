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
    LPCTSTR pFileName = _T("test_CanDriverErrorExt.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLCANDriverErrorExt obj;
    memset(&obj, 0, sizeof(VBLCANDriverErrorExt));

    /* VBLCanDriverErrorExt */
    obj.mChannel = 0x1111;
    obj.mTXErrors = 0x22;
    obj.mRXErrors = 0x33;
    obj.mErrorCode = 0x44444444;
    obj.mFlags = 0x55555555;
    obj.mState = 0x66;
    obj.mReserved1 = 0x77;
    obj.mReserved2 = 0x8888;
    obj.mReserved3[0] = 0x99999999;
    obj.mReserved3[1] = 0xAAAAAAAA;
    obj.mReserved3[2] = 0xBBBBBBBB;
    obj.mReserved3[3] = 0xCCCCCCCC;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLCANDriverErrorExt);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_CAN_DRIVER_ERROR_EXT;

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
