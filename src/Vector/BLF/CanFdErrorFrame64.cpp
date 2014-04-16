/*
 * Copyright (C) 2013 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#include "CanFdErrorFrame64.h"

namespace Vector {
namespace BLF {

CanFdErrorFrame64::CanFdErrorFrame64() :
    ObjectHeader(),
    channel(),
    dlc(),
    validDataBytes(),
    ecc(),
    flags(),
    errorCodeExt(),
    extFlags(),
    reserved1(),
    id(),
    frameLength(),
    btrCfgArb(),
    btrCfgData(),
    timeOffsetBrsNs(),
    timeOffsetCrcDelNs(),
    crc(),
    errorPosition(),
    reserved2(),
    data()
{
}

char * CanFdErrorFrame64::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy((char *) &dlc, buffer, size);
    buffer += size;

    // validDataBytes
    size = sizeof(validDataBytes);
    memcpy((char *) &validDataBytes, buffer, size);
    buffer += size;

    // ecc
    size = sizeof(ecc);
    memcpy((char *) &ecc, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((char *) &flags, buffer, size);
    buffer += size;

    // errorCodeExt
    size = sizeof(errorCodeExt);
    memcpy((char *) &errorCodeExt, buffer, size);
    buffer += size;

    // extFlags
    size = sizeof(extFlags);
    memcpy((char *) &extFlags, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((char *) &reserved1, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((char *) &id, buffer, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy((char *) &frameLength, buffer, size);
    buffer += size;

    // btrCfgArb
    size = sizeof(btrCfgArb);
    memcpy((char *) &btrCfgArb, buffer, size);
    buffer += size;

    // btrCfgData
    size = sizeof(btrCfgData);
    memcpy((char *) &btrCfgData, buffer, size);
    buffer += size;

    // timeOffsetBrsNs
    size = sizeof(timeOffsetBrsNs);
    memcpy((char *) &timeOffsetBrsNs, buffer, size);
    buffer += size;

    // timeOffsetCrcDelNs
    size = sizeof(timeOffsetCrcDelNs);
    memcpy((char *) &timeOffsetCrcDelNs, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((char *) &crc, buffer, size);
    buffer += size;

    // errorPosition
    size = sizeof(errorPosition);
    memcpy((char *) &errorPosition, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((char *) &reserved2, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((char *) &data, buffer, size);
    buffer += size;

    return buffer;
}

size_t CanFdErrorFrame64::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(channel) +
            sizeof(dlc) +
            sizeof(validDataBytes) +
            sizeof(ecc) +
            sizeof(flags) +
            sizeof(errorCodeExt) +
            sizeof(extFlags) +
            sizeof(reserved1) +
            sizeof(id) +
            sizeof(frameLength) +
            sizeof(btrCfgArb) +
            sizeof(btrCfgData) +
            sizeof(timeOffsetBrsNs) +
            sizeof(timeOffsetCrcDelNs) +
            sizeof(crc) +
            sizeof(errorPosition) +
            sizeof(reserved2) +
            sizeof(data);

    return size;
}

}
}
