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

#include <cstring>

#include "GlobalMarker.h"

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

void GlobalMarker::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&commentedEventType), sizeof(commentedEventType));
    is.read(reinterpret_cast<char *>(&foregroundColor), sizeof(foregroundColor));
    is.read(reinterpret_cast<char *>(&backgroundColor), sizeof(backgroundColor));
    is.read(reinterpret_cast<char *>(reserved1.data()), reserved1.size());
    is.read(reinterpret_cast<char *>(&isRelocatable), sizeof(isRelocatable));
    is.read(reinterpret_cast<char *>(&groupNameLength), sizeof(groupNameLength));
    is.read(reinterpret_cast<char *>(&markerNameLength), sizeof(markerNameLength));
    is.read(reinterpret_cast<char *>(&descriptionLength), sizeof(descriptionLength));
    is.read(reinterpret_cast<char *>(reserved2.data()), reserved2.size());
    groupName.resize(groupNameLength);
    is.read(const_cast<char *>(groupName.data()), groupNameLength);
    markerName.resize(markerNameLength);
    is.read(const_cast<char *>(markerName.data()), markerNameLength);
    description.resize(descriptionLength);
    is.read(const_cast<char *>(description.data()), descriptionLength);

    /* post processing */
    groupName.resize(strnlen(groupName.c_str(), groupNameLength)); // Vector bug: the actual string can be shorter than size!
    markerName.resize(strnlen(markerName.c_str(), markerNameLength)); // Vector bug: the actual string can be shorter than size!
    description.resize(strnlen(description.c_str(), descriptionLength)); // Vector bug: the actual string can be shorter than size!
    objectSize = calculateObjectSize();
}

void GlobalMarker::write(AbstractFile & os)
{
    /* pre processing */
    groupNameLength = groupName.size();
    markerNameLength = markerName.size();
    descriptionLength = description.size();

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&commentedEventType), sizeof(commentedEventType));
    os.write(reinterpret_cast<char *>(&foregroundColor), sizeof(foregroundColor));
    os.write(reinterpret_cast<char *>(&backgroundColor), sizeof(backgroundColor));
    os.write(reinterpret_cast<char *>(reserved1.data()), reserved1.size());
    os.write(reinterpret_cast<char *>(&isRelocatable), sizeof(isRelocatable));
    os.write(reinterpret_cast<char *>(&groupNameLength), sizeof(groupNameLength));
    os.write(reinterpret_cast<char *>(&markerNameLength), sizeof(markerNameLength));
    os.write(reinterpret_cast<char *>(&descriptionLength), sizeof(descriptionLength));
    os.write(reinterpret_cast<char *>(reserved2.data()), reserved2.size());
    os.write(const_cast<char *>(groupName.data()), groupNameLength);
    os.write(const_cast<char *>(markerName.data()), markerNameLength);
    os.write(const_cast<char *>(description.data()), descriptionLength);
}

size_t GlobalMarker::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(commentedEventType) +
        sizeof(foregroundColor) +
        sizeof(backgroundColor) +
        sizeof(isRelocatable) +
        reserved1.size() +
        sizeof(groupNameLength) +
        sizeof(markerNameLength) +
        sizeof(descriptionLength) +
        reserved2.size() +
        groupNameLength +
        markerNameLength +
        descriptionLength;

    return size;
}

}
}
