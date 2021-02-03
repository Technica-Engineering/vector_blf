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

#include <Vector/BLF/RestorePoints.h>

#include <algorithm>

namespace Vector {
namespace BLF {

void RestorePoints::read(AbstractFile & is) {
    is.read(reinterpret_cast<char *>(&objectSize), sizeof(objectSize));
    is.read(reinterpret_cast<char *>(&objectInterval), sizeof(objectInterval));
    restorePoints.resize((objectSize - calculateObjectSize()) / RestorePoint::calculateObjectSize()); // all remaining data
    is.read(reinterpret_cast<char *>(restorePoints.data()), static_cast<std::streamsize>(restorePoints.size()) * RestorePoint::calculateObjectSize());
}

void RestorePoints::write(AbstractFile & os) {
    /* pre processing */
    objectSize = calculateObjectSize();

    os.write(reinterpret_cast<char *>(&objectSize), sizeof(objectSize));
    os.write(reinterpret_cast<char *>(&objectInterval), sizeof(objectInterval));
    os.write(reinterpret_cast<char *>(restorePoints.data()), static_cast<std::streamsize>(restorePoints.size()) * RestorePoint::calculateObjectSize());
}

uint32_t RestorePoints::calculateObjectSize() const {
    return
        sizeof(objectSize) +
        sizeof(objectInterval) +
        restorePoints.size() * RestorePoint::calculateObjectSize();
}

}
}
