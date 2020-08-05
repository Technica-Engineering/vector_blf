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

#include <Vector/BLF/LinMessage2.h>

namespace Vector {
namespace BLF {

LinMessage2::LinMessage2() :
    ObjectHeader(ObjectType::LIN_MESSAGE2, 1) {
}

std::vector<uint8_t>::iterator LinMessage2::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);
    it = LinDatabyteTimestampEvent::fromData(it);

    std::copy(it, it + this->data.size(), std::begin(data));
    it += this->data.size();
    crc =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    dir =
            (static_cast<BYTE>(*it++) <<  0);
    simulated =
            (static_cast<BYTE>(*it++) <<  0);
    isEtf =
            (static_cast<BYTE>(*it++) <<  0);
    etfAssocIndex =
            (static_cast<BYTE>(*it++) <<  0);
    etfAssocEtfId =
            (static_cast<BYTE>(*it++) <<  0);
    fsmId =
            (static_cast<BYTE>(*it++) <<  0);
    fsmState =
            (static_cast<BYTE>(*it++) <<  0);
    reservedLinMessage1 =
            (static_cast<BYTE>(*it++) <<  0);
    reservedLinMessage2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);

    /* the following variables are only available in Version 2 and above */
    /*if (objectVersion < 0)*/ // Vector bug: Shouldn't this be < 1?
    /*    return it;*/

    respBaudrate =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    /* the following variables are only available in Version 3 and above */
    if (objectVersion < 1)   // Vector bug: Shouldn't this be < 2?
        return it;

    uint64_t * ptr = reinterpret_cast<uint64_t *>(&exactHeaderBaudrate);
    *ptr =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
    earlyStopbitOffset =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    earlyStopbitOffsetResponse =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);

    return it;
}

void LinMessage2::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);
    LinDatabyteTimestampEvent::toData(data);

    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((simulated >>  0) & 0xff);
    data.push_back((isEtf >>  0) & 0xff);
    data.push_back((etfAssocIndex >>  0) & 0xff);
    data.push_back((etfAssocEtfId >>  0) & 0xff);
    data.push_back((fsmId >>  0) & 0xff);
    data.push_back((fsmState >>  0) & 0xff);
    data.push_back((reservedLinMessage1 >>  0) & 0xff);
    data.push_back((reservedLinMessage2 >>  0) & 0xff);
    data.push_back((reservedLinMessage2 >>  8) & 0xff);

    /* the following variables are only available in Version 2 and above */
    /*if (objectVersion < 0)*/ // Vector bug: Shouldn't this be < 1?
    /*    return;*/

    data.push_back((respBaudrate >>  0) & 0xff);
    data.push_back((respBaudrate >>  8) & 0xff);
    data.push_back((respBaudrate >> 16) & 0xff);
    data.push_back((respBaudrate >> 24) & 0xff);

    /* the following variables are only available in Version 3 and above */
    if (objectVersion < 1)   // Vector bug: Shouldn't this be < 2?
        return;

    uint64_t * ptr = reinterpret_cast<uint64_t *>(&exactHeaderBaudrate);
    data.push_back((*ptr >>  0) & 0xff);
    data.push_back((*ptr >>  8) & 0xff);
    data.push_back((*ptr >> 16) & 0xff);
    data.push_back((*ptr >> 24) & 0xff);
    data.push_back((*ptr >> 32) & 0xff);
    data.push_back((*ptr >> 40) & 0xff);
    data.push_back((*ptr >> 48) & 0xff);
    data.push_back((*ptr >> 56) & 0xff);
    data.push_back((earlyStopbitOffset >>  0) & 0xff);
    data.push_back((earlyStopbitOffset >>  8) & 0xff);
    data.push_back((earlyStopbitOffset >> 16) & 0xff);
    data.push_back((earlyStopbitOffset >> 24) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >>  0) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >>  8) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >> 16) & 0xff);
    data.push_back((earlyStopbitOffsetResponse >> 24) & 0xff);
}

DWORD LinMessage2::calculateObjectSize() const {
    DWORD size =
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        static_cast<DWORD>(data.size()) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(simulated) +
        sizeof(isEtf) +
        sizeof(etfAssocIndex) +
        sizeof(etfAssocEtfId) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(reservedLinMessage1) +
        sizeof(reservedLinMessage2);

    /*if (objectVersion >= 0)*/ // Vector bug: Shouldn't this be >= 1?
    size += sizeof(respBaudrate);

    if (objectVersion >= 1) // Vector bug: Shouldn't this be >= 2?
        size += sizeof(exactHeaderBaudrate) +
                sizeof(earlyStopbitOffset) +
                sizeof(earlyStopbitOffsetResponse);

    return size;
}

}
}
