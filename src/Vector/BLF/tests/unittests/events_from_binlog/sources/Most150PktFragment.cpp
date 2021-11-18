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
    LPCTSTR pFileName = _T("test_Most150PktFragment.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLMOST150PktFragment obj;
    memset(&obj, 0, sizeof(VBLMOST150PktFragment));

    /* VBLMOST150PktFragment */
    obj.mChannel = 0x1111;
    obj.mDummy1 = 0x22;
    obj.mAckNack = 0x33;
    obj.mValidMask = 0x44444444;
    obj.mSourceAdr = 0x55555555;
    obj.mDestAdr = 0x66666666;
    obj.mPAck = 0x77;
    obj.mCAck = 0x88;
    obj.mPriority = 0x99;
    obj.mPIndex = 0xAA;
    obj.mCRC = 0xBBBBBBBB;
    obj.mDataLen = 0xCCCCCCCC;
    obj.mDataLenAnnounced = 0xDDDDDDDD;
    obj.mFirstDataLen = 3;
    BYTE firstData[3] = { 4, 5, 6 };
    obj.mFirstData = firstData;

    /* VBLObjectHeader2 */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mTimeStampStatus = 0x22;
    obj.mHeader.mReserved1 = 0x33;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x4444444444444444;
    obj.mHeader.mOriginalTimeStamp = 0x5555555555555555;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLMOST150PktFragment) + obj.mFirstDataLen;
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_MOST_150_PKT_FRAGMENT;

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
