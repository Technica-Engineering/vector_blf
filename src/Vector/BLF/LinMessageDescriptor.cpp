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

#include <Vector/BLF/LinMessageDescriptor.h>

namespace Vector {
namespace BLF {

void LinMessageDescriptor::read(AbstractFile & is) {
    LinSynchFieldEvent::read(is);
    is.read(reinterpret_cast<char *>(&supplierId), sizeof(supplierId));
    is.read(reinterpret_cast<char *>(&messageId), sizeof(messageId));
    is.read(reinterpret_cast<char *>(&nad), sizeof(nad));
    is.read(reinterpret_cast<char *>(&id), sizeof(id));
    is.read(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    is.read(reinterpret_cast<char *>(&checksumModel), sizeof(checksumModel));
}

void LinMessageDescriptor::write(AbstractFile & os) {
    LinSynchFieldEvent::write(os);
    os.write(reinterpret_cast<char *>(&supplierId), sizeof(supplierId));
    os.write(reinterpret_cast<char *>(&messageId), sizeof(messageId));
    os.write(reinterpret_cast<char *>(&nad), sizeof(nad));
    os.write(reinterpret_cast<char *>(&id), sizeof(id));
    os.write(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    os.write(reinterpret_cast<char *>(&checksumModel), sizeof(checksumModel));
}

uint32_t LinMessageDescriptor::calculateObjectSize() const {
    return
        LinSynchFieldEvent::calculateObjectSize() +
        sizeof(supplierId) +
        sizeof(messageId) +
        sizeof(nad) +
        sizeof(id) +
        sizeof(dlc) +
        sizeof(checksumModel);
}

}
}
