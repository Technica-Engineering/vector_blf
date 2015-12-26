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

#include <cstring>

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

char * CanFdErrorFrame64::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy((void *) &dlc, buffer, size);
    buffer += size;

    // validDataBytes
    size = sizeof(validDataBytes);
    memcpy((void *) &validDataBytes, buffer, size);
    buffer += size;

    // ecc
    size = sizeof(ecc);
    memcpy((void *) &ecc, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
    buffer += size;

    // errorCodeExt
    size = sizeof(errorCodeExt);
    memcpy((void *) &errorCodeExt, buffer, size);
    buffer += size;

    // extFlags
    size = sizeof(extFlags);
    memcpy((void *) &extFlags, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((void *) &id, buffer, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy((void *) &frameLength, buffer, size);
    buffer += size;

    // btrCfgArb
    size = sizeof(btrCfgArb);
    memcpy((void *) &btrCfgArb, buffer, size);
    buffer += size;

    // btrCfgData
    size = sizeof(btrCfgData);
    memcpy((void *) &btrCfgData, buffer, size);
    buffer += size;

    // timeOffsetBrsNs
    size = sizeof(timeOffsetBrsNs);
    memcpy((void *) &timeOffsetBrsNs, buffer, size);
    buffer += size;

    // timeOffsetCrcDelNs
    size = sizeof(timeOffsetCrcDelNs);
    memcpy((void *) &timeOffsetCrcDelNs, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((void *) &crc, buffer, size);
    buffer += size;

    // errorPosition
    size = sizeof(errorPosition);
    memcpy((void *) &errorPosition, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((void *) &data, buffer, size);
    buffer += size;

    return buffer;
}

char * CanFdErrorFrame64::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy(buffer, (void *) &dlc, size);
    buffer += size;

    // validDataBytes
    size = sizeof(validDataBytes);
    memcpy(buffer, (void *) &validDataBytes, size);
    buffer += size;

    // ecc
    size = sizeof(ecc);
    memcpy(buffer, (void *) &ecc, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy(buffer, (void *) &flags, size);
    buffer += size;

    // errorCodeExt
    size = sizeof(errorCodeExt);
    memcpy(buffer, (void *) &errorCodeExt, size);
    buffer += size;

    // extFlags
    size = sizeof(extFlags);
    memcpy(buffer, (void *) &extFlags, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy(buffer, (void *) &id, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy(buffer, (void *) &frameLength, size);
    buffer += size;

    // btrCfgArb
    size = sizeof(btrCfgArb);
    memcpy(buffer, (void *) &btrCfgArb, size);
    buffer += size;

    // btrCfgData
    size = sizeof(btrCfgData);
    memcpy(buffer, (void *) &btrCfgData, size);
    buffer += size;

    // timeOffsetBrsNs
    size = sizeof(timeOffsetBrsNs);
    memcpy(buffer, (void *) &timeOffsetBrsNs, size);
    buffer += size;

    // timeOffsetCrcDelNs
    size = sizeof(timeOffsetCrcDelNs);
    memcpy(buffer, (void *) &timeOffsetCrcDelNs, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy(buffer, (void *) &crc, size);
    buffer += size;

    // errorPosition
    size = sizeof(errorPosition);
    memcpy(buffer, (void *) &errorPosition, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy(buffer, (void *) &data, size);
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
