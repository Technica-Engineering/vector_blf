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
    LPCTSTR pFileName = _T("test_SystemVariable.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLSystemVariable obj;
    memset(&obj, 0, sizeof(VBLSystemVariable));

    /* VBLSystemVariable */
    obj.mRepresentation = 0x22222222;
    obj.mReserved[0] = 0x33333333;
    obj.mReserved[1] = 0x44444444;
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
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_SYS_VARIABLE;

    /* write DOUBLE object */
    DOUBLE doubleValue = 2.0;
    obj.mType = BL_SYSVAR_TYPE_DOUBLE;
    obj.mDataLength = sizeof(doubleValue);
    obj.mData = reinterpret_cast<unsigned char *>(&doubleValue);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSystemVariable) + obj.mNameLength + obj.mDataLength;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write LONG object */
    LONG longValue = 0x11111111;
    obj.mType = BL_SYSVAR_TYPE_LONG;
    obj.mDataLength = sizeof(longValue);
    obj.mData = reinterpret_cast<unsigned char *>(&longValue);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSystemVariable) + obj.mNameLength + obj.mDataLength;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write STRING object */
    char stringValue[] = "xyz";
    obj.mType = BL_SYSVAR_TYPE_STRING;
    obj.mDataLength = 3;
    obj.mData = reinterpret_cast<unsigned char *>(&stringValue);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSystemVariable) + obj.mNameLength + obj.mDataLength;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write DOUBLEARRAY object */
    DOUBLE doubleArray[] = { 1.0, 2.0, 3.0 };
    obj.mType = BL_SYSVAR_TYPE_DOUBLEARRAY;
    obj.mDataLength = sizeof(doubleArray);
    obj.mData = reinterpret_cast<unsigned char *>(&doubleArray);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSystemVariable) + obj.mNameLength + obj.mDataLength;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write LONGARRAY object */
    LONG longArray[] = { 1, 2, 3 };
    obj.mType = BL_SYSVAR_TYPE_LONGARRAY;
    obj.mDataLength = sizeof(longArray);
    obj.mData = reinterpret_cast<unsigned char *>(&longArray);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSystemVariable) + obj.mNameLength + obj.mDataLength;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write LONGLONG object */
    LONGLONG longLongValue = 0x1111111111111111;
    obj.mType = BL_SYSVAR_TYPE_LONGLONG;
    obj.mDataLength = sizeof(longLongValue);
    obj.mData = reinterpret_cast<unsigned char *>(&longLongValue);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSystemVariable) + obj.mNameLength + obj.mDataLength;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write BYTEARRAY object */
    BYTE byteArray[] = { 1, 2, 3 };
    obj.mType = BL_SYSVAR_TYPE_BYTEARRAY;
    obj.mDataLength = sizeof(byteArray);
    obj.mData = reinterpret_cast<unsigned char *>(&byteArray);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSystemVariable) + obj.mNameLength + obj.mDataLength;
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
