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

#include "LinUnexpectedWakeup.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinUnexpectedWakeup::LinUnexpectedWakeup() :
    ObjectHeader(),
    LinBusEvent(),
    width(),
    signal(),
    reserved()
{
}

char * LinUnexpectedWakeup::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);
    buffer = LinBusEvent::parse(buffer);

    // width
    size = sizeof(width);
    memcpy((void *) &width, buffer, size);
    buffer += size;

    // signal
    size = sizeof(signal);
    memcpy((void *) &signal, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

size_t LinUnexpectedWakeup::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            LinBusEvent::calculateObjectSize() +
            sizeof(width) +
            sizeof(signal) +
            sizeof(reserved);

    return size;
}

}
}
