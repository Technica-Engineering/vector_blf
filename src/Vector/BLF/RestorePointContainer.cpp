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

#include <Vector/BLF/RestorePointContainer.h>

namespace Vector {
namespace BLF {

RestorePointContainer::RestorePointContainer() :
    ObjectHeader(ObjectType::Unknown115) {
}

void RestorePointContainer::read(AbstractFile & is) {
    ObjectHeader::read(is);

    is.read(reinterpret_cast<char *>(reservedRestorePointContainer.data()), static_cast<std::streamsize>(reservedRestorePointContainer.size()));
    is.read(reinterpret_cast<char *>(&dataLength), sizeof(dataLength));
    data.resize(dataLength);
    is.read(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
}

void RestorePointContainer::write(AbstractFile & os) {
    /* pre processing */
    dataLength = static_cast<uint16_t>(data.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(reservedRestorePointContainer.data()), static_cast<std::streamsize>(reservedRestorePointContainer.size()));
    os.write(reinterpret_cast<char *>(&dataLength), sizeof(dataLength));
    os.write(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
}

uint32_t RestorePointContainer::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        static_cast<uint32_t>(reservedRestorePointContainer.size()) +
        sizeof(dataLength) +
        dataLength;
}

}
}
