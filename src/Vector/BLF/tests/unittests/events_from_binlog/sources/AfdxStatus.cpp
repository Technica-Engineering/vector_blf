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
    LPCTSTR pFileName = _T("test_AfdxStatus.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLAfdxStatus obj;
    memset(&obj, 0, sizeof(VBLAfdxStatus));

    /* VBLAfdxStatus */
    obj.mChannel = 0x1111;

    /* VBLAfdxLineStatus for A */
    obj.mStatusA.mFlags = 0x1111;
    obj.mStatusA.mLinkStatus = 0x22;
    obj.mStatusA.mEthernetPhy = 0x33;
    obj.mStatusA.mDuplex = 0x44;
    obj.mStatusA.mMdi = 0x55;
    obj.mStatusA.mConnector = 0x66;
    obj.mStatusA.mClockMode = 0x77;
    obj.mStatusA.mPairs = 0x88;
    obj.mStatusA.mReserved = 0x99;
    obj.mStatusA.mBitrate = 0xAAAAAAAA;

    /* VBLAfdxLineStatus for B */
    obj.mStatusB.mFlags = 0x1111;
    obj.mStatusB.mLinkStatus = 0x22;
    obj.mStatusB.mEthernetPhy = 0x33;
    obj.mStatusB.mDuplex = 0x44;
    obj.mStatusB.mMdi = 0x55;
    obj.mStatusB.mConnector = 0x66;
    obj.mStatusB.mClockMode = 0x77;
    obj.mStatusB.mPairs = 0x88;
    obj.mStatusB.mReserved = 0x99;
    obj.mStatusB.mBitrate = 0xAAAAAAAA;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLAfdxStatus);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_AFDX_STATUS;

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
