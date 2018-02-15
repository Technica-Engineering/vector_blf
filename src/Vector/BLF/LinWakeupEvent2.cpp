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

#include <Vector/BLF/LinWakeupEvent2.h>

namespace Vector {
namespace BLF {

LinWakeupEvent2::LinWakeupEvent2() :
    ObjectHeader(),
    LinBusEvent(),
    lengthInfo(),
    signal(),
    external(),
    reservedLinWakeupEvent1(),
    reservedLinWakeupEvent2()
{
    objectType = ObjectType::LIN_WAKEUP2;
}

void LinWakeupEvent2::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinBusEvent::read(is);
    is.read(reinterpret_cast<char *>(&lengthInfo), sizeof(lengthInfo));
    is.read(reinterpret_cast<char *>(&signal), sizeof(signal));
    is.read(reinterpret_cast<char *>(&external), sizeof(external));
    is.read(reinterpret_cast<char *>(&reservedLinWakeupEvent1), sizeof(reservedLinWakeupEvent1));
    is.read(reinterpret_cast<char *>(&reservedLinWakeupEvent2), sizeof(reservedLinWakeupEvent2));
    // @note might be extended in future versions
}

void LinWakeupEvent2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinBusEvent::write(os);
    os.write(reinterpret_cast<char *>(&lengthInfo), sizeof(lengthInfo));
    os.write(reinterpret_cast<char *>(&signal), sizeof(signal));
    os.write(reinterpret_cast<char *>(&external), sizeof(external));
    os.write(reinterpret_cast<char *>(&reservedLinWakeupEvent1), sizeof(reservedLinWakeupEvent1));
    os.write(reinterpret_cast<char *>(&reservedLinWakeupEvent2), sizeof(reservedLinWakeupEvent2));
}

DWORD LinWakeupEvent2::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(lengthInfo) +
        sizeof(signal) +
        sizeof(external) +
        sizeof(reservedLinWakeupEvent1) +
        sizeof(reservedLinWakeupEvent2);
}

}
}
