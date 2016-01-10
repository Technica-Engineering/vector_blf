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

#include "LinCrcError.h"

namespace Vector {
namespace BLF {

LinCrcError::LinCrcError() :
    ObjectHeader(),
    channel(),
    id(),
    dlc(),
    data(),
    fsmId(),
    fsmState(),
    headerTime(),
    fullTime(),
    crc(),
    dir(),
    reserved()
{
    objectType = ObjectType::LIN_CRC_ERROR;
}

void LinCrcError::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &id, sizeof(id));
    is.read((char *) &dlc, sizeof(dlc));
    is.read((char *) data.data(), data.size());
    is.read((char *) &fsmId, sizeof(fsmId));
    is.read((char *) &fsmState, sizeof(fsmState));
    is.read((char *) &headerTime, sizeof(headerTime));
    is.read((char *) &fullTime, sizeof(fullTime));
    is.read((char *) &crc, sizeof(crc));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &reserved, sizeof(reserved));
}

void LinCrcError::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &id, sizeof(id));
    os.write((char *) &dlc, sizeof(dlc));
    os.write((char *) data.data(), data.size());
    os.write((char *) &fsmId, sizeof(fsmId));
    os.write((char *) &fsmState, sizeof(fsmState));
    os.write((char *) &headerTime, sizeof(headerTime));
    os.write((char *) &fullTime, sizeof(fullTime));
    os.write((char *) &crc, sizeof(crc));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &reserved, sizeof(reserved));
}

size_t LinCrcError::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(id) +
        sizeof(dlc) +
        data.size() +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(headerTime) +
        sizeof(fullTime) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(reserved);

    return size;
}

}
}
