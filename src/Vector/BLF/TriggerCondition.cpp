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

std::vector<uint8_t>::iterator TriggerCondition::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    state =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    triggerBlockNameLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    triggerConditionLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    triggerBlockName.resize(triggerBlockNameLength);
    std::copy(it, it + triggerBlockName.size(), std::begin(triggerBlockName));
    it += triggerBlockName.size();
    triggerCondition.resize(triggerConditionLength);
    std::copy(it, it + triggerCondition.size(), std::begin(triggerCondition));
    it += triggerCondition.size();

    return it;
}

void TriggerCondition::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    triggerBlockNameLength = static_cast<DWORD>(triggerBlockName.size());
    triggerConditionLength = static_cast<DWORD>(triggerCondition.size());

    ObjectHeader::toData(data);

    data.push_back((state >>  0) & 0xff);
    data.push_back((state >>  8) & 0xff);
    data.push_back((state >> 16) & 0xff);
    data.push_back((state >> 24) & 0xff);
    data.push_back((triggerBlockNameLength >>  0) & 0xff);
    data.push_back((triggerBlockNameLength >>  8) & 0xff);
    data.push_back((triggerBlockNameLength >> 16) & 0xff);
    data.push_back((triggerBlockNameLength >> 24) & 0xff);
    data.push_back((triggerConditionLength >>  0) & 0xff);
    data.push_back((triggerConditionLength >>  8) & 0xff);
    data.push_back((triggerConditionLength >> 16) & 0xff);
    data.push_back((triggerConditionLength >> 24) & 0xff);
    data.insert(std::end(data), std::begin(triggerBlockName), std::end(triggerBlockName));
    data.insert(std::end(data), std::begin(triggerCondition), std::end(triggerCondition));
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
