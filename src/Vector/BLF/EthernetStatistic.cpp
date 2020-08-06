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

#include <Vector/BLF/EthernetStatistic.h>

namespace Vector {
namespace BLF {

EthernetStatistic::EthernetStatistic() :
    ObjectHeader(ObjectType::ETHERNET_STATISTIC) {
}

std::vector<uint8_t>::iterator EthernetStatistic::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedEthernetStatistic1 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedEthernetStatistic2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    rcvOk_HW =
        (static_cast<UINT64>(*it++) <<  0) |
        (static_cast<UINT64>(*it++) <<  8) |
        (static_cast<UINT64>(*it++) << 16) |
        (static_cast<UINT64>(*it++) << 24) |
        (static_cast<UINT64>(*it++) << 32) |
        (static_cast<UINT64>(*it++) << 40) |
        (static_cast<UINT64>(*it++) << 48) |
        (static_cast<UINT64>(*it++) << 56);
    xmitOk_HW =
        (static_cast<UINT64>(*it++) <<  0) |
        (static_cast<UINT64>(*it++) <<  8) |
        (static_cast<UINT64>(*it++) << 16) |
        (static_cast<UINT64>(*it++) << 24) |
        (static_cast<UINT64>(*it++) << 32) |
        (static_cast<UINT64>(*it++) << 40) |
        (static_cast<UINT64>(*it++) << 48) |
        (static_cast<UINT64>(*it++) << 56);
    rcvError_HW =
        (static_cast<UINT64>(*it++) <<  0) |
        (static_cast<UINT64>(*it++) <<  8) |
        (static_cast<UINT64>(*it++) << 16) |
        (static_cast<UINT64>(*it++) << 24) |
        (static_cast<UINT64>(*it++) << 32) |
        (static_cast<UINT64>(*it++) << 40) |
        (static_cast<UINT64>(*it++) << 48) |
        (static_cast<UINT64>(*it++) << 56);
    xmitError_HW =
        (static_cast<UINT64>(*it++) <<  0) |
        (static_cast<UINT64>(*it++) <<  8) |
        (static_cast<UINT64>(*it++) << 16) |
        (static_cast<UINT64>(*it++) << 24) |
        (static_cast<UINT64>(*it++) << 32) |
        (static_cast<UINT64>(*it++) << 40) |
        (static_cast<UINT64>(*it++) << 48) |
        (static_cast<UINT64>(*it++) << 56);
    rcvBytes_HW =
        (static_cast<UINT64>(*it++) <<  0) |
        (static_cast<UINT64>(*it++) <<  8) |
        (static_cast<UINT64>(*it++) << 16) |
        (static_cast<UINT64>(*it++) << 24) |
        (static_cast<UINT64>(*it++) << 32) |
        (static_cast<UINT64>(*it++) << 40) |
        (static_cast<UINT64>(*it++) << 48) |
        (static_cast<UINT64>(*it++) << 56);
    xmitBytes_HW =
        (static_cast<UINT64>(*it++) <<  0) |
        (static_cast<UINT64>(*it++) <<  8) |
        (static_cast<UINT64>(*it++) << 16) |
        (static_cast<UINT64>(*it++) << 24) |
        (static_cast<UINT64>(*it++) << 32) |
        (static_cast<UINT64>(*it++) << 40) |
        (static_cast<UINT64>(*it++) << 48) |
        (static_cast<UINT64>(*it++) << 56);
    rcvNoBuffer_HW =
        (static_cast<UINT64>(*it++) <<  0) |
        (static_cast<UINT64>(*it++) <<  8) |
        (static_cast<UINT64>(*it++) << 16) |
        (static_cast<UINT64>(*it++) << 24) |
        (static_cast<UINT64>(*it++) << 32) |
        (static_cast<UINT64>(*it++) << 40) |
        (static_cast<UINT64>(*it++) << 48) |
        (static_cast<UINT64>(*it++) << 56);
    sqi =
        (static_cast<SHORT>(*it++) <<  0) |
        (static_cast<SHORT>(*it++) <<  8);
    hardwareChannel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedEthernetStatistic3 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void EthernetStatistic::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((reservedEthernetStatistic1 >>  0) & 0xff);
    data.push_back((reservedEthernetStatistic1 >>  8) & 0xff);
    data.push_back((reservedEthernetStatistic2 >>  0) & 0xff);
    data.push_back((reservedEthernetStatistic2 >>  8) & 0xff);
    data.push_back((reservedEthernetStatistic2 >> 16) & 0xff);
    data.push_back((reservedEthernetStatistic2 >> 24) & 0xff);
    data.push_back((rcvOk_HW >>  0) & 0xff);
    data.push_back((rcvOk_HW >>  8) & 0xff);
    data.push_back((rcvOk_HW >> 16) & 0xff);
    data.push_back((rcvOk_HW >> 24) & 0xff);
    data.push_back((rcvOk_HW >> 32) & 0xff);
    data.push_back((rcvOk_HW >> 40) & 0xff);
    data.push_back((rcvOk_HW >> 48) & 0xff);
    data.push_back((rcvOk_HW >> 56) & 0xff);
    data.push_back((xmitOk_HW >>  0) & 0xff);
    data.push_back((xmitOk_HW >>  8) & 0xff);
    data.push_back((xmitOk_HW >> 16) & 0xff);
    data.push_back((xmitOk_HW >> 24) & 0xff);
    data.push_back((xmitOk_HW >> 32) & 0xff);
    data.push_back((xmitOk_HW >> 40) & 0xff);
    data.push_back((xmitOk_HW >> 48) & 0xff);
    data.push_back((xmitOk_HW >> 56) & 0xff);
    data.push_back((rcvError_HW >>  0) & 0xff);
    data.push_back((rcvError_HW >>  8) & 0xff);
    data.push_back((rcvError_HW >> 16) & 0xff);
    data.push_back((rcvError_HW >> 24) & 0xff);
    data.push_back((rcvError_HW >> 32) & 0xff);
    data.push_back((rcvError_HW >> 40) & 0xff);
    data.push_back((rcvError_HW >> 48) & 0xff);
    data.push_back((rcvError_HW >> 56) & 0xff);
    data.push_back((xmitError_HW >>  0) & 0xff);
    data.push_back((xmitError_HW >>  8) & 0xff);
    data.push_back((xmitError_HW >> 16) & 0xff);
    data.push_back((xmitError_HW >> 24) & 0xff);
    data.push_back((xmitError_HW >> 32) & 0xff);
    data.push_back((xmitError_HW >> 40) & 0xff);
    data.push_back((xmitError_HW >> 48) & 0xff);
    data.push_back((xmitError_HW >> 56) & 0xff);
    data.push_back((rcvBytes_HW >>  0) & 0xff);
    data.push_back((rcvBytes_HW >>  8) & 0xff);
    data.push_back((rcvBytes_HW >> 16) & 0xff);
    data.push_back((rcvBytes_HW >> 24) & 0xff);
    data.push_back((rcvBytes_HW >> 32) & 0xff);
    data.push_back((rcvBytes_HW >> 40) & 0xff);
    data.push_back((rcvBytes_HW >> 48) & 0xff);
    data.push_back((rcvBytes_HW >> 56) & 0xff);
    data.push_back((xmitBytes_HW >>  0) & 0xff);
    data.push_back((xmitBytes_HW >>  8) & 0xff);
    data.push_back((xmitBytes_HW >> 16) & 0xff);
    data.push_back((xmitBytes_HW >> 24) & 0xff);
    data.push_back((xmitBytes_HW >> 32) & 0xff);
    data.push_back((xmitBytes_HW >> 40) & 0xff);
    data.push_back((xmitBytes_HW >> 48) & 0xff);
    data.push_back((xmitBytes_HW >> 56) & 0xff);
    data.push_back((rcvNoBuffer_HW >>  0) & 0xff);
    data.push_back((rcvNoBuffer_HW >>  8) & 0xff);
    data.push_back((rcvNoBuffer_HW >> 16) & 0xff);
    data.push_back((rcvNoBuffer_HW >> 24) & 0xff);
    data.push_back((rcvNoBuffer_HW >> 32) & 0xff);
    data.push_back((rcvNoBuffer_HW >> 40) & 0xff);
    data.push_back((rcvNoBuffer_HW >> 48) & 0xff);
    data.push_back((rcvNoBuffer_HW >> 56) & 0xff);
    data.push_back((sqi >>  0) & 0xff);
    data.push_back((sqi >>  8) & 0xff);
    data.push_back((hardwareChannel >>  0) & 0xff);
    data.push_back((hardwareChannel >>  8) & 0xff);
    data.push_back((reservedEthernetStatistic3 >>  0) & 0xff);
    data.push_back((reservedEthernetStatistic3 >>  8) & 0xff);
    data.push_back((reservedEthernetStatistic3 >> 16) & 0xff);
    data.push_back((reservedEthernetStatistic3 >> 24) & 0xff);
}

DWORD EthernetStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedEthernetStatistic1) +
        sizeof(reservedEthernetStatistic2) +
        sizeof(rcvOk_HW) +
        sizeof(xmitOk_HW) +
        sizeof(rcvError_HW) +
        sizeof(xmitError_HW) +
        sizeof(rcvBytes_HW) +
        sizeof(xmitBytes_HW) +
        sizeof(rcvNoBuffer_HW) +
        sizeof(sqi) +
        sizeof(hardwareChannel) +
        sizeof(reservedEthernetStatistic3);
}

}
}
