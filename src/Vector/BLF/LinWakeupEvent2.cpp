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

#include "LinWakeupEvent2.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinWakeupEvent2::LinWakeupEvent2() :
    ObjectHeader(),
    LinBusEvent(),
    lengthInfo(),
    signal(),
    external(),
    reserved()
{
}

char * LinWakeupEvent2::read(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::read(buffer);
    buffer = LinBusEvent::read(buffer);

    // lengthInfo
    size = sizeof(lengthInfo);
    memcpy((void *) &lengthInfo, buffer, size);
    buffer += size;

    // signal
    size = sizeof(signal);
    memcpy((void *) &signal, buffer, size);
    buffer += size;

    // external
    size = sizeof(external);
    memcpy((void *) &external, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

size_t LinWakeupEvent2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(lengthInfo) +
        sizeof(signal) +
        sizeof(external) +
        sizeof(reserved);

    return size;
}

}
}
