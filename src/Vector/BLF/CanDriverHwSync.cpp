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

#include "CanDriverHwSync.h"

namespace Vector {
namespace BLF {

CanDriverHwSync::CanDriverHwSync() :
    ObjectHeader(),
    channel(),
    flags(),
    reserved()
{
    objectType = ObjectType::CAN_DRIVER_SYNC;
}

void CanDriverHwSync::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &reserved, sizeof(reserved));
}

void CanDriverHwSync::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &reserved, sizeof(reserved));
}

size_t CanDriverHwSync::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(reserved);

    return size;
}

}
}
