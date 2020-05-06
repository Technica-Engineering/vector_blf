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

#include <Vector/BLF/CanFdMessage.h>

namespace Vector {
namespace BLF {

CanFdMessage::CanFdMessage() :
    ObjectHeader(ObjectType::CAN_FD_MESSAGE) {
}

void CanFdMessage::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    is.read(reinterpret_cast<char *>(&id), sizeof(id));
    is.read(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    is.read(reinterpret_cast<char *>(&arbBitCount), sizeof(arbBitCount));
    is.read(reinterpret_cast<char *>(&canFdFlags), sizeof(canFdFlags));
    is.read(reinterpret_cast<char *>(&validDataBytes), sizeof(validDataBytes));
    is.read(reinterpret_cast<char *>(&reservedCanFdMessage1), sizeof(reservedCanFdMessage1));
    is.read(reinterpret_cast<char *>(&reservedCanFdMessage2), sizeof(reservedCanFdMessage2));
    data.resize(validDataBytes);
    is.read(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    is.read(reinterpret_cast<char *>(&reservedCanFdMessage3), sizeof(reservedCanFdMessage3));
    // @note might be extended in future versions
}

void CanFdMessage::write(AbstractFile & os) {
    /* pre processing */
    validDataBytes = static_cast<WORD>(data.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    os.write(reinterpret_cast<char *>(&id), sizeof(id));
    os.write(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    os.write(reinterpret_cast<char *>(&arbBitCount), sizeof(arbBitCount));
    os.write(reinterpret_cast<char *>(&canFdFlags), sizeof(canFdFlags));
    os.write(reinterpret_cast<char *>(&validDataBytes), sizeof(validDataBytes));
    os.write(reinterpret_cast<char *>(&reservedCanFdMessage1), sizeof(reservedCanFdMessage1));
    os.write(reinterpret_cast<char *>(&reservedCanFdMessage2), sizeof(reservedCanFdMessage2));
    os.write(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    os.write(reinterpret_cast<char *>(&reservedCanFdMessage3), sizeof(reservedCanFdMessage3));
}

DWORD CanFdMessage::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(dlc) +
        sizeof(id) +
        sizeof(frameLength) +
        sizeof(arbBitCount) +
        sizeof(canFdFlags) +
        sizeof(validDataBytes) +
        sizeof(reservedCanFdMessage1) +
        sizeof(reservedCanFdMessage2) +
        static_cast<DWORD>(data.size()) +
        sizeof(reservedCanFdMessage3);
}

}
}
