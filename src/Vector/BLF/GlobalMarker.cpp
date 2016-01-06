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

#include <cstring>

namespace Vector {
namespace BLF {

GlobalMarker::GlobalMarker() :
    ObjectHeader(),
    commentedEventType(),
    foregroundColor(),
    backgroundColor(),
    reserved1(),
    isRelocatable(),
    groupNameLength(),
    markerNameLength(),
    descriptionLength(),
    reserved2(),
    groupName(),
    markerName(),
    description()
{
    objectType = ObjectType::GLOBAL_MARKER;
}

GlobalMarker::~GlobalMarker()
{
}

char * GlobalMarker::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // commentedEventType
    size = sizeof(commentedEventType);
    memcpy((void *) &commentedEventType, buffer, size);
    buffer += size;

    // foregroundColor
    size = sizeof(foregroundColor);
    memcpy((void *) &foregroundColor, buffer, size);
    buffer += size;

    // backgroundColor
    size = sizeof(backgroundColor);
    memcpy((void *) &backgroundColor, buffer, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy((void *) &reserved1, buffer, size);
    buffer += size;

    // isRelocatable
    size = sizeof(isRelocatable);
    memcpy((void *) &isRelocatable, buffer, size);
    buffer += size;

    // groupNameLength
    size = sizeof(groupNameLength);
    memcpy((void *) &groupNameLength, buffer, size);
    buffer += size;

    // markerNameLength
    size = sizeof(markerNameLength);
    memcpy((void *) &markerNameLength, buffer, size);
    buffer += size;

    // descriptionLength
    size = sizeof(descriptionLength);
    memcpy((void *) &descriptionLength, buffer, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy((void *) &reserved2, buffer, size);
    buffer += size;

    // groupName
    size = groupNameLength;
    groupName.assign(buffer, size);
    buffer += size;

    // markerName
    size = markerNameLength;
    markerName.assign(buffer, size);
    buffer += size;

    // description
    size = descriptionLength;
    description.assign(buffer, size);
    buffer += size;

    return buffer;
}

char * GlobalMarker::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // commentedEventType
    size = sizeof(commentedEventType);
    memcpy(buffer, (void *) &commentedEventType, size);
    buffer += size;

    // foregroundColor
    size = sizeof(foregroundColor);
    memcpy(buffer, (void *) &foregroundColor, size);
    buffer += size;

    // backgroundColor
    size = sizeof(backgroundColor);
    memcpy(buffer, (void *) &backgroundColor, size);
    buffer += size;

    // reserved1
    size = sizeof(reserved1);
    memcpy(buffer, (void *) &reserved1, size);
    buffer += size;

    // isRelocatable
    size = sizeof(isRelocatable);
    memcpy(buffer, (void *) &isRelocatable, size);
    buffer += size;

    // groupNameLength
    size = sizeof(groupNameLength);
    memcpy(buffer, (void *) &groupNameLength, size);
    buffer += size;

    // markerNameLength
    size = sizeof(markerNameLength);
    memcpy(buffer, (void *) &markerNameLength, size);
    buffer += size;

    // descriptionLength
    size = sizeof(descriptionLength);
    memcpy(buffer, (void *) &descriptionLength, size);
    buffer += size;

    // reserved2
    size = sizeof(reserved2);
    memcpy(buffer, (void *) &reserved2, size);
    buffer += size;

    // groupName
    size = groupNameLength;
    memcpy(buffer, groupName.data(), size);
    buffer += size;

    // markerName
    size = markerNameLength;
    memcpy(buffer, markerName.data(), size);
    buffer += size;

    // description
    size = descriptionLength;
    memcpy(buffer, description.data(), size);
    buffer += size;

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
        sizeof(reserved1) +
        sizeof(groupNameLength) +
        sizeof(markerNameLength) +
        sizeof(descriptionLength) +
        sizeof(reserved2) +
        groupNameLength +
        markerNameLength +
        descriptionLength;

    return size;
}

}
}
