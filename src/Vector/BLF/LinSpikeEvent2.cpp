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
}

char * LinSpikeEvent2::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);
    buffer = LinBusEvent::parse(buffer);

    // width
    size = sizeof(width);
    memcpy((char *) &width, buffer, size);
    buffer += size;

    // internal
    size = sizeof(internal);
    memcpy((char *) &internal, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
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
