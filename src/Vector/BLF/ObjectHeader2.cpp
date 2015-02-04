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

#include "ObjectHeader2.h"

#include <cstring>

namespace Vector {
namespace BLF {

ObjectHeader2::ObjectHeader2() :
    ObjectHeaderBase(),
    objectFlags(),
    timeStampStatus(),
    reserved(),
    objectVersion(),
    objectTimeStamp(),
    originalTimeStamp()
{
}

char * ObjectHeader2::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeaderBase::parse(buffer);

    // objectFlags
    size = sizeof(objectFlags);
    memcpy((void *) &objectFlags, buffer, size);
    buffer += size;

    // timeStampStatus
    size = sizeof(timeStampStatus);
    memcpy((void *) &timeStampStatus, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // objectVersion
    size = sizeof(objectVersion);
    memcpy((void *) &objectVersion, buffer, size);
    buffer += size;

    // objectTimeStamp
    size = sizeof(objectTimeStamp);
    memcpy((void *) &objectTimeStamp, buffer, size);
    buffer += size;

    // originalTimeStamp
    size = sizeof(originalTimeStamp);
    memcpy((void *) &originalTimeStamp, buffer, size);
    buffer += size;

    return buffer;
}

size_t ObjectHeader2::calculateObjectSize()
{
    size_t size =
            ObjectHeaderBase::calculateObjectSize() +
            sizeof(objectFlags) +
            sizeof(timeStampStatus) +
            sizeof(reserved) +
            sizeof(objectVersion) +
            sizeof(objectTimeStamp) +
            sizeof(originalTimeStamp);

    return size;
}

}
}
