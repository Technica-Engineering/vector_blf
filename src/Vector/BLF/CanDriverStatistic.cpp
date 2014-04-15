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

char * CanDriverStatistic::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // busLoad
    size = sizeof(busLoad);
    memcpy((char *) &busLoad, buffer, size);
    buffer += size;

    // standardDataFrames
    size = sizeof(standardDataFrames);
    memcpy((char *) &standardDataFrames, buffer, size);
    buffer += size;

    // extendedDataFrames
    size = sizeof(extendedDataFrames);
    memcpy((char *) &extendedDataFrames, buffer, size);
    buffer += size;

    // standardRemoteFrames
    size = sizeof(standardRemoteFrames);
    memcpy((char *) &standardRemoteFrames, buffer, size);
    buffer += size;

    // extendedRemoteFrames
    size = sizeof(extendedRemoteFrames);
    memcpy((char *) &extendedRemoteFrames, buffer, size);
    buffer += size;

    // errorFrames
    size = sizeof(errorFrames);
    memcpy((char *) &errorFrames, buffer, size);
    buffer += size;

    // overloadFrames
    size = sizeof(overloadFrames);
    memcpy((char *) &overloadFrames, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
    buffer += size;

    return buffer;
}

}
}
