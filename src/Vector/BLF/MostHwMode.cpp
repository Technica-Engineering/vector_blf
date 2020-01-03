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

#include <Vector/BLF/MostHwMode.h>

namespace Vector {
namespace BLF {

MostHwMode::MostHwMode() :
    ObjectHeader2() {
    objectType = ObjectType::MOST_HWMODE;
}

void MostHwMode::read(AbstractFile & is) {
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&reservedMostHwMode), sizeof(reservedMostHwMode));
    is.read(reinterpret_cast<char *>(&hwMode), sizeof(hwMode));
    is.read(reinterpret_cast<char *>(&hwModeMask), sizeof(hwModeMask));
}

void MostHwMode::write(AbstractFile & os) {
    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&reservedMostHwMode), sizeof(reservedMostHwMode));
    os.write(reinterpret_cast<char *>(&hwMode), sizeof(hwMode));
    os.write(reinterpret_cast<char *>(&hwModeMask), sizeof(hwModeMask));
}

DWORD MostHwMode::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedMostHwMode) +
        sizeof(hwMode) +
        sizeof(hwModeMask);
}

}
}
