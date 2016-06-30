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

#include "CanErrorFrameExt.h"

namespace Vector {
namespace BLF {

CanErrorFrameExt::CanErrorFrameExt() :
    ObjectHeader(),
    channel(),
    length(),
    flags(),
    ecc(),
    position(),
    dlc(),
    reserved1(),
    frameLengthInNs(),
    id(),
    flagsExt(),
    reserved2(),
    data()
{
    objectType = ObjectType::CAN_ERROR_EXT;
}

void CanErrorFrameExt::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&length), sizeof(length));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&ecc), sizeof(ecc));
    is.read(reinterpret_cast<char *>(&position), sizeof(position));
    is.read(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&frameLengthInNs), sizeof(frameLengthInNs));
    is.read(reinterpret_cast<char *>(&id), sizeof(id));
    is.read(reinterpret_cast<char *>(&flagsExt), sizeof(flagsExt));
    is.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    is.read(reinterpret_cast<char *>(data.data()), data.size());
}

void CanErrorFrameExt::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&length), sizeof(length));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&ecc), sizeof(ecc));
    os.write(reinterpret_cast<char *>(&position), sizeof(position));
    os.write(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&frameLengthInNs), sizeof(frameLengthInNs));
    os.write(reinterpret_cast<char *>(&id), sizeof(id));
    os.write(reinterpret_cast<char *>(&flagsExt), sizeof(flagsExt));
    os.write(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    os.write(reinterpret_cast<char *>(data.data()), data.size());
}

DWORD CanErrorFrameExt::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(length) +
        sizeof(flags) +
        sizeof(ecc) +
        sizeof(position) +
        sizeof(dlc) +
        sizeof(reserved1) +
        sizeof(frameLengthInNs) +
        sizeof(id) +
        sizeof(flagsExt) +
        sizeof(reserved2) +
        data.size();
}

}
}
