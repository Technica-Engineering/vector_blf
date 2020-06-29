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

#include <Vector/BLF/MostDataLost.h>

namespace Vector {
namespace BLF {

MostDataLost::MostDataLost() :
    ObjectHeader2(ObjectType::MOST_DATALOST) {
}

std::vector<uint8_t>::iterator MostDataLost::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedMostDataLost =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    info =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    lostMsgsCtrl =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    lostMsgsAsync =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    lastGoodTimeStampNs =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    nextGoodTimeStampNs =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);

    return it;
}

void MostDataLost::toData(std::vector<uint8_t> & data) {
    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedMostDataLost >>  0) & 0xff);
    data.push_back((reservedMostDataLost >>  8) & 0xff);
    data.push_back((info >>  0) & 0xff);
    data.push_back((info >>  8) & 0xff);
    data.push_back((info >> 16) & 0xff);
    data.push_back((info >> 24) & 0xff);
    data.push_back((lostMsgsCtrl >>  0) & 0xff);
    data.push_back((lostMsgsCtrl >>  8) & 0xff);
    data.push_back((lostMsgsCtrl >> 16) & 0xff);
    data.push_back((lostMsgsCtrl >> 24) & 0xff);
    data.push_back((lostMsgsAsync >>  0) & 0xff);
    data.push_back((lostMsgsAsync >>  8) & 0xff);
    data.push_back((lostMsgsAsync >> 16) & 0xff);
    data.push_back((lostMsgsAsync >> 24) & 0xff);
    data.push_back((lastGoodTimeStampNs >>  0) & 0xff);
    data.push_back((lastGoodTimeStampNs >>  8) & 0xff);
    data.push_back((lastGoodTimeStampNs >> 16) & 0xff);
    data.push_back((lastGoodTimeStampNs >> 24) & 0xff);
    data.push_back((lastGoodTimeStampNs >> 32) & 0xff);
    data.push_back((lastGoodTimeStampNs >> 40) & 0xff);
    data.push_back((lastGoodTimeStampNs >> 48) & 0xff);
    data.push_back((lastGoodTimeStampNs >> 56) & 0xff);
    data.push_back((nextGoodTimeStampNs >>  0) & 0xff);
    data.push_back((nextGoodTimeStampNs >>  8) & 0xff);
    data.push_back((nextGoodTimeStampNs >> 16) & 0xff);
    data.push_back((nextGoodTimeStampNs >> 24) & 0xff);
    data.push_back((nextGoodTimeStampNs >> 32) & 0xff);
    data.push_back((nextGoodTimeStampNs >> 40) & 0xff);
    data.push_back((nextGoodTimeStampNs >> 48) & 0xff);
    data.push_back((nextGoodTimeStampNs >> 56) & 0xff);
}

DWORD MostDataLost::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedMostDataLost) +
        sizeof(info) +
        sizeof(lostMsgsCtrl) +
        sizeof(lostMsgsAsync) +
        sizeof(lastGoodTimeStampNs) +
        sizeof(nextGoodTimeStampNs);
}

}
}
