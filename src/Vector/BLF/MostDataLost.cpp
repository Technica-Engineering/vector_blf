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

#include "MostDataLost.h"

#include <cstring>

namespace Vector {
namespace BLF {

MostDataLost::MostDataLost() :
    ObjectHeader2(),
    channel(),
    reserved(),
    info(),
    lostMsgsCtrl(),
    lostMsgsAsync(),
    lastGoodTimeStampNs(),
    nextGoodTimeStampNs()
{
}

char * MostDataLost::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader2::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // info
    size = sizeof(info);
    memcpy((void *) &info, buffer, size);
    buffer += size;

    // lostMsgsCtrl
    size = sizeof(lostMsgsCtrl);
    memcpy((void *) &lostMsgsCtrl, buffer, size);
    buffer += size;

    // lostMsgsAsync
    size = sizeof(lostMsgsAsync);
    memcpy((void *) &lostMsgsAsync, buffer, size);
    buffer += size;

    // lastGoodTimeStampNs
    size = sizeof(lastGoodTimeStampNs);
    memcpy((void *) &lastGoodTimeStampNs, buffer, size);
    buffer += size;

    // nextGoodTimeStampNs
    size = sizeof(nextGoodTimeStampNs);
    memcpy((void *) &nextGoodTimeStampNs, buffer, size);
    buffer += size;

    return buffer;
}

size_t MostDataLost::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reserved) +
        sizeof(info) +
        sizeof(lostMsgsCtrl) +
        sizeof(lostMsgsAsync) +
        sizeof(lastGoodTimeStampNs) +
        sizeof(nextGoodTimeStampNs);

    return size;
}

}
}
