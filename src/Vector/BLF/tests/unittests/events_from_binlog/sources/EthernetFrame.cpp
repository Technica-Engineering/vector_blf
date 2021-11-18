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
    LPCTSTR pFileName = _T("test_EthernetFrame.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLEthernetFrame obj;
    memset(&obj, 0, sizeof(VBLEthernetFrame));

    /* VBLEthernetFrame */
    obj.mSourceAddress[0] = 0x11;
    obj.mSourceAddress[1] = 0x22;
    obj.mSourceAddress[2] = 0x33;
    obj.mSourceAddress[3] = 0x44;
    obj.mSourceAddress[4] = 0x55;
    obj.mSourceAddress[5] = 0x66;
    obj.mChannel = 0x7777;
    obj.mDestinationAddress[0] = 0x88;
    obj.mDestinationAddress[1] = 0x99;
    obj.mDestinationAddress[2] = 0xAA;
    obj.mDestinationAddress[3] = 0xBB;
    obj.mDestinationAddress[4] = 0xCC;
    obj.mDestinationAddress[5] = 0xDD;
    obj.mDir = 0xEEEE;
    obj.mType = 0xFFFF;
    obj.mTPID = 0x1111;
    obj.mTCI = 0x2222;
    obj.mPayLoadLength = 3; // @todo this should be payLoadLength = payLoad.size() + 2;
    BYTE payLoad[3] = { 4, 5, 6 };
    obj.mPayLoad = payLoad;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLEthernetFrame) + obj.mPayLoadLength;
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_ETHERNET_FRAME;

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
