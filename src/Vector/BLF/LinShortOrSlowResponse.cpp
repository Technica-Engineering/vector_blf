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

#include "LinShortOrSlowResponse.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinShortOrSlowResponse::LinShortOrSlowResponse() :
    ObjectHeader(),
    LinDatabyteTimestampEvent(),
    numberOfRespBtes(),
    respBytes(),
    slowResponse(),
    interruptedByBreak(),
    reserved()
{
}

char * LinShortOrSlowResponse::read(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::read(buffer);
    buffer = LinDatabyteTimestampEvent::read(buffer);

    // numberOfRespBtes
    size = sizeof(numberOfRespBtes);
    memcpy((void *) &numberOfRespBtes, buffer, size);
    buffer += size;

    // respBytes
    size = sizeof(respBytes);
    memcpy((void *) &respBytes, buffer, size);
    buffer += size;

    // slowResponse
    size = sizeof(slowResponse);
    memcpy((void *) &slowResponse, buffer, size);
    buffer += size;

    // interruptedByBreak
    size = sizeof(interruptedByBreak);
    memcpy((void *) &interruptedByBreak, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

char * LinShortOrSlowResponse::write(char * buffer)
{
    // @todo
}

size_t LinShortOrSlowResponse::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        sizeof(numberOfRespBtes) +
        sizeof(respBytes) +
        sizeof(slowResponse) +
        sizeof(interruptedByBreak) +
        sizeof(reserved);

    return size;
}

}
}
