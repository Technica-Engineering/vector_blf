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
    LPCTSTR pFileName = _T("test_DiagRequestInterpretation.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLDiagRequestInterpretation obj;
    memset(&obj, 0, sizeof(VBLDiagRequestInterpretation));

    /* VBLDiagRequestInterpretation */
    obj.mDiagDescriptionHandle = 0x11111111;
    obj.mDiagVariantHandle = 0x22222222;
    obj.mDiagServiceHandle = 0x33333333;
    obj.mEcuQualifierLength = 3;
    obj.mVariantQualifierLength = 3;
    obj.mServiceQualifierLength = 3;
    obj.mEcuQualifier = "xyz";
    obj.mVariantQualifier = "xyz";
    obj.mServiceQualifier = "xyz";

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLDiagRequestInterpretation) + obj.mEcuQualifierLength + obj.mVariantQualifierLength + obj.mServiceQualifierLength;
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_DIAG_REQUEST_INTERPRETATION;

    /* write object */
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write object again */
    // Vector bug: objectSize is set to 0x31 by BLWriteObject, so we need to set it back to 0x41.
    obj.mHeader.mBase.mObjectSize = sizeof(VBLDiagRequestInterpretation) + obj.mEcuQualifierLength + obj.mVariantQualifierLength + obj.mServiceQualifierLength;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* close handle */
    if (!BLCloseHandle(hFile))
        return -1;

    return 0;
}
