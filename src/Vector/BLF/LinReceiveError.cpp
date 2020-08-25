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

#include <Vector/BLF/LinReceiveError.h>

namespace Vector {
namespace BLF {

LinReceiveError::LinReceiveError() :
    ObjectHeader(ObjectType::LIN_RCV_ERROR) {
}

void LinReceiveError::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&id), sizeof(id));
    is.read(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    is.read(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    is.read(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    is.read(reinterpret_cast<char *>(&headerTime), sizeof(headerTime));
    is.read(reinterpret_cast<char *>(&fullTime), sizeof(fullTime));
    is.read(reinterpret_cast<char *>(&stateReason), sizeof(stateReason));
    is.read(reinterpret_cast<char *>(&offendingByte), sizeof(offendingByte));
    is.read(reinterpret_cast<char *>(&shortError), sizeof(shortError));
    is.read(reinterpret_cast<char *>(&timeoutDuringDlcDetection), sizeof(timeoutDuringDlcDetection));
    is.read(reinterpret_cast<char *>(&reservedLinReceiveError), sizeof(reservedLinReceiveError));
}

void LinReceiveError::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&id), sizeof(id));
    os.write(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    os.write(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    os.write(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    os.write(reinterpret_cast<char *>(&headerTime), sizeof(headerTime));
    os.write(reinterpret_cast<char *>(&fullTime), sizeof(fullTime));
    os.write(reinterpret_cast<char *>(&stateReason), sizeof(stateReason));
    os.write(reinterpret_cast<char *>(&offendingByte), sizeof(offendingByte));
    os.write(reinterpret_cast<char *>(&shortError), sizeof(shortError));
    os.write(reinterpret_cast<char *>(&timeoutDuringDlcDetection), sizeof(timeoutDuringDlcDetection));
    os.write(reinterpret_cast<char *>(&reservedLinReceiveError), sizeof(reservedLinReceiveError));
}

DWORD LinReceiveError::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(dlc) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(headerTime) +
        sizeof(fullTime) +
        sizeof(stateReason) +
        sizeof(offendingByte) +
        sizeof(shortError) +
        sizeof(timeoutDuringDlcDetection) +
        sizeof(reservedLinReceiveError);
}

}
}
