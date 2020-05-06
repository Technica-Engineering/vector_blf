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

#include <Vector/BLF/LinSendError2.h>

namespace Vector {
namespace BLF {

LinSendError2::LinSendError2() :
    ObjectHeader(ObjectType::LIN_SND_ERROR2, 1) {
}

void LinSendError2::read(AbstractFile & is) {
    ObjectHeader::read(is);
    LinMessageDescriptor::read(is);
    is.read(reinterpret_cast<char *>(&eoh), sizeof(eoh));
    is.read(reinterpret_cast<char *>(&isEtf), sizeof(isEtf));
    is.read(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    is.read(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    is.read(reinterpret_cast<char *>(&reservedLinSendError1), sizeof(reservedLinSendError1));
    is.read(reinterpret_cast<char *>(&reservedLinSendError2), sizeof(reservedLinSendError2));
    is.read(reinterpret_cast<char *>(&exactHeaderBaudrate), sizeof(exactHeaderBaudrate));
    is.read(reinterpret_cast<char *>(&earlyStopbitOffset), sizeof(earlyStopbitOffset));
    is.read(reinterpret_cast<char *>(&reservedLinSendError3), sizeof(reservedLinSendError3));
    // @note might be extended in future versions
}

void LinSendError2::write(AbstractFile & os) {
    ObjectHeader::write(os);
    LinMessageDescriptor::write(os);
    os.write(reinterpret_cast<char *>(&eoh), sizeof(eoh));
    os.write(reinterpret_cast<char *>(&isEtf), sizeof(isEtf));
    os.write(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    os.write(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    os.write(reinterpret_cast<char *>(&reservedLinSendError1), sizeof(reservedLinSendError1));
    os.write(reinterpret_cast<char *>(&reservedLinSendError2), sizeof(reservedLinSendError2));
    os.write(reinterpret_cast<char *>(&exactHeaderBaudrate), sizeof(exactHeaderBaudrate));
    os.write(reinterpret_cast<char *>(&earlyStopbitOffset), sizeof(earlyStopbitOffset));
    os.write(reinterpret_cast<char *>(&reservedLinSendError3), sizeof(reservedLinSendError3));
}

DWORD LinSendError2::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        LinMessageDescriptor::calculateObjectSize() +
        sizeof(eoh) +
        sizeof(isEtf) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(reservedLinSendError1) +
        sizeof(reservedLinSendError2) +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        sizeof(reservedLinSendError3);
}

}
}
