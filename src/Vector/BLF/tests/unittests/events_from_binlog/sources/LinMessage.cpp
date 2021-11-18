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
    LPCTSTR pFileName = _T("test_LinMessage.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLLINMessage obj;
    memset(&obj, 0, sizeof(VBLLINMessage));

    /* VBLLINMessage */
    obj.mChannel = 0x1111;
    obj.mID = 0x22;
    obj.mDLC = 0x33;
    obj.mData[0] = 0x44;
    obj.mData[1] = 0x55;
    obj.mData[2] = 0x66;
    obj.mData[3] = 0x77;
    obj.mData[4] = 0x88;
    obj.mData[5] = 0x99;
    obj.mData[6] = 0xAA;
    obj.mData[7] = 0xBB;
    obj.mFSMId = 0xCC;
    obj.mFSMState = 0xDD;
    obj.mHeaderTime = 0xEE;
    obj.mFullTime = 0xFF;
    obj.mCRC = 0x1111;
    obj.mDir = 0x22;
    obj.mReserved = 0x33;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLLINMessage);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_LIN_MESSAGE;

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
