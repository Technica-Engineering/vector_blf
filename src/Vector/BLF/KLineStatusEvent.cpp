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

#include "KLineStatusEvent.h"

#include <cstring>

namespace Vector {
namespace BLF {

KLineStatusEvent::KLineStatusEvent() :
    ObjectHeader(),
    type(),
    dataLen(),
    port(),
    reserved(),
    data()
{
    objectType = ObjectType::KLINE_STATUSEVENT;
}

char * KLineStatusEvent::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // type
    size = sizeof(type);
    memcpy((void *) &type, buffer, size);
    buffer += size;

    // dataLen
    size = sizeof(dataLen);
    memcpy((void *) &dataLen, buffer, size);
    buffer += size;

    // port
    size = sizeof(port);
    memcpy((void *) &port, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // data
    size = dataLen;
    memcpy(data.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * KLineStatusEvent::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // type
    size = sizeof(type);
    memcpy(buffer, (void *) &type, size);
    buffer += size;

    // dataLen
    size = sizeof(dataLen);
    memcpy(buffer, (void *) &dataLen, size);
    buffer += size;

    // port
    size = sizeof(port);
    memcpy(buffer, (void *) &port, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    // data
    size = dataLen;
    memcpy(buffer, data.data(), size);
    buffer += size;

    return buffer;
}

size_t KLineStatusEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(type) +
        sizeof(dataLen) +
        sizeof(port) +
        sizeof(reserved) +
        dataLen;

    return size;
}

}
}
