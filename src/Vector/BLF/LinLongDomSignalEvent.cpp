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

#include <Vector/BLF/LinLongDomSignalEvent.h>

namespace Vector {
namespace BLF {

LinLongDomSignalEvent::LinLongDomSignalEvent() :
    ObjectHeader(ObjectType::LIN_LONG_DOM_SIG) {
}

void LinLongDomSignalEvent::read(AbstractFile & is) {
    ObjectHeader::read(is);
    LinBusEvent::read(is);
    is.read(reinterpret_cast<char *>(&type), sizeof(type));
    is.read(reinterpret_cast<char *>(&reservedLinLongDomSignalEvent1), sizeof(reservedLinLongDomSignalEvent1));
    is.read(reinterpret_cast<char *>(&reservedLinLongDomSignalEvent2), sizeof(reservedLinLongDomSignalEvent2));
    is.read(reinterpret_cast<char *>(&reservedLinLongDomSignalEvent3), sizeof(reservedLinLongDomSignalEvent3));
}

void LinLongDomSignalEvent::write(AbstractFile & os) {
    ObjectHeader::write(os);
    LinBusEvent::write(os);
    os.write(reinterpret_cast<char *>(&type), sizeof(type));
    os.write(reinterpret_cast<char *>(&reservedLinLongDomSignalEvent1), sizeof(reservedLinLongDomSignalEvent1));
    os.write(reinterpret_cast<char *>(&reservedLinLongDomSignalEvent2), sizeof(reservedLinLongDomSignalEvent2));
    os.write(reinterpret_cast<char *>(&reservedLinLongDomSignalEvent3), sizeof(reservedLinLongDomSignalEvent3));
}

DWORD LinLongDomSignalEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(type) +
        sizeof(reservedLinLongDomSignalEvent1) +
        sizeof(reservedLinLongDomSignalEvent2) +
        sizeof(reservedLinLongDomSignalEvent3);
}

}
}
