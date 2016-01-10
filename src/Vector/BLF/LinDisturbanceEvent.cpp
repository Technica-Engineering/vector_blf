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
    objectType = ObjectType::LIN_DISTURBANCE_EVENT;
}

void LinDisturbanceEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &id, sizeof(id));
    is.read((char *) &disturbingFrameId, sizeof(disturbingFrameId));
    is.read((char *) &disturbanceType, sizeof(disturbanceType));
    is.read((char *) &byteIndex, sizeof(byteIndex));
    is.read((char *) &bitIndex, sizeof(bitIndex));
    is.read((char *) &bitOffsetInSixteenthBits, sizeof(bitOffsetInSixteenthBits));
    is.read((char *) &disturbanceLengthInSixteenthBits, sizeof(disturbanceLengthInSixteenthBits));
}

void LinDisturbanceEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &id, sizeof(id));
    os.write((char *) &disturbingFrameId, sizeof(disturbingFrameId));
    os.write((char *) &disturbanceType, sizeof(disturbanceType));
    os.write((char *) &byteIndex, sizeof(byteIndex));
    os.write((char *) &bitIndex, sizeof(bitIndex));
    os.write((char *) &bitOffsetInSixteenthBits, sizeof(bitOffsetInSixteenthBits));
    os.write((char *) &disturbanceLengthInSixteenthBits, sizeof(disturbanceLengthInSixteenthBits));
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
