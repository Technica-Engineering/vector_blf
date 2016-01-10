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

#include "CanMessage2.h"

namespace Vector {
namespace BLF {

CanMessage2::CanMessage2() :
    ObjectHeader(),
    channel(),
    flags(),
    dlc(),
    id(),
    data(),
    frameLength(),
    bitCount(),
    reserved1(),
    reserved2()
{
    objectType = ObjectType::CAN_MESSAGE2;
}

void CanMessage2::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &dlc, sizeof(dlc));
    is.read((char *) &id, sizeof(id));
    is.read((char *) data.data(), data.size());
    is.read((char *) &frameLength, sizeof(frameLength));
    is.read((char *) &bitCount, sizeof(bitCount));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &reserved2, sizeof(reserved2));
}

void CanMessage2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &dlc, sizeof(dlc));
    os.write((char *) &id, sizeof(id));
    os.write((char *) data.data(), data.size());
    os.write((char *) &frameLength, sizeof(frameLength));
    os.write((char *) &bitCount, sizeof(bitCount));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &reserved2, sizeof(reserved2));
}

size_t CanMessage2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(dlc) +
        sizeof(id) +
        data.size() +
        sizeof(frameLength) +
        sizeof(bitCount) +
        sizeof(reserved1) +
        sizeof(reserved2);

    return size;
}

}
}
