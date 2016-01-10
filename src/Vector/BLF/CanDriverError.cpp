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

#include "CanDriverError.h"

namespace Vector {
namespace BLF {

CanDriverError::CanDriverError() :
    ObjectHeader(),
    channel(),
    txErrors(),
    rxErrors(),
    errorCode()
{
    objectType = ObjectType::CAN_DRIVER_ERROR;
}

void CanDriverError::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &txErrors, sizeof(txErrors));
    is.read((char *) &rxErrors, sizeof(rxErrors));
    is.read((char *) &errorCode, sizeof(errorCode));
}

void CanDriverError::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &txErrors, sizeof(txErrors));
    os.write((char *) &rxErrors, sizeof(rxErrors));
    os.write((char *) &errorCode, sizeof(errorCode));
}

size_t CanDriverError::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(txErrors) +
        sizeof(rxErrors) +
        sizeof(errorCode);

    return size;
}

}
}
