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

#include "CanDriverErrorExt.h"

#include <cstring>

namespace Vector {
namespace BLF {

CanDriverErrorExt::CanDriverErrorExt() :
    ObjectHeader(),
    channel(),
    txErrors(),
    rxErrors(),
    errorCode(),
    flags(),
    state(),
    reserved1(),
    reserved2(),
    reserved3()
{
    objectType = ObjectType::CAN_DRIVER_ERROR_EXT;
}

char * CanDriverErrorExt::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // txErrors
    size = sizeof(txErrors);
    memcpy((void *) &txErrors, buffer, size);
    buffer += size;

    // rxErrors
    size = sizeof(rxErrors);
    memcpy((void *) &rxErrors, buffer, size);
    buffer += size;

    // errorCode
    size = sizeof(errorCode);
    memcpy((void *) &errorCode, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
    buffer += size;

    // state
    size = sizeof(state);
    memcpy((void *) &state, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // reserved3
    size = reserved3.size();
    memcpy(reserved3.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * CanDriverErrorExt::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // txErrors
    size = sizeof(txErrors);
    memcpy(buffer, (void *) &txErrors, size);
    buffer += size;

    // rxErrors
    size = sizeof(rxErrors);
    memcpy(buffer, (void *) &rxErrors, size);
    buffer += size;

    // errorCode
    size = sizeof(errorCode);
    memcpy(buffer, (void *) &errorCode, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy(buffer, (void *) &flags, size);
    buffer += size;

    // state
    size = sizeof(state);
    memcpy(buffer, (void *) &state, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    // reserved3
    size = reserved3.size();
    memcpy(buffer, reserved3.data(), size);
    buffer += size;

    return buffer;
}

size_t CanDriverErrorExt::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(txErrors) +
        sizeof(rxErrors) +
        sizeof(errorCode) +
        sizeof(flags) +
        sizeof(state) +
        sizeof(reserved1) +
        sizeof(reserved2) +
        reserved3.size();

    return size;
}

}
}
