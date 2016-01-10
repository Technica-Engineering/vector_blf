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

#include "KLineStatusEvent.h"

namespace Vector {
namespace BLF {

KLineStatusEvent::KLineStatusEvent() :
    ObjectHeader(),
    type(),
    dataLen(),
    port(),
    reserved(),
    data()
{
    objectType = ObjectType::KLINE_STATUSEVENT;
}

void KLineStatusEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &type, sizeof(type));
    is.read((char *) &dataLen, sizeof(dataLen));
    is.read((char *) &port, sizeof(port));
    is.read((char *) &reserved, sizeof(reserved));
    is.read((char *) data.data(), data.size());
}

void KLineStatusEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &type, sizeof(type));
    os.write((char *) &dataLen, sizeof(dataLen));
    os.write((char *) &port, sizeof(port));
    os.write((char *) &reserved, sizeof(reserved));
    os.write((char *) data.data(), data.size());
}

size_t KLineStatusEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(type) +
        sizeof(dataLen) +
        sizeof(port) +
        sizeof(reserved) +
        dataLen;

    return size;
}

}
}
