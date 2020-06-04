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

#include <Vector/BLF/MostGenReg.h>

namespace Vector {
namespace BLF {

MostGenReg::MostGenReg() :
    ObjectHeader2(ObjectType::MOST_GENREG) {
}

void MostGenReg::read(RawFile & is) {
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&subType), sizeof(subType));
    is.read(reinterpret_cast<char *>(&reservedMostGenReg1), sizeof(reservedMostGenReg1));
    is.read(reinterpret_cast<char *>(&handle), sizeof(handle));
    is.read(reinterpret_cast<char *>(&regId), sizeof(regId));
    is.read(reinterpret_cast<char *>(&reservedMostGenReg2), sizeof(reservedMostGenReg2));
    is.read(reinterpret_cast<char *>(&reservedMostGenReg3), sizeof(reservedMostGenReg3));
    is.read(reinterpret_cast<char *>(&regValue), sizeof(regValue));
}

void MostGenReg::write(RawFile & os) {
    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&subType), sizeof(subType));
    os.write(reinterpret_cast<char *>(&reservedMostGenReg1), sizeof(reservedMostGenReg1));
    os.write(reinterpret_cast<char *>(&handle), sizeof(handle));
    os.write(reinterpret_cast<char *>(&regId), sizeof(regId));
    os.write(reinterpret_cast<char *>(&reservedMostGenReg2), sizeof(reservedMostGenReg2));
    os.write(reinterpret_cast<char *>(&reservedMostGenReg3), sizeof(reservedMostGenReg3));
    os.write(reinterpret_cast<char *>(&regValue), sizeof(regValue));
}

DWORD MostGenReg::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(subType) +
        sizeof(reservedMostGenReg1) +
        sizeof(handle) +
        sizeof(regId) +
        sizeof(reservedMostGenReg2) +
        sizeof(reservedMostGenReg3) +
        sizeof(regValue);
}

}
}
