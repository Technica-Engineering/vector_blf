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
    LPCTSTR pFileName = _T("test_EthernetErrorForwarded.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLEthernetErrorForwarded obj;
    memset(&obj, 0, sizeof(VBLEthernetErrorForwarded));

    /* VBLEthernetErrorForwarded */
    obj.mStructLength = sizeof(VBLEthernetErrorForwarded) - sizeof(VBLObjectHeader) - sizeof(obj.mStructLength) - sizeof(obj.mFrameData);
    obj.mFlags = 0x1111;
    obj.mChannel = 0x2222;
    obj.mHardwareChannel = 0x3333;
    obj.mFrameDuration = 0x4444444444444444;
    obj.mFrameChecksum = 0x55555555;
    obj.mDir = 0x6666;
    obj.mFrameLength = 3;
    obj.mFrameHandle = 0x88888888;
    obj.mError = 0x99999999;
    BYTE frameData[3] = { 0xAA, 0xBB, 0xCC };
    obj.mFrameData = frameData;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = offsetof(VBLEthernetErrorForwarded, mFrameData) + obj.mFrameLength;
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_ETHERNET_ERROR_FORWARDED;

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
