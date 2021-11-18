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
    LPCTSTR pFileName = _T("test_SerialEvent.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0))
        return -1;

    /* define object */
    VBLSerialEvent obj;
    memset(&obj, 0, sizeof(VBLSerialEvent));

    /* VBLSerialEvent */
    obj.mPort = 0x22222222;
    obj.mBaudrate = 0x33333333;
    obj.mReserved = 0x44444444;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_SERIAL_EVENT;

    /* write GeneralSerialEvent object */
    obj.mFlags = BL_SERIAL_TYPE_KLINE_EVENT;
    BYTE data[3] = { 0x11, 0x22, 0x33 };
    LONGLONG timeStamps[3] = { 0x4444, 0x5555, 0x6666 };
    memset(&obj.mGeneral, 0, 16); // size of union of singleByte/compact/general
    obj.mGeneral.mDataLength = 3;
    obj.mGeneral.mTimeStampsLength = 3 * sizeof(LONGLONG);
    obj.mGeneral.mData = reinterpret_cast<unsigned char *>(data);
    obj.mGeneral.mTimeStamps = reinterpret_cast<PLONGLONG>(timeStamps);
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSerialEvent) + obj.mGeneral.mDataLength + obj.mGeneral.mTimeStampsLength;
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write SingleByteSerialEvent object */
    obj.mFlags = BL_SERIAL_TYPE_SINGLE_BYTE;
    memset(&obj.mSingleByte, 0, 16); // size of union of singleByte/compact/general
    obj.mSingleByte.mByte = 0x11;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSerialEvent);
    if (!BLWriteObject(hFile, &obj.mHeader.mBase))
        return -1;

    /* write CompactSerialEvent object */
    obj.mFlags = BL_SERIAL_TYPE_COMPACT_BYTES;
    memset(&obj.mCompact, 0, 16); // size of union of singleByte/compact/general
    obj.mCompact.mCompactLength = 3;
    obj.mCompact.mCompactData[0] = 0x11;
    obj.mCompact.mCompactData[1] = 0x22;
    obj.mCompact.mCompactData[2] = 0x33;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLSerialEvent);
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
