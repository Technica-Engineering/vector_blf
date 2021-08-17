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
    LPCTSTR pFileName = _T("test_LinUnexpectedWakeup.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLLINUnexpectedWakeup obj;
    memset(&obj, 0, sizeof(VBLLINUnexpectedWakeup));

    /* VBLLINUnexpectedWakeup */
    obj.mWidth = 0x1111111111111111;
    obj.mSignal = 0x22;
    for (BYTE i = 0; i < 7; i++)
        obj.mReserved[i] = 0x33;

    /* VBLINBusEvent */
    obj.mLinBusEvent.mSOF = 0x1111111111111111;
    obj.mLinBusEvent.mEventBaudrate = 0x22222222;
    obj.mLinBusEvent.mChannel = 0x3333;
    obj.mLinBusEvent.mReserved[0] = 0x44;
    obj.mLinBusEvent.mReserved[1] = 0x44;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLLINUnexpectedWakeup);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_LIN_UNEXPECTED_WAKEUP;

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
