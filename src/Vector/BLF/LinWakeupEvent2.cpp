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

#include "LinWakeupEvent2.h"

namespace Vector {
namespace BLF {

LinWakeupEvent2::LinWakeupEvent2() :
    ObjectHeader(),
    LinBusEvent(),
    lengthInfo(),
    signal(),
    external(),
    reserved()
{
    objectType = ObjectType::LIN_WAKEUP2;
}

void LinWakeupEvent2::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinBusEvent::read(is);
    is.read((char *) &lengthInfo, sizeof(lengthInfo));
    is.read((char *) &signal, sizeof(signal));
    is.read((char *) &external, sizeof(external));
    is.read((char *) reserved.data(), reserved.size());
}

void LinWakeupEvent2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinBusEvent::write(os);
    os.write((char *) &lengthInfo, sizeof(lengthInfo));
    os.write((char *) &signal, sizeof(signal));
    os.write((char *) &external, sizeof(external));
    os.write((char *) reserved.data(), reserved.size());
}

size_t LinWakeupEvent2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(lengthInfo) +
        sizeof(signal) +
        sizeof(external) +
        reserved.size();

    return size;
}

}
}
