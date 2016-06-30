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

#include "CanFdMessage.h"

namespace Vector {
namespace BLF {

CanFdMessage::CanFdMessage() :
    ObjectHeader(),
    channel(),
    flags(),
    dlc(),
    id(),
    frameLength(),
    arbBitCount(),
    canFdFlags(),
    validDataBytes(),
    reserved1(),
    reserved2(),
    data()
{
    objectType = ObjectType::CAN_FD_MESSAGE;
}

void CanFdMessage::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    is.read(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    is.read(reinterpret_cast<char *>(&arbBitCount), sizeof(arbBitCount));
    is.read(reinterpret_cast<char *>(&canFdFlags), sizeof(canFdFlags));
    is.read(reinterpret_cast<char *>(&validDataBytes), sizeof(validDataBytes));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    is.read(reinterpret_cast<char *>(data.data()), data.size());
}

void CanFdMessage::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    os.write(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    os.write(reinterpret_cast<char *>(&arbBitCount), sizeof(arbBitCount));
    os.write(reinterpret_cast<char *>(&canFdFlags), sizeof(canFdFlags));
    os.write(reinterpret_cast<char *>(&validDataBytes), sizeof(validDataBytes));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    os.write(reinterpret_cast<char *>(data.data()), data.size());
}

DWORD CanFdMessage::calculateObjectSize()
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(dlc) +
        sizeof(id) +
        sizeof(frameLength) +
        sizeof(arbBitCount) +
        sizeof(canFdFlags) +
        sizeof(validDataBytes) +
        sizeof(reserved1) +
        sizeof(reserved2) +
        data.size();
}

}
}
