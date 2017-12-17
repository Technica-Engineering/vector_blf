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

#include <Vector/BLF/J1708Message.h>

#include <iostream>

namespace Vector {
namespace BLF {

J1708Message::J1708Message() :
    ObjectHeader(),
    channel(),
    dir(),
    reservedJ1708Message1(),
    error(),
    size(),
    data(),
    reservedJ1708Message2()
{
    objectType = ObjectType::J1708_MESSAGE; // or J1708_VIRTUAL_MSG
}

void J1708Message::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&reservedJ1708Message1), sizeof(reservedJ1708Message1));
    is.read(reinterpret_cast<char *>(&error), sizeof(error));
    is.read(reinterpret_cast<char *>(&size), sizeof(size));
    is.read(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    is.read(reinterpret_cast<char *>(&reservedJ1708Message2), sizeof(reservedJ1708Message2));
}

void J1708Message::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&reservedJ1708Message1), sizeof(reservedJ1708Message1));
    os.write(reinterpret_cast<char *>(&error), sizeof(error));
    os.write(reinterpret_cast<char *>(&size), sizeof(size));
    os.write(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    os.write(reinterpret_cast<char *>(&reservedJ1708Message2), sizeof(reservedJ1708Message2));
}

DWORD J1708Message::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedJ1708Message1) +
        sizeof(error) +
        sizeof(size) +
        static_cast<DWORD>(data.size()) +
        sizeof(reservedJ1708Message2);
}

}
}
