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

#include "MostEcl.h"

#include <cstring>

namespace Vector {
namespace BLF {

MostEcl::MostEcl() :
    ObjectHeader2(),
    channel(),
    mode(),
    eclState(),
    reserved()
{
}

char * MostEcl::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // mode
    size = sizeof(mode);
    memcpy((void *) &mode, buffer, size);
    buffer += size;

    // eclState
    size = sizeof(eclState);
    memcpy((void *) &eclState, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

char * MostEcl::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // mode
    size = sizeof(mode);
    memcpy(buffer, (void *) &mode, size);
    buffer += size;

    // eclState
    size = sizeof(eclState);
    memcpy(buffer, (void *) &eclState, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    return buffer;
}

size_t MostEcl::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(mode) +
        sizeof(eclState) +
        sizeof(reserved);

    return size;
}

}
}
