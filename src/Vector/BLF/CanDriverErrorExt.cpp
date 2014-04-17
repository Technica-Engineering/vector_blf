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
    reserved()
{
}

char * CanDriverErrorExt::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // txErrors
    size = sizeof(txErrors);
    memcpy((char *) &txErrors, buffer, size);
    buffer += size;

    // rxErrors
    size = sizeof(rxErrors);
    memcpy((char *) &rxErrors, buffer, size);
    buffer += size;

    // errorCode
    size = sizeof(errorCode);
    memcpy((char *) &errorCode, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((char *) &flags, buffer, size);
    buffer += size;

    // state
    size = sizeof(state);
    memcpy((char *) &state, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
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
            sizeof(reserved);

    return size;
}

}
}
