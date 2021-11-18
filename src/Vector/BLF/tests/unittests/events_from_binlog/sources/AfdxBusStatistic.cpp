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
    LPCTSTR pFileName = _T("test_AfdxBusStatistic.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLAfdxBusStatistic obj;
    memset(&obj, 0, sizeof(VBLAfdxBusStatistic));

    /* VBLAfdxBusStatistic */
    obj.mChannel = 0x1111;
    obj.mFlags = 0x2222;
    obj.mStatDuration = 0x33333333;
    obj.mStatRxPacketCountHW = 0x44444444;
    obj.mStatTxPacketCountHW = 0x55555555;
    obj.mStatRxErrorCountHW = 0x66666666;
    obj.mStatTxErrorCountHW = 0x77777777;
    obj.mStatRxBytesHW = 0x88888888;
    obj.mStatTxBytesHW = 0x99999999;
    obj.mStatRxPacketCount = 0xAAAAAAAA;
    obj.mStatTxPacketCount = 0xBBBBBBBB;
    obj.mStatDroppedPacketCount = 0xCCCCCCCC;
    obj.mStatInvalidPacketCount = 0xDDDDDDDD;
    obj.mStatLostPacketCount = 0xEEEEEEEE;
    obj.mLine = 0xFF;
    obj.mLinkStatus = 0x11;
    obj.mLinkSpeed = 0x2222;
    obj.mLinkLost = 0x3333;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLAfdxBusStatistic);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_AFDX_BUS_STATISTIC;

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
