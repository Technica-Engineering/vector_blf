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

#include "LinMessageDescriptor.h"

#include <cstring>

namespace Vector {
namespace BLF {

LinMessageDescriptor::LinMessageDescriptor() :
    LinSynchFieldEvent(),
    supplierId(),
    messageId(),
    nad(),
    id(),
    dlc(),
    checksumModel()
{
}

char * LinMessageDescriptor::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = LinSynchFieldEvent::read(buffer);

    // supplierId
    size = sizeof(supplierId);
    memcpy((void *) &supplierId, buffer, size);
    buffer += size;

    // messageId
    size = sizeof(messageId);
    memcpy((void *) &messageId, buffer, size);
    buffer += size;

    // nad
    size = sizeof(nad);
    memcpy((void *) &nad, buffer, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy((void *) &id, buffer, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy((void *) &dlc, buffer, size);
    buffer += size;

    // checksumModel
    size = sizeof(checksumModel);
    memcpy((void *) &checksumModel, buffer, size);
    buffer += size;

    return buffer;
}

char * LinMessageDescriptor::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = LinSynchFieldEvent::write(buffer);

    // supplierId
    size = sizeof(supplierId);
    memcpy(buffer, (void *) &supplierId, size);
    buffer += size;

    // messageId
    size = sizeof(messageId);
    memcpy(buffer, (void *) &messageId, size);
    buffer += size;

    // nad
    size = sizeof(nad);
    memcpy(buffer, (void *) &nad, size);
    buffer += size;

    // id
    size = sizeof(id);
    memcpy(buffer, (void *) &id, size);
    buffer += size;

    // dlc
    size = sizeof(dlc);
    memcpy(buffer, (void *) &dlc, size);
    buffer += size;

    // checksumModel
    size = sizeof(checksumModel);
    memcpy(buffer, (void *) &checksumModel, size);
    buffer += size;

    return buffer;
}

size_t LinMessageDescriptor::calculateObjectSize()
{
    size_t size =
        LinSynchFieldEvent::calculateObjectSize() +
        sizeof(supplierId) +
        sizeof(messageId) +
        sizeof(nad) +
        sizeof(id) +
        sizeof(dlc) +
        sizeof(checksumModel);

    return size;
}

}
}
