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

#include "CanErrorFrameExt.h"

#include <cstring>

namespace Vector {
namespace BLF {

CanErrorFrameExt::CanErrorFrameExt() :
    ObjectHeader(),
    channel(),
    length(),
    flags(),
    ecc(),
    position(),
    dlc(),
    reserved1(),
    frameLengthInNs(),
    id(),
    flagsExt(),
    reserved2(),
    data()
{
    objectType = ObjectType::CAN_ERROR_EXT;
}

char * CanErrorFrameExt::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // length
    size = sizeof(length);
    memcpy((void *) &length, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
    buffer += size;

    // ecc
    size = sizeof(ecc);
    memcpy((void *) &ecc, buffer, size);
    buffer += size;

    // position
    size = sizeof(position);
    memcpy((void *) &position, buffer, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy((void *) &dlc, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // frameLengthInNs
    size = sizeof(frameLengthInNs);
    memcpy((void *) &frameLengthInNs, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((void *) &id, buffer, size);
    buffer += size;

    // flagsExt
    size = sizeof(flagsExt);
    memcpy((void *) &flagsExt, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // data
    size = data.size();
    memcpy(data.data(), buffer, size);
    buffer += size;

    return buffer;
}

char * CanErrorFrameExt::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // length
    size = sizeof(length);
    memcpy(buffer, (void *) &length, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy(buffer, (void *) &flags, size);
    buffer += size;

    // ecc
    size = sizeof(ecc);
    memcpy(buffer, (void *) &ecc, size);
    buffer += size;

    // position
    size = sizeof(position);
    memcpy(buffer, (void *) &position, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy(buffer, (void *) &dlc, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // frameLengthInNs
    size = sizeof(frameLengthInNs);
    memcpy(buffer, (void *) &frameLengthInNs, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy(buffer, (void *) &id, size);
    buffer += size;

    // flagsExt
    size = sizeof(flagsExt);
    memcpy(buffer, (void *) &flagsExt, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    // data
    size = data.size();
    memcpy(buffer, data.data(), size);
    buffer += size;

    return buffer;
}

size_t CanErrorFrameExt::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(length) +
        sizeof(flags) +
        sizeof(ecc) +
        sizeof(position) +
        sizeof(dlc) +
        sizeof(reserved1) +
        sizeof(frameLengthInNs) +
        sizeof(id) +
        sizeof(flagsExt) +
        sizeof(reserved2) +
        data.size();

    return size;
}

}
}
