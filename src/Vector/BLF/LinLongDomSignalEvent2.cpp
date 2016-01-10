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

#include "LinLongDomSignalEvent2.h"

namespace Vector {
namespace BLF {

LinLongDomSignalEvent2::LinLongDomSignalEvent2() :
    ObjectHeader(),
    LinBusEvent(),
    type(),
    reserved(),
    length()
{
    objectType = ObjectType::LIN_LONG_DOM_SIG2;
}

void LinLongDomSignalEvent2::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinBusEvent::read(is);
    is.read((char *) &type, sizeof(type));
    is.read((char *) reserved.data(), reserved.size());
    is.read((char *) &length, sizeof(length));
}

void LinLongDomSignalEvent2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinBusEvent::write(os);
    os.write((char *) &type, sizeof(type));
    os.write((char *) reserved.data(), reserved.size());
    os.write((char *) &length, sizeof(length));
}

size_t LinLongDomSignalEvent2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(type) +
        reserved.size() +
        sizeof(length);

    return size;
}

}
}
