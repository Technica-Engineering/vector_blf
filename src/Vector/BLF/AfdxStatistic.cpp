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

#include <Vector/BLF/AfdxStatistic.h>

namespace Vector {
namespace BLF {

AfdxStatistic::AfdxStatistic() :
    ObjectHeader(ObjectType::AFDX_STATISTIC) {
}

std::vector<uint8_t>::iterator AfdxStatistic::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    flags =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    rxPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    rxByteCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    txPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    txByteCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    collisionCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    errorCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statDroppedRedundantPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statRedundantErrorPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statIntegrityErrorPacketCount =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statAvrgPeriodMsec =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statAvrgJitterMysec =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    vlid =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);
    statDuration =
        (static_cast<ULONG>(*it++) <<  0) |
        (static_cast<ULONG>(*it++) <<  8) |
        (static_cast<ULONG>(*it++) << 16) |
        (static_cast<ULONG>(*it++) << 24);

    return it;
}

void AfdxStatistic::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((rxPacketCount >>  0) & 0xff);
    data.push_back((rxPacketCount >>  8) & 0xff);
    data.push_back((rxPacketCount >> 16) & 0xff);
    data.push_back((rxPacketCount >> 24) & 0xff);
    data.push_back((rxByteCount >>  0) & 0xff);
    data.push_back((rxByteCount >>  8) & 0xff);
    data.push_back((rxByteCount >> 16) & 0xff);
    data.push_back((rxByteCount >> 24) & 0xff);
    data.push_back((txPacketCount >>  0) & 0xff);
    data.push_back((txPacketCount >>  8) & 0xff);
    data.push_back((txPacketCount >> 16) & 0xff);
    data.push_back((txPacketCount >> 24) & 0xff);
    data.push_back((txByteCount >>  0) & 0xff);
    data.push_back((txByteCount >>  8) & 0xff);
    data.push_back((txByteCount >> 16) & 0xff);
    data.push_back((txByteCount >> 24) & 0xff);
    data.push_back((collisionCount >>  0) & 0xff);
    data.push_back((collisionCount >>  8) & 0xff);
    data.push_back((collisionCount >> 16) & 0xff);
    data.push_back((collisionCount >> 24) & 0xff);
    data.push_back((errorCount >>  0) & 0xff);
    data.push_back((errorCount >>  8) & 0xff);
    data.push_back((errorCount >> 16) & 0xff);
    data.push_back((errorCount >> 24) & 0xff);
    data.push_back((statDroppedRedundantPacketCount >>  0) & 0xff);
    data.push_back((statDroppedRedundantPacketCount >>  8) & 0xff);
    data.push_back((statDroppedRedundantPacketCount >> 16) & 0xff);
    data.push_back((statDroppedRedundantPacketCount >> 24) & 0xff);
    data.push_back((statRedundantErrorPacketCount >>  0) & 0xff);
    data.push_back((statRedundantErrorPacketCount >>  8) & 0xff);
    data.push_back((statRedundantErrorPacketCount >> 16) & 0xff);
    data.push_back((statRedundantErrorPacketCount >> 24) & 0xff);
    data.push_back((statIntegrityErrorPacketCount >>  0) & 0xff);
    data.push_back((statIntegrityErrorPacketCount >>  8) & 0xff);
    data.push_back((statIntegrityErrorPacketCount >> 16) & 0xff);
    data.push_back((statIntegrityErrorPacketCount >> 24) & 0xff);
    data.push_back((statAvrgPeriodMsec >>  0) & 0xff);
    data.push_back((statAvrgPeriodMsec >>  8) & 0xff);
    data.push_back((statAvrgPeriodMsec >> 16) & 0xff);
    data.push_back((statAvrgPeriodMsec >> 24) & 0xff);
    data.push_back((statAvrgJitterMysec >>  0) & 0xff);
    data.push_back((statAvrgJitterMysec >>  8) & 0xff);
    data.push_back((statAvrgJitterMysec >> 16) & 0xff);
    data.push_back((statAvrgJitterMysec >> 24) & 0xff);
    data.push_back((vlid >>  0) & 0xff);
    data.push_back((vlid >>  8) & 0xff);
    data.push_back((vlid >> 16) & 0xff);
    data.push_back((vlid >> 24) & 0xff);
    data.push_back((statDuration >>  0) & 0xff);
    data.push_back((statDuration >>  8) & 0xff);
    data.push_back((statDuration >> 16) & 0xff);
    data.push_back((statDuration >> 24) & 0xff);
}

DWORD AfdxStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(rxPacketCount) +
        sizeof(rxByteCount) +
        sizeof(txPacketCount) +
        sizeof(txByteCount) +
        sizeof(collisionCount) +
        sizeof(errorCount) +
        sizeof(statDroppedRedundantPacketCount) +
        sizeof(statRedundantErrorPacketCount) +
        sizeof(statIntegrityErrorPacketCount) +
        sizeof(statAvrgPeriodMsec) +
        sizeof(statAvrgJitterMysec) +
        sizeof(vlid) +
        sizeof(statDuration);
}

}
}
