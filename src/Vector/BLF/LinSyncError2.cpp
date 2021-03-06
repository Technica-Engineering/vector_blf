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

#include <Vector/BLF/LinSyncError2.h>

namespace Vector {
namespace BLF {

LinSyncError2::LinSyncError2() :
    ObjectHeader(ObjectType::LIN_SYN_ERROR2) {
}

void LinSyncError2::read(AbstractFile & is) {
    ObjectHeader::read(is);
    LinSynchFieldEvent::read(is);
    is.read(reinterpret_cast<char *>(timeDiff.data()), static_cast<std::streamsize>(timeDiff.size() * sizeof(uint16_t)));
    // @note might be extended in future versions
}

void LinSyncError2::write(AbstractFile & os) {
    ObjectHeader::write(os);
    LinSynchFieldEvent::write(os);
    os.write(reinterpret_cast<char *>(timeDiff.data()), static_cast<std::streamsize>(timeDiff.size() * sizeof(uint16_t)));
}

uint32_t LinSyncError2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinSynchFieldEvent::calculateObjectSize() +
        static_cast<uint32_t>(timeDiff.size() * sizeof(uint16_t));
}

}
}
