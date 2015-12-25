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

#include "MostGenReg.h"

#include <cstring>

namespace Vector {
namespace BLF {

MostGenReg::MostGenReg() :
    ObjectHeader2(),
    channel(),
    subType(),
    reserved1(),
    handle(),
    regId(),
    reserved2(),
    regValue()
{
}

char * MostGenReg::read(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader2::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // subType
    size = sizeof(subType);
    memcpy((void *) &subType, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // handle
    size = sizeof(handle);
    memcpy((void *) &handle, buffer, size);
    buffer += size;

    // regId
    size = sizeof(regId);
    memcpy((void *) &regId, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // regValue
    size = sizeof(regValue);
    memcpy((void *) &regValue, buffer, size);
    buffer += size;

    return buffer;
}

char * MostGenReg::write(char * buffer)
{
    // @todo
}

size_t MostGenReg::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(subType) +
        sizeof(reserved1) +
        sizeof(handle) +
        sizeof(regId) +
        sizeof(reserved2) +
        sizeof(regValue);

    return size;
}

}
}
