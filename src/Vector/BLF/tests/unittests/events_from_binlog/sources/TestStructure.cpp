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
    LPCTSTR pFileName = _T("test_TestStructure.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLTestStructure obj;
    memset(&obj, 0, sizeof(VBLTestStructure));

    /* VBLTestStructure */
    obj.mExecutingObjectIdentity = 0x11111111;
    obj.mType = BL_TESTSTRUCT_TYPE_TM_TESTMODULE;
    obj.mUniqueNo = 0x22222222;
    obj.mAction = BL_TESTSTRUCT_ACTION_BEGIN;
    obj.mResult = BL_TESTSTRUCT_VERDICT_PASSED;
    obj.mExecutingObjectName = L"xyz";
    obj.mName = L"xyz";
    obj.mText = L"xyz";
    obj.mExecutingObjectNameLength = 3;
    obj.mNameLength = 3;
    obj.mTextLength = 3;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLTestStructure) + (obj.mExecutingObjectNameLength + obj.mNameLength + obj.mTextLength) * sizeof(wchar_t);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_TEST_STRUCTURE;

    /* write object */
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write object again */
    // Vector bug: objectSize is set to 0x42 by BLWriteObject, so we need to set it back to 0x4E.
    obj.mHeader.mBase.mObjectSize = sizeof(VBLTestStructure) + (obj.mExecutingObjectNameLength + obj.mNameLength + obj.mTextLength) * sizeof(wchar_t);
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* close handle */
    if (!BLCloseHandle(hFile))
        return -1;

    return 0;
}
