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

#include <Vector/BLF/MostStatistic.h>

namespace Vector {
namespace BLF {

MostStatistic::MostStatistic() :
    ObjectHeader(ObjectType::MOST_STATISTIC) {
}

std::vector<uint8_t>::iterator MostStatistic::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    pktCnt =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    frmCnt =
        (static_cast<LONG>(*it++) <<  0) |
        (static_cast<LONG>(*it++) <<  8) |
        (static_cast<LONG>(*it++) << 16) |
        (static_cast<LONG>(*it++) << 24);
    lightCnt =
        (static_cast<LONG>(*it++) <<  0) |
        (static_cast<LONG>(*it++) <<  8) |
        (static_cast<LONG>(*it++) << 16) |
        (static_cast<LONG>(*it++) << 24);
    bufferLevel =
        (static_cast<LONG>(*it++) <<  0) |
        (static_cast<LONG>(*it++) <<  8) |
        (static_cast<LONG>(*it++) << 16) |
        (static_cast<LONG>(*it++) << 24);

    return it;
}

void MostStatistic::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((pktCnt >>  0) & 0xff);
    data.push_back((pktCnt >>  8) & 0xff);
    data.push_back((frmCnt >>  0) & 0xff);
    data.push_back((frmCnt >>  8) & 0xff);
    data.push_back((frmCnt >> 16) & 0xff);
    data.push_back((frmCnt >> 24) & 0xff);
    data.push_back((lightCnt >>  0) & 0xff);
    data.push_back((lightCnt >>  8) & 0xff);
    data.push_back((lightCnt >> 16) & 0xff);
    data.push_back((lightCnt >> 24) & 0xff);
    data.push_back((bufferLevel >>  0) & 0xff);
    data.push_back((bufferLevel >>  8) & 0xff);
    data.push_back((bufferLevel >> 16) & 0xff);
    data.push_back((bufferLevel >> 24) & 0xff);
}

DWORD MostStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(pktCnt) +
        sizeof(frmCnt) +
        sizeof(lightCnt) +
        sizeof(bufferLevel);
}

}
}
