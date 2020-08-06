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

#include <Vector/BLF/FlexRayVFrReceiveMsgEx.h>

#include <algorithm>

namespace Vector {
namespace BLF {

FlexRayVFrReceiveMsgEx::FlexRayVFrReceiveMsgEx() :
    ObjectHeader(ObjectType::FR_RCVMESSAGE_EX) {
}

std::vector<uint8_t>::iterator FlexRayVFrReceiveMsgEx::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    version =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    channelMask =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    clientIndexFlexRayVFrReceiveMsgEx =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    clusterNo =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameId =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    headerCrc1 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    headerCrc2 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    byteCount =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dataCount =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    cycle =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    tag =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    this->data =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameFlags =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    appParameter =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameCrc =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameLengthNs =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameId1 =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    pduOffset =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    blfLogMask =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    std::generate(reservedFlexRayVFrReceiveMsgEx.begin(), reservedFlexRayVFrReceiveMsgEx.end(), [&it]() {
        return
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    });
    dataBytes.assign(it, it + dataCount);
    it += dataCount;

    return it;
}

void FlexRayVFrReceiveMsgEx::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    dataCount = static_cast<WORD>(dataBytes.size());

    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((version >>  0) & 0xff);
    data.push_back((version >>  8) & 0xff);
    data.push_back((channelMask >>  0) & 0xff);
    data.push_back((channelMask >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((dir >>  8) & 0xff);
    data.push_back((clientIndexFlexRayVFrReceiveMsgEx >>  0) & 0xff);
    data.push_back((clientIndexFlexRayVFrReceiveMsgEx >>  8) & 0xff);
    data.push_back((clientIndexFlexRayVFrReceiveMsgEx >> 16) & 0xff);
    data.push_back((clientIndexFlexRayVFrReceiveMsgEx >> 24) & 0xff);
    data.push_back((clusterNo >>  0) & 0xff);
    data.push_back((clusterNo >>  8) & 0xff);
    data.push_back((clusterNo >> 16) & 0xff);
    data.push_back((clusterNo >> 24) & 0xff);
    data.push_back((frameId >>  0) & 0xff);
    data.push_back((frameId >>  8) & 0xff);
    data.push_back((headerCrc1 >>  0) & 0xff);
    data.push_back((headerCrc1 >>  8) & 0xff);
    data.push_back((headerCrc2 >>  0) & 0xff);
    data.push_back((headerCrc2 >>  8) & 0xff);
    data.push_back((byteCount >>  0) & 0xff);
    data.push_back((byteCount >>  8) & 0xff);
    data.push_back((dataCount >>  0) & 0xff);
    data.push_back((dataCount >>  8) & 0xff);
    data.push_back((cycle >>  0) & 0xff);
    data.push_back((cycle >>  8) & 0xff);
    data.push_back((tag >>  0) & 0xff);
    data.push_back((tag >>  8) & 0xff);
    data.push_back((tag >> 16) & 0xff);
    data.push_back((tag >> 24) & 0xff);
    data.push_back((this->data >>  0) & 0xff);
    data.push_back((this->data >>  8) & 0xff);
    data.push_back((this->data >> 16) & 0xff);
    data.push_back((this->data >> 24) & 0xff);
    data.push_back((frameFlags >>  0) & 0xff);
    data.push_back((frameFlags >>  8) & 0xff);
    data.push_back((frameFlags >> 16) & 0xff);
    data.push_back((frameFlags >> 24) & 0xff);
    data.push_back((appParameter >>  0) & 0xff);
    data.push_back((appParameter >>  8) & 0xff);
    data.push_back((appParameter >> 16) & 0xff);
    data.push_back((appParameter >> 24) & 0xff);
    data.push_back((frameCrc >>  0) & 0xff);
    data.push_back((frameCrc >>  8) & 0xff);
    data.push_back((frameCrc >> 16) & 0xff);
    data.push_back((frameCrc >> 24) & 0xff);
    data.push_back((frameLengthNs >>  0) & 0xff);
    data.push_back((frameLengthNs >>  8) & 0xff);
    data.push_back((frameLengthNs >> 16) & 0xff);
    data.push_back((frameLengthNs >> 24) & 0xff);
    data.push_back((frameId1 >>  0) & 0xff);
    data.push_back((frameId1 >>  8) & 0xff);
    data.push_back((pduOffset >>  0) & 0xff);
    data.push_back((pduOffset >>  8) & 0xff);
    data.push_back((blfLogMask >>  0) & 0xff);
    data.push_back((blfLogMask >>  8) & 0xff);
    std::for_each(reservedFlexRayVFrReceiveMsgEx.begin(), reservedFlexRayVFrReceiveMsgEx.end(), [&data](const WORD & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
    });
    data.insert(std::end(data), std::begin(dataBytes), std::end(dataBytes));
}

DWORD FlexRayVFrReceiveMsgEx::calculateObjectSize() const {
    DWORD size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(dir) +
        sizeof(clientIndexFlexRayVFrReceiveMsgEx) +
        sizeof(clusterNo) +
        sizeof(frameId) +
        sizeof(headerCrc1) +
        sizeof(headerCrc2) +
        sizeof(byteCount) +
        sizeof(dataCount) +
        sizeof(cycle) +
        sizeof(tag) +
        sizeof(data) +
        sizeof(frameFlags) +
        sizeof(appParameter) +
        sizeof(frameCrc) +
        sizeof(frameLengthNs) +
        sizeof(frameId1) +
        sizeof(pduOffset) +
        sizeof(blfLogMask) +
        static_cast<DWORD>(reservedFlexRayVFrReceiveMsgEx.size() * sizeof(WORD)) +
        dataCount;

    return size;
}

}
}
