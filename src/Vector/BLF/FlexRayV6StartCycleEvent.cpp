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

#include <Vector/BLF/FlexRayV6StartCycleEvent.h>

namespace Vector {
namespace BLF {

FlexRayV6StartCycleEvent::FlexRayV6StartCycleEvent() :
    ObjectHeader(ObjectType::FLEXRAY_CYCLE) {
}

std::vector<uint8_t>::iterator FlexRayV6StartCycleEvent::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    lowTime =
        (static_cast<BYTE>(*it++) <<  0);
    fpgaTick =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    fpgaTickOverflow =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    clientIndexFlexRayV6StartCycleEvent =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    clusterTime =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    std::copy(it, it + dataBytes.size(), std::begin(dataBytes));
    it += dataBytes.size();
    reservedFlexRayV6StartCycleEvent =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);

    return it;
}

void FlexRayV6StartCycleEvent::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((lowTime >>  0) & 0xff);
    data.push_back((fpgaTick >>  0) & 0xff);
    data.push_back((fpgaTick >>  8) & 0xff);
    data.push_back((fpgaTick >> 16) & 0xff);
    data.push_back((fpgaTick >> 24) & 0xff);
    data.push_back((fpgaTickOverflow >>  0) & 0xff);
    data.push_back((fpgaTickOverflow >>  8) & 0xff);
    data.push_back((fpgaTickOverflow >> 16) & 0xff);
    data.push_back((fpgaTickOverflow >> 24) & 0xff);
    data.push_back((clientIndexFlexRayV6StartCycleEvent >>  0) & 0xff);
    data.push_back((clientIndexFlexRayV6StartCycleEvent >>  8) & 0xff);
    data.push_back((clientIndexFlexRayV6StartCycleEvent >> 16) & 0xff);
    data.push_back((clientIndexFlexRayV6StartCycleEvent >> 24) & 0xff);
    data.push_back((clusterTime >>  0) & 0xff);
    data.push_back((clusterTime >>  8) & 0xff);
    data.push_back((clusterTime >> 16) & 0xff);
    data.push_back((clusterTime >> 24) & 0xff);
    data.insert(std::end(data), std::begin(dataBytes), std::end(dataBytes));
    data.push_back((reservedFlexRayV6StartCycleEvent >>  0) & 0xff);
    data.push_back((reservedFlexRayV6StartCycleEvent >>  8) & 0xff);
}

DWORD FlexRayV6StartCycleEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(lowTime) +
        sizeof(fpgaTick) +
        sizeof(fpgaTickOverflow) +
        sizeof(clientIndexFlexRayV6StartCycleEvent) +
        sizeof(clusterTime) +
        static_cast<DWORD>(dataBytes.size()) +
        sizeof(reservedFlexRayV6StartCycleEvent);
}

}
}
