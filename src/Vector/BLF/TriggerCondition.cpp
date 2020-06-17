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

#include <Vector/BLF/TriggerCondition.h>

namespace Vector {
namespace BLF {

TriggerCondition::TriggerCondition() :
    ObjectHeader(ObjectType::TRIGGER_CONDITION) {
}

void TriggerCondition::read(RawFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&state), sizeof(state));
    is.read(reinterpret_cast<char *>(&triggerBlockNameLength), sizeof(triggerBlockNameLength));
    is.read(reinterpret_cast<char *>(&triggerConditionLength), sizeof(triggerConditionLength));
    triggerBlockName.resize(triggerBlockNameLength);
    is.read(&triggerBlockName[0], triggerBlockNameLength);
    triggerCondition.resize(triggerConditionLength);
    is.read(&triggerCondition[0], triggerConditionLength);
}

void TriggerCondition::write(RawFile & os) {
    /* pre processing */
    triggerBlockNameLength = static_cast<DWORD>(triggerBlockName.size());
    triggerConditionLength = static_cast<DWORD>(triggerCondition.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&state), sizeof(state));
    os.write(reinterpret_cast<char *>(&triggerBlockNameLength), sizeof(triggerBlockNameLength));
    os.write(reinterpret_cast<char *>(&triggerConditionLength), sizeof(triggerConditionLength));
    os.write(&triggerBlockName[0], triggerBlockNameLength);
    os.write(&triggerCondition[0], triggerConditionLength);
}

DWORD TriggerCondition::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(state) +
        sizeof(triggerBlockNameLength) +
        sizeof(triggerConditionLength) +
        triggerBlockNameLength +
        triggerConditionLength;
}

}
}
