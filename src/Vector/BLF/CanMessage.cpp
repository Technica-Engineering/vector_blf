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

#include "CanMessage.h"

namespace Vector {
namespace BLF {

CanMessage::CanMessage() :
    ObjectHeader(),
    channel(),
    flags(),
    dlc(),
    id(),
    data()
{
    objectType = ObjectType::CAN_MESSAGE;
}

void CanMessage::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &dlc, sizeof(dlc));
    is.read((char *) &id, sizeof(id));
    is.read((char *) data.data(), data.size());
}

void CanMessage::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &dlc, sizeof(dlc));
    os.write((char *) &id, sizeof(id));
    os.write((char *) data.data(), data.size());
}

size_t CanMessage::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(dlc) +
        sizeof(id) +
        data.size();

    return size;
}

}
}
