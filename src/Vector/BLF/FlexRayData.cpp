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
    reserved1(),
    reserved2(),
    dataBytes()
{
    objectType = ObjectType::FLEXRAY_DATA;
}

char * FlexRayData::read(char * buffer)
{
    size_t size;

    // preceding data
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

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // dataBytes
    size = dataBytes.size();
    memcpy(dataBytes.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * FlexRayData::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // mux
    size = sizeof(mux);
    memcpy(buffer, (void *) &mux, size);
    buffer += size;

    // len
    size = sizeof(len);
    memcpy(buffer, (void *) &len, size);
    buffer += size;

    // messageId
    size = sizeof(messageId);
    memcpy(buffer, (void *) &messageId, size);
    buffer += size;

    // crc
    size = sizeof(crc);
    memcpy(buffer, (void *) &crc, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy(buffer, (void *) &dir, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    // dataBytes
    size = dataBytes.size();
    memcpy(buffer, dataBytes.data(), size);
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
        sizeof(reserved1) +
        sizeof(reserved2) +
        dataBytes.size();

    return size;
}

}
}
