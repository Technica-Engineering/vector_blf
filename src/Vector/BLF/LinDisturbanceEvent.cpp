/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/LinDisturbanceEvent.h>

namespace Vector {
namespace BLF {

LinDisturbanceEvent::LinDisturbanceEvent() :
    ObjectHeader(ObjectType::LIN_DISTURBANCE_EVENT) {
}

void LinDisturbanceEvent::read(RawFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&id), sizeof(id));
    is.read(reinterpret_cast<char *>(&disturbingFrameId), sizeof(disturbingFrameId));
    is.read(reinterpret_cast<char *>(&disturbanceType), sizeof(disturbanceType));
    is.read(reinterpret_cast<char *>(&byteIndex), sizeof(byteIndex));
    is.read(reinterpret_cast<char *>(&bitIndex), sizeof(bitIndex));
    is.read(reinterpret_cast<char *>(&bitOffsetInSixteenthBits), sizeof(bitOffsetInSixteenthBits));
    is.read(reinterpret_cast<char *>(&disturbanceLengthInSixteenthBits), sizeof(disturbanceLengthInSixteenthBits));
    // @note might be extended in future versions
}

void LinDisturbanceEvent::write(RawFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&id), sizeof(id));
    os.write(reinterpret_cast<char *>(&disturbingFrameId), sizeof(disturbingFrameId));
    os.write(reinterpret_cast<char *>(&disturbanceType), sizeof(disturbanceType));
    os.write(reinterpret_cast<char *>(&byteIndex), sizeof(byteIndex));
    os.write(reinterpret_cast<char *>(&bitIndex), sizeof(bitIndex));
    os.write(reinterpret_cast<char *>(&bitOffsetInSixteenthBits), sizeof(bitOffsetInSixteenthBits));
    os.write(reinterpret_cast<char *>(&disturbanceLengthInSixteenthBits), sizeof(disturbanceLengthInSixteenthBits));
}

DWORD LinDisturbanceEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(disturbingFrameId) +
        sizeof(disturbanceType) +
        sizeof(byteIndex) +
        sizeof(bitIndex) +
        sizeof(bitOffsetInSixteenthBits) +
        sizeof(disturbanceLengthInSixteenthBits);
}

}
}
