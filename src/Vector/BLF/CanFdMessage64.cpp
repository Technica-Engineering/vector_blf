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

#include "CanFdMessage64.h"

#include <cstring>

namespace Vector {
namespace BLF {

CanFdMessage64::CanFdMessage64() :
    ObjectHeader(),
    channel(),
    dlc(),
    validDataBytes(),
    txCount(),
    id(),
    frameLength(),
    flags(),
    btrCfgArb(),
    btrCfgData(),
    timeOffsetBrsNs(),
    timeOffsetCrcDelNs(),
    bitCount(),
    dir(),
    reserved(),
    data()
{
    objectType = ObjectType::CAN_FD_MESSAGE_64;
}

char * CanFdMessage64::read(char * buffer)
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

    // txCount
    size = sizeof(txCount);
    memcpy((void *) &txCount, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((void *) &id, buffer, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy((void *) &frameLength, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
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

    // bitCount
    size = sizeof(bitCount);
    memcpy((void *) &bitCount, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((void *) &dir, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((void *) &data, buffer, size);
    buffer += size;

    return buffer;
}

char * CanFdMessage64::write(char * buffer)
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

    // txCount
    size = sizeof(txCount);
    memcpy(buffer, (void *) &txCount, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy(buffer, (void *) &id, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy(buffer, (void *) &frameLength, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy(buffer, (void *) &flags, size);
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

    // bitCount
    size = sizeof(bitCount);
    memcpy(buffer, (void *) &bitCount, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy(buffer, (void *) &dir, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy(buffer, (void *) &data, size);
    buffer += size;

    return buffer;
}

size_t CanFdMessage64::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dlc) +
        sizeof(validDataBytes) +
        sizeof(txCount) +
        sizeof(id) +
        sizeof(frameLength) +
        sizeof(flags) +
        sizeof(btrCfgArb) +
        sizeof(btrCfgData) +
        sizeof(timeOffsetBrsNs) +
        sizeof(timeOffsetCrcDelNs) +
        sizeof(bitCount) +
        sizeof(dir) +
        sizeof(reserved) +
        sizeof(data);

    return size;
}

}
}
