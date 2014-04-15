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

#include "GpsEvent.h"

#include <cstring>

namespace Vector {
namespace BLF {

GpsEvent::GpsEvent() :
    ObjectHeader(),
    flags(),
    channel(),
    reserved(),
    latitude(),
    longitude(),
    altitude(),
    speed(),
    course()
{
}

char * GpsEvent::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // flags
    size = sizeof(flags);
    memcpy((char *) &flags, buffer, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
    buffer += size;

    // latitude
    size = sizeof(latitude);
    memcpy((char *) &latitude, buffer, size);
    buffer += size;

    // longitude
    size = sizeof(longitude);
    memcpy((char *) &longitude, buffer, size);
    buffer += size;

    // altitude
    size = sizeof(altitude);
    memcpy((char *) &altitude, buffer, size);
    buffer += size;

    // speed
    size = sizeof(speed);
    memcpy((char *) &speed, buffer, size);
    buffer += size;

    // course
    size = sizeof(course);
    memcpy((char *) &course, buffer, size);
    buffer += size;

    return buffer;
}

size_t GpsEvent::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(flags) +
            sizeof(channel) +
            sizeof(reserved) +
            sizeof(latitude) +
            sizeof(longitude) +
            sizeof(altitude) +
            sizeof(speed) +
            sizeof(course);

    return size;
}

}
}
