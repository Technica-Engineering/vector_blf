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

#include <Vector/BLF/LinSyncError.h>

namespace Vector {
namespace BLF {

LinSyncError::LinSyncError() :
    ObjectHeader(ObjectType::LIN_SYN_ERROR) {
}

void LinSyncError::read(RawFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&reservedLinSyncError1), sizeof(reservedLinSyncError1));
    is.read(reinterpret_cast<char *>(timeDiff.data()), static_cast<std::streamsize>(timeDiff.size() * sizeof(WORD)));
    is.read(reinterpret_cast<char *>(&reservedLinSyncError2), sizeof(reservedLinSyncError2));
}

void LinSyncError::write(RawFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&reservedLinSyncError1), sizeof(reservedLinSyncError1));
    os.write(reinterpret_cast<char *>(timeDiff.data()), static_cast<std::streamsize>(timeDiff.size() * sizeof(WORD)));
    os.write(reinterpret_cast<char *>(&reservedLinSyncError2), sizeof(reservedLinSyncError2));
}

DWORD LinSyncError::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedLinSyncError1) +
        static_cast<DWORD>(timeDiff.size() * sizeof(WORD)) +
        sizeof(reservedLinSyncError2);
}

}
}
