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

#include <Vector/BLF/MostStatisticEx.h>

namespace Vector {
namespace BLF {

MostStatisticEx::MostStatisticEx() :
    ObjectHeader2(ObjectType::MOST_STATISTICEX) {
}

std::vector<uint8_t>::iterator MostStatisticEx::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedMostStatisticEx1 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    codingErrors =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    frameCounter =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    reservedMostStatisticEx2 =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void MostStatisticEx::toData(std::vector<uint8_t> & data) {
    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedMostStatisticEx1 >>  0) & 0xff);
    data.push_back((reservedMostStatisticEx1 >>  8) & 0xff);
    data.push_back((codingErrors >>  0) & 0xff);
    data.push_back((codingErrors >>  8) & 0xff);
    data.push_back((codingErrors >> 16) & 0xff);
    data.push_back((codingErrors >> 24) & 0xff);
    data.push_back((frameCounter >>  0) & 0xff);
    data.push_back((frameCounter >>  8) & 0xff);
    data.push_back((frameCounter >> 16) & 0xff);
    data.push_back((frameCounter >> 24) & 0xff);
    data.push_back((reservedMostStatisticEx2 >>  0) & 0xff);
    data.push_back((reservedMostStatisticEx2 >>  8) & 0xff);
    data.push_back((reservedMostStatisticEx2 >> 16) & 0xff);
    data.push_back((reservedMostStatisticEx2 >> 24) & 0xff);
}

DWORD MostStatisticEx::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedMostStatisticEx1) +
        sizeof(codingErrors) +
        sizeof(frameCounter) +
        sizeof(reservedMostStatisticEx2);
}

}
}
