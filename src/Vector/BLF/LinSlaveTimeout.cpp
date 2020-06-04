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

#include <Vector/BLF/LinSlaveTimeout.h>

namespace Vector {
namespace BLF {

LinSlaveTimeout::LinSlaveTimeout() :
    ObjectHeader(ObjectType::LIN_SLV_TIMEOUT) {
}

void LinSlaveTimeout::read(RawFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&slaveId), sizeof(slaveId));
    is.read(reinterpret_cast<char *>(&stateId), sizeof(stateId));
    is.read(reinterpret_cast<char *>(&followStateId), sizeof(followStateId));
}

void LinSlaveTimeout::write(RawFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&slaveId), sizeof(slaveId));
    os.write(reinterpret_cast<char *>(&stateId), sizeof(stateId));
    os.write(reinterpret_cast<char *>(&followStateId), sizeof(followStateId));
}

DWORD LinSlaveTimeout::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(slaveId) +
        sizeof(stateId) +
        sizeof(followStateId);
}

}
}
