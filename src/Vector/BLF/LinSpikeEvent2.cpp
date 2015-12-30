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

#include "LinSpikeEvent2.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinSpikeEvent2::LinSpikeEvent2() :
    ObjectHeader(),
    LinBusEvent(),
    width(),
    internal(),
    reserved()
{
    objectType = ObjectType::LIN_SPIKE_EVENT2;
}

char * LinSpikeEvent2::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);
    buffer = LinBusEvent::read(buffer);

    // width
    size = sizeof(width);
    memcpy((void *) &width, buffer, size);
    buffer += size;

    // internal
    size = sizeof(internal);
    memcpy((void *) &internal, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

char * LinSpikeEvent2::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);
    buffer = LinBusEvent::write(buffer);

    // width
    size = sizeof(width);
    memcpy(buffer, (void *) &width, size);
    buffer += size;

    // internal
    size = sizeof(internal);
    memcpy(buffer, (void *) &internal, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    return buffer;
}

size_t LinSpikeEvent2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(width) +
        sizeof(internal) +
        sizeof(reserved);

    return size;
}

}
}
