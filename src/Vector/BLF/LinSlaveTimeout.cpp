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

#include "LinSlaveTimeout.h"

namespace Vector {
namespace BLF {

LinSlaveTimeout::LinSlaveTimeout() :
    ObjectHeader(),
    channel(),
    slaveId(),
    stateId(),
    followStateId()
{
    objectType = ObjectType::LIN_SLV_TIMEOUT;
}

void LinSlaveTimeout::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &slaveId, sizeof(slaveId));
    is.read((char *) &stateId, sizeof(stateId));
    is.read((char *) &followStateId, sizeof(followStateId));
}

void LinSlaveTimeout::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &slaveId, sizeof(slaveId));
    os.write((char *) &stateId, sizeof(stateId));
    os.write((char *) &followStateId, sizeof(followStateId));
}

size_t LinSlaveTimeout::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(slaveId) +
        sizeof(stateId) +
        sizeof(followStateId);

    return size;
}

}
}
