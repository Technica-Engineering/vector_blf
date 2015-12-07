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

#include "MostReg.h"

#include <cstring>

namespace Vector {
namespace BLF {

MostReg::MostReg() :
    ObjectHeader2(),
    channel(),
    subType(),
    reserved(),
    handle(),
    offset(),
    chip(),
    regDataLen(),
    regData()
{
}

char * MostReg::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader2::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // subType
    size = sizeof(subType);
    memcpy((void *) &subType, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // handle
    size = sizeof(handle);
    memcpy((void *) &handle, buffer, size);
    buffer += size;

    // offset
    size = sizeof(offset);
    memcpy((void *) &offset, buffer, size);
    buffer += size;

    // chip
    size = sizeof(chip);
    memcpy((void *) &chip, buffer, size);
    buffer += size;

    // regDataLen
    size = sizeof(regDataLen);
    memcpy((void *) &regDataLen, buffer, size);
    buffer += size;

    // regData
    size = sizeof(regData);
    memcpy((void *) &regData, buffer, size);
    buffer += size;

    return buffer;
}

size_t MostReg::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(subType) +
        sizeof(reserved) +
        sizeof(handle) +
        sizeof(offset) +
        sizeof(chip) +
        sizeof(regDataLen) +
        sizeof(regData);

    return size;
}

}
}
