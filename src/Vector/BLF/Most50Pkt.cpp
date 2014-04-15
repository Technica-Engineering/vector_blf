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

#include "Most50Pkt.h"

namespace Vector {
namespace BLF {

Most50Pkt::Most50Pkt() :
    ObjectHeader2(),
    channel(),
    dir(),
    dummy1(),
    sourceAdr(),
    destAdr(),
    transferType(),
    state(),
    ackNack(),
    dummy2(),
    crc(),
    dummy3(),
    dummy4(),
    priority(),
    dummy5(),
    pktDataLength(),
    pktData(nullptr)
{
}

Most50Pkt::~Most50Pkt()
{
    delete[] pktData;
    pktData = nullptr;
}

char * Most50Pkt::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader2::parse(buffer);

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

size_t Most50Pkt::calculateObjectSize()
{
    size_t size =
            ObjectHeader2::calculateObjectSize() +
            sizeof(channel) +
            sizeof(dir) +
            sizeof(dummy1) +
            sizeof(sourceAdr) +
            sizeof(destAdr) +
            sizeof(transferType) +
            sizeof(state) +
            sizeof(ackNack) +
            sizeof(dummy2) +
            sizeof(crc) +
            sizeof(dummy3) +
            sizeof(dummy4) +
            sizeof(priority) +
            sizeof(dummy5) +
            sizeof(pktDataLength) +
            pktDataLength;

    return size;
}

}
}
