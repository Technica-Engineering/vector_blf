/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/MostTrigger.h>

namespace Vector {
namespace BLF {

MostTrigger::MostTrigger() :
    ObjectHeader2(ObjectType::MOST_TRIGGER) {
}

void MostTrigger::read(RawFile & is) {
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&reservedMostTrigger), sizeof(reservedMostTrigger));
    is.read(reinterpret_cast<char *>(&mode), sizeof(mode));
    is.read(reinterpret_cast<char *>(&hw), sizeof(hw));
    is.read(reinterpret_cast<char *>(&previousTriggerValue), sizeof(previousTriggerValue));
    is.read(reinterpret_cast<char *>(&currentTriggerValue), sizeof(currentTriggerValue));
}

void MostTrigger::write(RawFile & os) {
    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&reservedMostTrigger), sizeof(reservedMostTrigger));
    os.write(reinterpret_cast<char *>(&mode), sizeof(mode));
    os.write(reinterpret_cast<char *>(&hw), sizeof(hw));
    os.write(reinterpret_cast<char *>(&previousTriggerValue), sizeof(previousTriggerValue));
    os.write(reinterpret_cast<char *>(&currentTriggerValue), sizeof(currentTriggerValue));
}

DWORD MostTrigger::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedMostTrigger) +
        sizeof(mode) +
        sizeof(hw) +
        sizeof(previousTriggerValue) +
        sizeof(currentTriggerValue);
}

}
}
