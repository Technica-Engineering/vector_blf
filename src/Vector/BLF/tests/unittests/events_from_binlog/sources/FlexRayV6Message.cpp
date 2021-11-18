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
    LPCTSTR pFileName = _T("test_FlexRayV6Message.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLFLEXRAYV6Message obj;
    memset(&obj, 0, sizeof(VBLFLEXRAYV6Message));

    /* VBLFLEXRAYV6Message */
    obj.mChannel = 0x1111;
    obj.mDir = 0x22;
    obj.mLowTime = 0x33;
    obj.mFPGATick = 0x44444444;
    obj.mFPGATickOverflow = 0x55555555;
    obj.mClientIndex = 0x66666666;
    obj.mClusterTime = 0x77777777;
    obj.mFrameId = 0x8888;
    obj.mHeaderCRC = 0x9999;
    obj.mFrameState = 0xAAAA;
    obj.mLength = 0xBB;
    obj.mCycle = 0xCC;
    obj.mHeaderBitMask = 0xDD;
    obj.mReserved1 = 0xEE;
    obj.mReserved2 = 0xFFFF;
    for (BYTE i = 0; i < 64; i++)
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
    obj.mHeader.mBase.mObjectSize = sizeof(VBLFLEXRAYV6Message);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_FLEXRAY_MESSAGE;

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
