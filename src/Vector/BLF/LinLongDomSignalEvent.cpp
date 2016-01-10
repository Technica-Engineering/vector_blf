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

#include "LinLongDomSignalEvent.h"

namespace Vector {
namespace BLF {

LinLongDomSignalEvent::LinLongDomSignalEvent() :
    ObjectHeader(),
    LinBusEvent(),
    type(),
    reserved()
{
    objectType = ObjectType::LIN_LONG_DOM_SIG;
}

void LinLongDomSignalEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinBusEvent::read(is);
    is.read((char *) &type, sizeof(type));
    is.read((char *) reserved.data(), reserved.size());
}

void LinLongDomSignalEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinBusEvent::write(os);
    os.write((char *) &type, sizeof(type));
    os.write((char *) reserved.data(), reserved.size());
}

size_t LinLongDomSignalEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(type) +
        reserved.size();

    return size;
}

}
}
