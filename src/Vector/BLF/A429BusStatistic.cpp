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

#include <Vector/BLF/A429BusStatistic.h>

#include <algorithm>

namespace Vector {
namespace BLF {

A429BusStatistic::A429BusStatistic() :
    ObjectHeader(ObjectType::A429_BUS_STATISTIC) {
}

std::vector<uint8_t>::iterator A429BusStatistic::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    reservedA429BusStatistic =
        (static_cast<BYTE>(*it++) <<  0);
    busload =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    dataTotal =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    errorTotal =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    bitrate =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    parityErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    bitrateErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    gapErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    lineErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    formatErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    dutyFactorErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    wordLenErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    codingErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    idleErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    levelErrors =
        (static_cast<USHORT>(*it++) <<  0) |
        (static_cast<USHORT>(*it++) <<  8);
    std::generate(labelCount.begin(), labelCount.end(), [&it]() {
        return
            (static_cast<USHORT>(*it++) <<  0) |
            (static_cast<USHORT>(*it++) <<  8);
    });

    return it;
}

void A429BusStatistic::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((reservedA429BusStatistic >>  0) & 0xff);
    data.push_back((busload >>  0) & 0xff);
    data.push_back((busload >>  8) & 0xff);
    data.push_back((busload >> 16) & 0xff);
    data.push_back((busload >> 24) & 0xff);
    data.push_back((dataTotal >>  0) & 0xff);
    data.push_back((dataTotal >>  8) & 0xff);
    data.push_back((dataTotal >> 16) & 0xff);
    data.push_back((dataTotal >> 24) & 0xff);
    data.push_back((errorTotal >>  0) & 0xff);
    data.push_back((errorTotal >>  8) & 0xff);
    data.push_back((errorTotal >> 16) & 0xff);
    data.push_back((errorTotal >> 24) & 0xff);
    data.push_back((bitrate >>  0) & 0xff);
    data.push_back((bitrate >>  8) & 0xff);
    data.push_back((bitrate >> 16) & 0xff);
    data.push_back((bitrate >> 24) & 0xff);
    data.push_back((parityErrors >>  0) & 0xff);
    data.push_back((parityErrors >>  8) & 0xff);
    data.push_back((bitrateErrors >>  0) & 0xff);
    data.push_back((bitrateErrors >>  8) & 0xff);
    data.push_back((gapErrors >>  0) & 0xff);
    data.push_back((gapErrors >>  8) & 0xff);
    data.push_back((lineErrors >>  0) & 0xff);
    data.push_back((lineErrors >>  8) & 0xff);
    data.push_back((formatErrors >>  0) & 0xff);
    data.push_back((formatErrors >>  8) & 0xff);
    data.push_back((dutyFactorErrors >>  0) & 0xff);
    data.push_back((dutyFactorErrors >>  8) & 0xff);
    data.push_back((wordLenErrors >>  0) & 0xff);
    data.push_back((wordLenErrors >>  8) & 0xff);
    data.push_back((codingErrors >>  0) & 0xff);
    data.push_back((codingErrors >>  8) & 0xff);
    data.push_back((idleErrors >>  0) & 0xff);
    data.push_back((idleErrors >>  8) & 0xff);
    data.push_back((levelErrors >>  0) & 0xff);
    data.push_back((levelErrors >>  8) & 0xff);
    std::for_each(labelCount.begin(), labelCount.end(), [&data](const USHORT & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
    });
}

DWORD A429BusStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedA429BusStatistic) +
        sizeof(busload) +
        sizeof(dataTotal) +
        sizeof(errorTotal) +
        sizeof(bitrate) +
        sizeof(parityErrors) +
        sizeof(bitrateErrors) +
        sizeof(gapErrors) +
        sizeof(lineErrors) +
        sizeof(formatErrors) +
        sizeof(dutyFactorErrors) +
        sizeof(wordLenErrors) +
        sizeof(codingErrors) +
        sizeof(idleErrors) +
        sizeof(levelErrors) +
        static_cast<DWORD>(labelCount.size() * sizeof(USHORT));
}

}
}
