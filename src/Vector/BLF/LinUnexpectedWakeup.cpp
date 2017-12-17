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

#include <Vector/BLF/LinUnexpectedWakeup.h>

namespace Vector {
namespace BLF {

LinUnexpectedWakeup::LinUnexpectedWakeup() :
    ObjectHeader(),
    LinBusEvent(),
    width(),
    signal(),
    reservedLinUnexpectedWakeup1(),
    reservedLinUnexpectedWakeup2(),
    reservedLinUnexpectedWakeup3()
{
    objectType = ObjectType::LIN_UNEXPECTED_WAKEUP;
}

void LinUnexpectedWakeup::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinBusEvent::read(is);
    is.read(reinterpret_cast<char *>(&width), sizeof(width));
    is.read(reinterpret_cast<char *>(&signal), sizeof(signal));
    is.read(reinterpret_cast<char *>(&reservedLinUnexpectedWakeup1), sizeof(reservedLinUnexpectedWakeup1));
    is.read(reinterpret_cast<char *>(&reservedLinUnexpectedWakeup2), sizeof(reservedLinUnexpectedWakeup2));
    is.read(reinterpret_cast<char *>(&reservedLinUnexpectedWakeup3), sizeof(reservedLinUnexpectedWakeup3));
}

void LinUnexpectedWakeup::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinBusEvent::write(os);
    os.write(reinterpret_cast<char *>(&width), sizeof(width));
    os.write(reinterpret_cast<char *>(&signal), sizeof(signal));
    os.write(reinterpret_cast<char *>(&reservedLinUnexpectedWakeup1), sizeof(reservedLinUnexpectedWakeup1));
    os.write(reinterpret_cast<char *>(&reservedLinUnexpectedWakeup2), sizeof(reservedLinUnexpectedWakeup2));
    os.write(reinterpret_cast<char *>(&reservedLinUnexpectedWakeup3), sizeof(reservedLinUnexpectedWakeup3));
}

DWORD LinUnexpectedWakeup::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        LinBusEvent::calculateObjectSize() +
        sizeof(width) +
        sizeof(signal) +
        sizeof(reservedLinUnexpectedWakeup1) +
        sizeof(reservedLinUnexpectedWakeup2) +
        sizeof(reservedLinUnexpectedWakeup3);
}

}
}
