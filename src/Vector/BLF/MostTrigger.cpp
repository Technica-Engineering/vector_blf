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

std::vector<uint8_t>::iterator MostTrigger::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedMostTrigger =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    mode =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    hw =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    previousTriggerValue =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    currentTriggerValue =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void MostTrigger::toData(std::vector<uint8_t> & data) {
    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedMostTrigger >>  0) & 0xff);
    data.push_back((reservedMostTrigger >>  8) & 0xff);
    data.push_back((mode >>  0) & 0xff);
    data.push_back((mode >>  8) & 0xff);
    data.push_back((hw >>  0) & 0xff);
    data.push_back((hw >>  8) & 0xff);
    data.push_back((previousTriggerValue >>  0) & 0xff);
    data.push_back((previousTriggerValue >>  8) & 0xff);
    data.push_back((previousTriggerValue >> 16) & 0xff);
    data.push_back((previousTriggerValue >> 24) & 0xff);
    data.push_back((currentTriggerValue >>  0) & 0xff);
    data.push_back((currentTriggerValue >>  8) & 0xff);
    data.push_back((currentTriggerValue >> 16) & 0xff);
    data.push_back((currentTriggerValue >> 24) & 0xff);
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
