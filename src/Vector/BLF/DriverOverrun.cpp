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

#include "DriverOverrun.h"

namespace Vector {
namespace BLF {

DriverOverrun::DriverOverrun() :
    ObjectHeader(),
    busType(),
    channel(),
    reserved()
{
    objectType = ObjectType::OVERRUN_ERROR;
}

void DriverOverrun::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &busType, sizeof(busType));
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &reserved, sizeof(reserved));
}

void DriverOverrun::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &busType, sizeof(busType));
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &reserved, sizeof(reserved));
}

size_t DriverOverrun::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(busType) +
        sizeof(channel) +
        sizeof(reserved);

    return size;
}

}
}
