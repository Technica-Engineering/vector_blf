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
    reserved1(),
    error(),
    size(),
    data(),
    reserved2()
{
    /* can be one of:
     *   - objectType = ObjectType::J1708_MESSAGE;
     *   - objectType = ObjectType::J1708_VIRTUAL_MSG;
     */
}

void J1708Message::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &error, sizeof(error));
    is.read((char *) &size, sizeof(size));
    is.read((char *) data.data(), data.size());
    is.read((char *) reserved2.data(), reserved2.size());
}

void J1708Message::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &error, sizeof(error));
    os.write((char *) &size, sizeof(size));
    os.write((char *) data.data(), data.size());
    os.write((char *) reserved2.data(), reserved2.size());
}

size_t J1708Message::calculateObjectSize()
{
    size_t size_ =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reserved1) +
        sizeof(error) +
        sizeof(size) +
        data.size() +
        reserved2.size();

    return size_;
}

}
}
