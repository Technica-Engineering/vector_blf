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

#include "AfdxStatistic.h"

#include <cstring>

namespace Vector {
namespace BLF {

AfdxStatistic::AfdxStatistic() :
    ObjectHeader(),
    channel(),
    flags(),
    rxPacketCount(),
    rxByteCount(),
    txPacketCount(),
    txByteCount(),
    collisionCount(),
    errorCount(),
    statDroppedRedundantPacketCount(),
    statRedundantErrorPacketCount(),
    statIntegrityErrorPacketCount(),
    statAvrgPeriodMsec(),
    statAvrgJitterMysec(),
    vlid(),
    statDuration()
{
}

char * AfdxStatistic::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((char *) &flags, buffer, size);
    buffer += size;

    // rxPacketCount
    size = sizeof(rxPacketCount);
    memcpy((char *) &rxPacketCount, buffer, size);
    buffer += size;

    // rxByteCount
    size = sizeof(rxByteCount);
    memcpy((char *) &rxByteCount, buffer, size);
    buffer += size;

    // txPacketCount
    size = sizeof(txPacketCount);
    memcpy((char *) &txPacketCount, buffer, size);
    buffer += size;

    // txByteCount
    size = sizeof(txByteCount);
    memcpy((char *) &txByteCount, buffer, size);
    buffer += size;

    // collisionCount
    size = sizeof(collisionCount);
    memcpy((char *) &collisionCount, buffer, size);
    buffer += size;

    // errorCount
    size = sizeof(errorCount);
    memcpy((char *) &errorCount, buffer, size);
    buffer += size;

    // statDroppedRedundantPacketCount
    size = sizeof(statDroppedRedundantPacketCount);
    memcpy((char *) &statDroppedRedundantPacketCount, buffer, size);
    buffer += size;

    // statRedundantErrorPacketCount
    size = sizeof(statRedundantErrorPacketCount);
    memcpy((char *) &statRedundantErrorPacketCount, buffer, size);
    buffer += size;

    // statIntegrityErrorPacketCount
    size = sizeof(statIntegrityErrorPacketCount);
    memcpy((char *) &statIntegrityErrorPacketCount, buffer, size);
    buffer += size;

    // statAvrgPeriodMsec
    size = sizeof(statAvrgPeriodMsec);
    memcpy((char *) &statAvrgPeriodMsec, buffer, size);
    buffer += size;

    // statAvrgJitterMysec
    size = sizeof(statAvrgJitterMysec);
    memcpy((char *) &statAvrgJitterMysec, buffer, size);
    buffer += size;

    // vlid
    size = sizeof(vlid);
    memcpy((char *) &vlid, buffer, size);
    buffer += size;

    // statDuration
    size = sizeof(statDuration);
    memcpy((char *) &statDuration, buffer, size);
    buffer += size;

    return buffer;
}

}
}
