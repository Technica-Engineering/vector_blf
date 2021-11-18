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
    LPCTSTR pFileName = _T("test_A429Message.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLA429Message obj;
    memset(&obj, 0, sizeof(VBLA429Message));

    /* VBLA429Message */
    obj.mA429Data[0] = 0x11;
    obj.mA429Data[1] = 0x22;
    obj.mA429Data[2] = 0x33;
    obj.mA429Data[3] = 0x44;
    obj.mChannel = 0x5555;
    obj.mDir = 0x66;
    obj.mReserved = 0x77;
    obj.mBitrate = 0x88888888;
    obj.mErrReason = 0x79999999; // signed
    obj.mErrPosition = 0xAAAA;
    obj.mFrameGap = 0xBBBBBBBBBBBBBBBB;
    obj.mFrameLength = 0xCCCCCCCC;
    obj.mMsgCtrl = 0xDDDD;
    obj.mCycleTime = 0xEEEEEEEE;
    obj.mError = 0xFFFFFFFF;
    obj.mBitLenOfLastBit = 0x11111111;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLA429Message);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_A429_MESSAGE;

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
