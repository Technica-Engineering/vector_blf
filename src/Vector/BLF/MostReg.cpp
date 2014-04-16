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

namespace Vector {
namespace BLF {

MostReg::MostReg() :
    ObjectHeader2(),
    channel(),
    subType(),
    dummy1(),
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
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // subType
    size = sizeof(subType);
    memcpy((char *) &subType, buffer, size);
    buffer += size;

    // dummy1
    size = sizeof(dummy1);
    memcpy((char *) &dummy1, buffer, size);
    buffer += size;

    // handle
    size = sizeof(handle);
    memcpy((char *) &handle, buffer, size);
    buffer += size;

    // offset
    size = sizeof(offset);
    memcpy((char *) &offset, buffer, size);
    buffer += size;

    // chip
    size = sizeof(chip);
    memcpy((char *) &chip, buffer, size);
    buffer += size;

    // regDataLen
    size = sizeof(regDataLen);
    memcpy((char *) &regDataLen, buffer, size);
    buffer += size;

    // regData
    size = sizeof(regData);
    memcpy((char *) &regData, buffer, size);
    buffer += size;

    return buffer;
}

size_t MostReg::calculateObjectSize()
{
    size_t size =
            ObjectHeader2::calculateObjectSize() +
            sizeof(channel) +
            sizeof(subType) +
            sizeof(dummy1) +
            sizeof(handle) +
            sizeof(offset) +
            sizeof(chip) +
            sizeof(regDataLen) +
            sizeof(regData);

    return size;
}

}
}
