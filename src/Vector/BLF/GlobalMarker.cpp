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

#include "GlobalMarker.h"

namespace Vector {
namespace BLF {

GlobalMarker::GlobalMarker() :
    ObjectHeader(),
    commentedEventType(),
    foregroundColor(),
    backgroundColor(),
    isRelocatable(),
    groupNameLength(),
    markerNameLength(),
    descriptionLength(),
    groupName(nullptr),
    markerName(nullptr),
    description(nullptr)
{
}

GlobalMarker::~GlobalMarker()
{
    delete[] groupName;
    groupName = nullptr;

    delete[] markerName;
    markerName = nullptr;

    delete[] description;
    description = nullptr;
}

char * GlobalMarker::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

#if 0
    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;
#else
    // @todo
#endif

    return buffer;
}

size_t GlobalMarker::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(commentedEventType) +
            sizeof(foregroundColor) +
            sizeof(backgroundColor) +
            sizeof(isRelocatable) +
            sizeof(groupNameLength) +
            sizeof(markerNameLength) +
            sizeof(descriptionLength) +
            groupNameLength +
            markerNameLength +
            descriptionLength;

    return size;
}

}
}
