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

#include <Vector/BLF/CanDriverStatistic.h>

namespace Vector {
namespace BLF {

CanDriverStatistic::CanDriverStatistic() :
    ObjectHeader(ObjectType::CAN_STATISTIC) {
}

std::vector<uint8_t>::iterator CanDriverStatistic::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    busLoad =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    standardDataFrames =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    extendedDataFrames =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    standardRemoteFrames =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    extendedRemoteFrames =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    errorFrames =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    overloadFrames =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    reservedCanDriverStatistic =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void CanDriverStatistic::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((busLoad >>  0) & 0xff);
    data.push_back((busLoad >>  8) & 0xff);
    data.push_back((standardDataFrames >>  0) & 0xff);
    data.push_back((standardDataFrames >>  8) & 0xff);
    data.push_back((standardDataFrames >> 16) & 0xff);
    data.push_back((standardDataFrames >> 24) & 0xff);
    data.push_back((extendedDataFrames >>  0) & 0xff);
    data.push_back((extendedDataFrames >>  8) & 0xff);
    data.push_back((extendedDataFrames >> 16) & 0xff);
    data.push_back((extendedDataFrames >> 24) & 0xff);
    data.push_back((standardRemoteFrames >>  0) & 0xff);
    data.push_back((standardRemoteFrames >>  8) & 0xff);
    data.push_back((standardRemoteFrames >> 16) & 0xff);
    data.push_back((standardRemoteFrames >> 24) & 0xff);
    data.push_back((extendedRemoteFrames >>  0) & 0xff);
    data.push_back((extendedRemoteFrames >>  8) & 0xff);
    data.push_back((extendedRemoteFrames >> 16) & 0xff);
    data.push_back((extendedRemoteFrames >> 24) & 0xff);
    data.push_back((errorFrames >>  0) & 0xff);
    data.push_back((errorFrames >>  8) & 0xff);
    data.push_back((errorFrames >> 16) & 0xff);
    data.push_back((errorFrames >> 24) & 0xff);
    data.push_back((overloadFrames >>  0) & 0xff);
    data.push_back((overloadFrames >>  8) & 0xff);
    data.push_back((overloadFrames >> 16) & 0xff);
    data.push_back((overloadFrames >> 24) & 0xff);
    data.push_back((reservedCanDriverStatistic >>  0) & 0xff);
    data.push_back((reservedCanDriverStatistic >>  8) & 0xff);
    data.push_back((reservedCanDriverStatistic >> 16) & 0xff);
    data.push_back((reservedCanDriverStatistic >> 24) & 0xff);
}

DWORD CanDriverStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(busLoad) +
        sizeof(standardDataFrames) +
        sizeof(extendedDataFrames) +
        sizeof(standardRemoteFrames) +
        sizeof(extendedRemoteFrames) +
        sizeof(errorFrames) +
        sizeof(overloadFrames) +
        sizeof(reservedCanDriverStatistic);
}

}
}
