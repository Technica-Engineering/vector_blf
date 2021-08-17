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
    LPCTSTR pFileName = _T("test_EnvironmentVariable.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLEnvironmentVariable obj;
    memset(&obj, 0, sizeof(VBLEnvironmentVariable));

    /* VBLEnvironmentVariable */
    obj.mNameLength = 3;
    obj.mName = "xyz";

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;

    /* write INT object */
    ULONG longValue = 0x11111111;
    obj.mDataLength = sizeof(longValue);
    obj.mData = reinterpret_cast<unsigned char *>(&longValue);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLEnvironmentVariable) + obj.mNameLength + obj.mDataLength;
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_ENV_INTEGER;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write DOUBLE object */
    DOUBLE doubleValue = 2.0;
    obj.mDataLength = sizeof(doubleValue);
    obj.mData = reinterpret_cast<unsigned char *>(&doubleValue);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLEnvironmentVariable) + obj.mNameLength + obj.mDataLength;
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_ENV_DOUBLE;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write STRING object */
    char stringValue[] = "xyz";
    obj.mDataLength = 3;
    obj.mData = reinterpret_cast<unsigned char *>(&stringValue);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLEnvironmentVariable) + obj.mNameLength + obj.mDataLength;
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_ENV_STRING;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write DATA object */
    BYTE dataValue[3] = { 1, 2, 3 };
    obj.mDataLength = 3;
    obj.mData = dataValue;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLEnvironmentVariable) + obj.mNameLength + obj.mDataLength;
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_ENV_DATA;
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
