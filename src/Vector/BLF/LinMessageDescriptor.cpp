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

void LinMessageDescriptor::read(AbstractFile & is)
{
    LinSynchFieldEvent::read(is);
    is.read((char *) &supplierId, sizeof(supplierId));
    is.read((char *) &messageId, sizeof(messageId));
    is.read((char *) &nad, sizeof(nad));
    is.read((char *) &id, sizeof(id));
    is.read((char *) &dlc, sizeof(dlc));
    is.read((char *) &checksumModel, sizeof(checksumModel));
}

void LinMessageDescriptor::write(AbstractFile & os)
{
    LinSynchFieldEvent::write(os);
    os.write((char *) &supplierId, sizeof(supplierId));
    os.write((char *) &messageId, sizeof(messageId));
    os.write((char *) &nad, sizeof(nad));
    os.write((char *) &id, sizeof(id));
    os.write((char *) &dlc, sizeof(dlc));
    os.write((char *) &checksumModel, sizeof(checksumModel));
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
