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

#include "LinDisturbanceEvent.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinDisturbanceEvent::LinDisturbanceEvent() :
    ObjectHeader(),
    channel(),
    id(),
    disturbingFrameId(),
    disturbanceType(),
    byteIndex(),
    bitIndex(),
    bitOffsetInSixteenthBits(),
    disturbanceLengthInSixteenthBits()
{
}

char * LinDisturbanceEvent::read(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((void *) &id, buffer, size);
    buffer += size;

    // disturbingFrameId
    size = sizeof(disturbingFrameId);
    memcpy((void *) &disturbingFrameId, buffer, size);
    buffer += size;

    // disturbanceType
    size = sizeof(disturbanceType);
    memcpy((void *) &disturbanceType, buffer, size);
    buffer += size;

    // byteIndex
    size = sizeof(byteIndex);
    memcpy((void *) &byteIndex, buffer, size);
    buffer += size;

    // bitIndex
    size = sizeof(bitIndex);
    memcpy((void *) &bitIndex, buffer, size);
    buffer += size;

    // bitOffsetInSixteenthBits
    size = sizeof(bitOffsetInSixteenthBits);
    memcpy((void *) &bitOffsetInSixteenthBits, buffer, size);
    buffer += size;

    // disturbanceLengthInSixteenthBits
    size = sizeof(disturbanceLengthInSixteenthBits);
    memcpy((void *) &disturbanceLengthInSixteenthBits, buffer, size);
    buffer += size;

    return buffer;
}

char * LinDisturbanceEvent::write(char * buffer)
{
    // @todo
}

size_t LinDisturbanceEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(disturbingFrameId) +
        sizeof(disturbanceType) +
        sizeof(byteIndex) +
        sizeof(bitIndex) +
        sizeof(bitOffsetInSixteenthBits) +
        sizeof(disturbanceLengthInSixteenthBits);

    return size;
}

}
}
