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
    objectType = ObjectType::GPS_EVENT;
}

char * GpsEvent::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // latitude
    size = sizeof(latitude);
    memcpy((void *) &latitude, buffer, size);
    buffer += size;

    // longitude
    size = sizeof(longitude);
    memcpy((void *) &longitude, buffer, size);
    buffer += size;

    // altitude
    size = sizeof(altitude);
    memcpy((void *) &altitude, buffer, size);
    buffer += size;

    // speed
    size = sizeof(speed);
    memcpy((void *) &speed, buffer, size);
    buffer += size;

    // course
    size = sizeof(course);
    memcpy((void *) &course, buffer, size);
    buffer += size;

    return buffer;
}

char * GpsEvent::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // flags
    size = sizeof(flags);
    memcpy(buffer, (void *) &flags, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    // latitude
    size = sizeof(latitude);
    memcpy(buffer, (void *) &latitude, size);
    buffer += size;

    // longitude
    size = sizeof(longitude);
    memcpy(buffer, (void *) &longitude, size);
    buffer += size;

    // altitude
    size = sizeof(altitude);
    memcpy(buffer, (void *) &altitude, size);
    buffer += size;

    // speed
    size = sizeof(speed);
    memcpy(buffer, (void *) &speed, size);
    buffer += size;

    // course
    size = sizeof(course);
    memcpy(buffer, (void *) &course, size);
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
