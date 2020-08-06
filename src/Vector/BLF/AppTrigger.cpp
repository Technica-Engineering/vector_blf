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

#include <Vector/BLF/AppTrigger.h>

namespace Vector {
namespace BLF {

AppTrigger::AppTrigger() :
    ObjectHeader(ObjectType::APP_TRIGGER) {
}

std::vector<uint8_t>::iterator AppTrigger::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    preTriggerTime =
        (static_cast<ULONGLONG>(*it++) <<  0) |
        (static_cast<ULONGLONG>(*it++) <<  8) |
        (static_cast<ULONGLONG>(*it++) << 16) |
        (static_cast<ULONGLONG>(*it++) << 24) |
        (static_cast<ULONGLONG>(*it++) << 32) |
        (static_cast<ULONGLONG>(*it++) << 40) |
        (static_cast<ULONGLONG>(*it++) << 48) |
        (static_cast<ULONGLONG>(*it++) << 56);
    postTriggerTime =
        (static_cast<ULONGLONG>(*it++) <<  0) |
        (static_cast<ULONGLONG>(*it++) <<  8) |
        (static_cast<ULONGLONG>(*it++) << 16) |
        (static_cast<ULONGLONG>(*it++) << 24) |
        (static_cast<ULONGLONG>(*it++) << 32) |
        (static_cast<ULONGLONG>(*it++) << 40) |
        (static_cast<ULONGLONG>(*it++) << 48) |
        (static_cast<ULONGLONG>(*it++) << 56);
    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    flags =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    appSpecific2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void AppTrigger::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((preTriggerTime >>  0) & 0xff);
    data.push_back((preTriggerTime >>  8) & 0xff);
    data.push_back((preTriggerTime >> 16) & 0xff);
    data.push_back((preTriggerTime >> 24) & 0xff);
    data.push_back((preTriggerTime >> 32) & 0xff);
    data.push_back((preTriggerTime >> 40) & 0xff);
    data.push_back((preTriggerTime >> 48) & 0xff);
    data.push_back((preTriggerTime >> 56) & 0xff);
    data.push_back((postTriggerTime >>  0) & 0xff);
    data.push_back((postTriggerTime >>  8) & 0xff);
    data.push_back((postTriggerTime >> 16) & 0xff);
    data.push_back((postTriggerTime >> 24) & 0xff);
    data.push_back((postTriggerTime >> 32) & 0xff);
    data.push_back((postTriggerTime >> 40) & 0xff);
    data.push_back((postTriggerTime >> 48) & 0xff);
    data.push_back((postTriggerTime >> 56) & 0xff);
    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((appSpecific2 >>  0) & 0xff);
    data.push_back((appSpecific2 >>  8) & 0xff);
    data.push_back((appSpecific2 >> 16) & 0xff);
    data.push_back((appSpecific2 >> 24) & 0xff);
}

DWORD AppTrigger::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(preTriggerTime) +
        sizeof(postTriggerTime) +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(appSpecific2);
}

}
}
