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

#include "LinBaudrateEvent.h"

namespace Vector {
namespace BLF {

LinBaudrateEvent::LinBaudrateEvent() :
    ObjectHeader(),
    channel(),
    reserved(),
    baudrate()
{
    objectType = ObjectType::LIN_BAUDRATE;
}

void LinBaudrateEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &reserved, sizeof(reserved));
    is.read((char *) &baudrate, sizeof(baudrate));
}

void LinBaudrateEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &reserved, sizeof(reserved));
    os.write((char *) &baudrate, sizeof(baudrate));
}

size_t LinBaudrateEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reserved) +
        sizeof(baudrate);

    return size;
}

}
}
