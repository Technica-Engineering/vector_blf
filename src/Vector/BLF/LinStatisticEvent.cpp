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

#include <Vector/BLF/LinStatisticEvent.h>

namespace Vector {
namespace BLF {

LinStatisticEvent::LinStatisticEvent() :
    ObjectHeader(ObjectType::LIN_STATISTIC) {
}

std::vector<uint8_t>::iterator LinStatisticEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedLinStatisticEvent1 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedLinStatisticEvent2 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    uint64_t * ptr = reinterpret_cast<uint64_t *>(&busLoad);
    *ptr =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
    burstsTotal =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    burstsOverrun =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    framesSent =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    framesReceived =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    framesUnanswered =
            (static_cast<ULONG>(*it++) <<  0) |
            (static_cast<ULONG>(*it++) <<  8) |
            (static_cast<ULONG>(*it++) << 16) |
            (static_cast<ULONG>(*it++) << 24);
    reservedLinStatisticEvent3 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void LinStatisticEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedLinStatisticEvent1 >>  0) & 0xff);
    data.push_back((reservedLinStatisticEvent1 >>  8) & 0xff);
    data.push_back((reservedLinStatisticEvent2 >>  0) & 0xff);
    data.push_back((reservedLinStatisticEvent2 >>  8) & 0xff);
    data.push_back((reservedLinStatisticEvent2 >> 16) & 0xff);
    data.push_back((reservedLinStatisticEvent2 >> 24) & 0xff);
    uint64_t * ptr = reinterpret_cast<uint64_t *>(&busLoad);
    data.push_back((*ptr >>  0) & 0xff);
    data.push_back((*ptr >>  8) & 0xff);
    data.push_back((*ptr >> 16) & 0xff);
    data.push_back((*ptr >> 24) & 0xff);
    data.push_back((*ptr >> 32) & 0xff);
    data.push_back((*ptr >> 40) & 0xff);
    data.push_back((*ptr >> 48) & 0xff);
    data.push_back((*ptr >> 56) & 0xff);
    data.push_back((burstsTotal >>  0) & 0xff);
    data.push_back((burstsTotal >>  8) & 0xff);
    data.push_back((burstsTotal >> 16) & 0xff);
    data.push_back((burstsTotal >> 24) & 0xff);
    data.push_back((burstsOverrun >>  0) & 0xff);
    data.push_back((burstsOverrun >>  8) & 0xff);
    data.push_back((burstsOverrun >> 16) & 0xff);
    data.push_back((burstsOverrun >> 24) & 0xff);
    data.push_back((framesSent >>  0) & 0xff);
    data.push_back((framesSent >>  8) & 0xff);
    data.push_back((framesSent >> 16) & 0xff);
    data.push_back((framesSent >> 24) & 0xff);
    data.push_back((framesReceived >>  0) & 0xff);
    data.push_back((framesReceived >>  8) & 0xff);
    data.push_back((framesReceived >> 16) & 0xff);
    data.push_back((framesReceived >> 24) & 0xff);
    data.push_back((framesUnanswered >>  0) & 0xff);
    data.push_back((framesUnanswered >>  8) & 0xff);
    data.push_back((framesUnanswered >> 16) & 0xff);
    data.push_back((framesUnanswered >> 24) & 0xff);
    data.push_back((reservedLinStatisticEvent3 >>  0) & 0xff);
    data.push_back((reservedLinStatisticEvent3 >>  8) & 0xff);
    data.push_back((reservedLinStatisticEvent3 >> 16) & 0xff);
    data.push_back((reservedLinStatisticEvent3 >> 24) & 0xff);
}

DWORD LinStatisticEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedLinStatisticEvent1) +
        sizeof(reservedLinStatisticEvent2) +
        sizeof(busLoad) +
        sizeof(burstsTotal) +
        sizeof(burstsOverrun) +
        sizeof(framesSent) +
        sizeof(framesReceived) +
        sizeof(framesUnanswered) +
        sizeof(reservedLinStatisticEvent3);
}

}
}
