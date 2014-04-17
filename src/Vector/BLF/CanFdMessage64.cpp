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
}

char * CanFdMessage64::parse(char * buffer)
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

    // txCount
    size = sizeof(txCount);
    memcpy((char *) &txCount, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((char *) &id, buffer, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy((char *) &frameLength, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((char *) &flags, buffer, size);
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

    // bitCount
    size = sizeof(bitCount);
    memcpy((char *) &bitCount, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((char *) &data, buffer, size);
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
