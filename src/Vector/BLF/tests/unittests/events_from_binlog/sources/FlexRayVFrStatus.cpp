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
    LPCTSTR pFileName = _T("test_FlexRayVFrStatus.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLFLEXRAYVFrStatus obj;
    memset(&obj, 0, sizeof(VBLFLEXRAYVFrStatus));

    /* VBLFLEXRAYVFrStatus */
    obj.mChannel = 0x1111;
    obj.mVersion = 0x2222;
    obj.mChannelMask = 0x3333;
    obj.mCycle = 0x44;
    obj.mClientIndex = 0x55555555;
    obj.mClusterNo = 0x66666666;
    obj.mWus = 0x77777777;
    obj.mCcSyncState = 0x88888888;
    obj.mTag = 0x99999999;
    obj.mData[0] = 0xAAAAAAAA;
    obj.mData[1] = 0xBBBBBBBB;
    for (WORD i = 0; i < 16; i++)
        obj.mReserved[i] = i;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLFLEXRAYVFrStatus);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_FR_STATUS;

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
