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
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &dlc, sizeof(dlc));
    is.read((char *) &frameLength, sizeof(frameLength));
    is.read((char *) &arbBitCount, sizeof(arbBitCount));
    is.read((char *) &canFdFlags, sizeof(canFdFlags));
    is.read((char *) &validDataBytes, sizeof(validDataBytes));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) data.data(), data.size());
}

void CanFdMessage::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &dlc, sizeof(dlc));
    os.write((char *) &frameLength, sizeof(frameLength));
    os.write((char *) &arbBitCount, sizeof(arbBitCount));
    os.write((char *) &canFdFlags, sizeof(canFdFlags));
    os.write((char *) &validDataBytes, sizeof(validDataBytes));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) data.data(), data.size());
}

size_t CanFdMessage::calculateObjectSize()
{
    size_t size =
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

    return size;
}

}
}
