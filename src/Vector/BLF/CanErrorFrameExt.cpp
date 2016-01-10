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
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &length, sizeof(length));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &ecc, sizeof(ecc));
    is.read((char *) &position, sizeof(position));
    is.read((char *) &dlc, sizeof(dlc));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &frameLengthInNs, sizeof(frameLengthInNs));
    is.read((char *) &id, sizeof(id));
    is.read((char *) &flagsExt, sizeof(flagsExt));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) data.data(), data.size());
}

void CanErrorFrameExt::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &length, sizeof(length));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &ecc, sizeof(ecc));
    os.write((char *) &position, sizeof(position));
    os.write((char *) &dlc, sizeof(dlc));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &frameLengthInNs, sizeof(frameLengthInNs));
    os.write((char *) &id, sizeof(id));
    os.write((char *) &flagsExt, sizeof(flagsExt));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) data.data(), data.size());
}

size_t CanErrorFrameExt::calculateObjectSize()
{
    size_t size =
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

    return size;
}

}
}
