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
    LPCTSTR pFileName = _T("test_MostSpy.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLMOSTSpy obj;
    memset(&obj, 0, sizeof(VBLMOSTSpy));

    /* VBLMOSTSpy */
    obj.mChannel = 0x1111;
    obj.mDir = 0x22;
    obj.mDummy1 = 0x33;
    obj.mSourceAdr = 0x44444444;
    obj.mDestAdr = 0x55555555;
    for (BYTE i = 0; i < 17; i++)
        obj.mMsg[i] = i;
    obj.mDummy2 = 0x66;
    obj.mRTyp = 0x7777;
    obj.mRTypAdr = 0x88;
    obj.mState = 0x99;
    obj.mDummy3 = 0xAA;
    obj.mAckNack = 0xBB;
    obj.mCRC = 0xCCCCCCCC;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLMOSTSpy);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_MOST_SPY;

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
