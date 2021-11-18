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
    LPCTSTR pFileName = _T("test_A429BusStatistic.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLA429BusStatistic obj;
    memset(&obj, 0, sizeof(VBLA429BusStatistic));

    /* VBLA429BusStatistic */
    obj.mChannel = 0x1111;
    obj.mDir = 0x22;
    obj.mBusLoad = 0x33333333;
    obj.mDataTotal = 0x44444444;
    obj.mErrorTotal = 0x55555555;
    obj.mBitrate = 0x66666666;
    obj.mParityErrors = 0x7777;
    obj.mBitrateErrors = 0x8888;
    obj.mGapErrors = 0x9999;
    obj.mLineErrors = 0xAAAA;
    obj.mFormatErrors = 0xBBBB;
    obj.mDutyFactorErrors = 0xCCCC;
    obj.mWordLenErrors = 0xDDDD;
    obj.mCodingErrors = 0xEEEE;
    obj.mIdleErrors = 0xFFFF;
    obj.mLevelErrors = 0x1111;
    for (WORD i = 0; i < 256; i++)
        obj.mLabelCount[i] = i;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLA429BusStatistic);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_A429_BUS_STATISTIC;

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
