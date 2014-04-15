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
    reserved1(),
    reserved2(),
    data()
{
}

char * CanFdMessage64::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

#if 0
    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;
#else
    // @todo
#endif

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
            sizeof(reserved1) +
            sizeof(reserved2) +
            sizeof(data);
}

}
}
