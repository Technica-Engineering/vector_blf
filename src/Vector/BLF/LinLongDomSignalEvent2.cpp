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

#include "LinLongDomSignalEvent2.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinLongDomSignalEvent2::LinLongDomSignalEvent2() :
    ObjectHeader(),
    LinBusEvent(),
    type(),
    reserved(),
    length()
{
}

char * LinLongDomSignalEvent2::read(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::read(buffer);
    buffer = LinBusEvent::read(buffer);

    // type
    size = sizeof(type);
    memcpy((void *) &type, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // length
    size = sizeof(length);
    memcpy((void *) &length, buffer, size);
    buffer += size;

    return buffer;
}

char * LinLongDomSignalEvent2::write(char * buffer)
{
    // @todo
}

size_t LinLongDomSignalEvent2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(type) +
        sizeof(reserved) +
        sizeof(length);

    return size;
}

}
}
