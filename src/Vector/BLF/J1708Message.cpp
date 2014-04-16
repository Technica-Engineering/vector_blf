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

#include "J1708Message.h"

namespace Vector {
namespace BLF {

J1708Message::J1708Message() :
    ObjectHeader(),
    channel(),
    dir(),
    error(),
    size(),
    data()
{
}

char * J1708Message::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // error
    size = sizeof(error);
    memcpy((char *) &error, buffer, size);
    buffer += size;

    // size
    size = sizeof(size);
    memcpy((char *) &size, buffer, size);
    buffer += size;

    // data
    size = sizeof(data);
    memcpy((char *) &data, buffer, size);
    buffer += size;

    return buffer;
}

size_t J1708Message::calculateObjectSize()
{
    size_t size_ =
            ObjectHeader::calculateObjectSize() +
            sizeof(channel) +
            sizeof(dir) +
            sizeof(error) +
            sizeof(size) +
            sizeof(data);

    return size_;
}

}
}
