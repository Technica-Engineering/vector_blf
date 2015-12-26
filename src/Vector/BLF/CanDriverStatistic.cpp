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

#include "CanDriverStatistic.h"

#include <cstring>

namespace Vector {
namespace BLF {

CanDriverStatistic::CanDriverStatistic() :
    ObjectHeader(),
    channel(),
    busLoad(),
    standardDataFrames(),
    extendedDataFrames(),
    standardRemoteFrames(),
    extendedRemoteFrames(),
    errorFrames(),
    overloadFrames(),
    reserved()
{
}

char * CanDriverStatistic::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // busLoad
    size = sizeof(busLoad);
    memcpy((void *) &busLoad, buffer, size);
    buffer += size;

    // standardDataFrames
    size = sizeof(standardDataFrames);
    memcpy((void *) &standardDataFrames, buffer, size);
    buffer += size;

    // extendedDataFrames
    size = sizeof(extendedDataFrames);
    memcpy((void *) &extendedDataFrames, buffer, size);
    buffer += size;

    // standardRemoteFrames
    size = sizeof(standardRemoteFrames);
    memcpy((void *) &standardRemoteFrames, buffer, size);
    buffer += size;

    // extendedRemoteFrames
    size = sizeof(extendedRemoteFrames);
    memcpy((void *) &extendedRemoteFrames, buffer, size);
    buffer += size;

    // errorFrames
    size = sizeof(errorFrames);
    memcpy((void *) &errorFrames, buffer, size);
    buffer += size;

    // overloadFrames
    size = sizeof(overloadFrames);
    memcpy((void *) &overloadFrames, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

char * CanDriverStatistic::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // busLoad
    size = sizeof(busLoad);
    memcpy(buffer, (void *) &busLoad, size);
    buffer += size;

    // standardDataFrames
    size = sizeof(standardDataFrames);
    memcpy(buffer, (void *) &standardDataFrames, size);
    buffer += size;

    // extendedDataFrames
    size = sizeof(extendedDataFrames);
    memcpy(buffer, (void *) &extendedDataFrames, size);
    buffer += size;

    // standardRemoteFrames
    size = sizeof(standardRemoteFrames);
    memcpy(buffer, (void *) &standardRemoteFrames, size);
    buffer += size;

    // extendedRemoteFrames
    size = sizeof(extendedRemoteFrames);
    memcpy(buffer, (void *) &extendedRemoteFrames, size);
    buffer += size;

    // errorFrames
    size = sizeof(errorFrames);
    memcpy(buffer, (void *) &errorFrames, size);
    buffer += size;

    // overloadFrames
    size = sizeof(overloadFrames);
    memcpy(buffer, (void *) &overloadFrames, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    return buffer;
}

size_t CanDriverStatistic::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(busLoad) +
        sizeof(standardDataFrames) +
        sizeof(extendedDataFrames) +
        sizeof(standardRemoteFrames) +
        sizeof(extendedRemoteFrames) +
        sizeof(errorFrames) +
        sizeof(overloadFrames) +
        sizeof(reserved);

    return size;
}

}
}
