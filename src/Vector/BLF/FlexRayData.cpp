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
    dummy1(),
    dummy2(),
    dataBytes()
{
}

char * FlexRayData::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // mux
    size = sizeof(mux);
    memcpy((char *) &mux, buffer, size);
    buffer += size;

    // len
    size = sizeof(len);
    memcpy((char *) &len, buffer, size);
    buffer += size;

    // messageId
    size = sizeof(messageId);
    memcpy((char *) &messageId, buffer, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy((char *) &crc, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // dummy1
    size = sizeof(dummy1);
    memcpy((char *) &dummy1, buffer, size);
    buffer += size;

    // dummy2
    size = sizeof(dummy2);
    memcpy((char *) &dummy2, buffer, size);
    buffer += size;

    // dataBytes
    size = sizeof(dataBytes);
    memcpy((char *) &dataBytes, buffer, size);
    buffer += size;

    return buffer;
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
            sizeof(dummy1) +
            sizeof(dummy2) +
            sizeof(dataBytes);

    return size;
}

}
}
