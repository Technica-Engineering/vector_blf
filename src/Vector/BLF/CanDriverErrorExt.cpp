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

#include <Vector/BLF/CanDriverErrorExt.h>

namespace Vector {
namespace BLF {

CanDriverErrorExt::CanDriverErrorExt() :
    ObjectHeader() {
    objectType = ObjectType::CAN_DRIVER_ERROR_EXT;
}

void CanDriverErrorExt::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&txErrors), sizeof(txErrors));
    is.read(reinterpret_cast<char *>(&rxErrors), sizeof(rxErrors));
    is.read(reinterpret_cast<char *>(&errorCode), sizeof(errorCode));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&state), sizeof(state));
    is.read(reinterpret_cast<char *>(&reservedCanDriverErrorExt1), sizeof(reservedCanDriverErrorExt1));
    is.read(reinterpret_cast<char *>(&reservedCanDriverErrorExt2), sizeof(reservedCanDriverErrorExt2));
    is.read(reinterpret_cast<char *>(reservedCanDriverErrorExt3.data()), static_cast<std::streamsize>(reservedCanDriverErrorExt3.size() * sizeof(DWORD)));
}

void CanDriverErrorExt::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&txErrors), sizeof(txErrors));
    os.write(reinterpret_cast<char *>(&rxErrors), sizeof(rxErrors));
    os.write(reinterpret_cast<char *>(&errorCode), sizeof(errorCode));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&state), sizeof(state));
    os.write(reinterpret_cast<char *>(&reservedCanDriverErrorExt1), sizeof(reservedCanDriverErrorExt1));
    os.write(reinterpret_cast<char *>(&reservedCanDriverErrorExt2), sizeof(reservedCanDriverErrorExt2));
    os.write(reinterpret_cast<char *>(reservedCanDriverErrorExt3.data()), static_cast<std::streamsize>(reservedCanDriverErrorExt3.size() * sizeof(DWORD)));
}

DWORD CanDriverErrorExt::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(txErrors) +
        sizeof(rxErrors) +
        sizeof(errorCode) +
        sizeof(flags) +
        sizeof(state) +
        sizeof(reservedCanDriverErrorExt1) +
        sizeof(reservedCanDriverErrorExt2) +
        static_cast<DWORD>(reservedCanDriverErrorExt3.size() * sizeof(DWORD));
}

}
}
