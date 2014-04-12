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
    data(),
    alreadyRead(false)
{
}

void CanMessage::read(std::istream & is)
{
    if (alreadyRead)
        return;

    ObjectHeader::read(is);

    const std::streamsize size =
            sizeof(channel) +
            sizeof(flags) +
            sizeof(dlc) +
            sizeof(id) +
            sizeof(data);
    is.read((char *) &channel, size);
    remainingSize -= size;
    alreadyRead = true;
}

}
}
