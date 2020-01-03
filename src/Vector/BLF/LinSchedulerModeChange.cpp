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

#include <Vector/BLF/LinSchedulerModeChange.h>

namespace Vector {
namespace BLF {

LinSchedulerModeChange::LinSchedulerModeChange() :
    ObjectHeader() {
    objectType = ObjectType::LIN_SCHED_MODCH;
}

void LinSchedulerModeChange::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&oldMode), sizeof(oldMode));
    is.read(reinterpret_cast<char *>(&newMode), sizeof(newMode));
    is.read(reinterpret_cast<char *>(&reservedLinSchedulerModeChange), sizeof(reservedLinSchedulerModeChange));
}

void LinSchedulerModeChange::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&oldMode), sizeof(oldMode));
    os.write(reinterpret_cast<char *>(&newMode), sizeof(newMode));
    os.write(reinterpret_cast<char *>(&reservedLinSchedulerModeChange), sizeof(reservedLinSchedulerModeChange));
}

DWORD LinSchedulerModeChange::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(oldMode) +
        sizeof(newMode) +
        sizeof(reservedLinSchedulerModeChange);

}

}
}
