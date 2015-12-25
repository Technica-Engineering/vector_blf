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

#include "FlexRayData.h"

#include <cstring>

namespace Vector {
namespace BLF {

FlexRayData::FlexRayData() :
    ObjectHeader(),
    channel(),
    mux(),
    len(),
    messageId(),
    crc(),
    dir(),
    reserved(),
    dataBytes()
{
}

char * FlexRayData::read(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // mux
    size = sizeof(mux);
    memcpy((void *) &mux, buffer, size);
    buffer += size;

    // len
    size = sizeof(len);
    memcpy((void *) &len, buffer, size);
    buffer += size;

    // messageId
    size = sizeof(messageId);
    memcpy((void *) &messageId, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((void *) &crc, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((void *) &dir, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // dataBytes
    size = sizeof(dataBytes);
    memcpy((void *) &dataBytes, buffer, size);
    buffer += size;

    return buffer;
}

char * FlexRayData::write(char * buffer)
{
    // @todo
}

size_t FlexRayData::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(mux) +
        sizeof(len) +
        sizeof(messageId) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(reserved) +
        sizeof(dataBytes);

    return size;
}

}
}
