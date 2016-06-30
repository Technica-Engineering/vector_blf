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

#include "LinSendError.h"

namespace Vector {
namespace BLF {

LinSendError::LinSendError() :
    ObjectHeader(),
    channel(),
    id(),
    dlc(),
    fsmId(),
    fsmState(),
    headerTime(),
    fullTime()
{
    objectType = ObjectType::LIN_SND_ERROR;
}

void LinSendError::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&id), sizeof(id));
    is.read(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    is.read(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    is.read(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    is.read(reinterpret_cast<char *>(&headerTime), sizeof(headerTime));
    is.read(reinterpret_cast<char *>(&fullTime), sizeof(fullTime));
}

void LinSendError::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&id), sizeof(id));
    os.write(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    os.write(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    os.write(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    os.write(reinterpret_cast<char *>(&headerTime), sizeof(headerTime));
    os.write(reinterpret_cast<char *>(&fullTime), sizeof(fullTime));
}

DWORD LinSendError::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(dlc) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(headerTime) +
        sizeof(fullTime);
}

}
}
