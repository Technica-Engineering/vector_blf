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

#include <Vector/BLF/EthernetRxError.h>

namespace Vector {
namespace BLF {

EthernetRxError::EthernetRxError() :
    ObjectHeader(ObjectType::ETHERNET_RX_ERROR) {
}

std::vector<uint8_t>::iterator EthernetRxError::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    structLength =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    hardwareChannel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    fcs =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameDataLength =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedEthernetRxError =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    error =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameData.resize(frameDataLength);
    std::copy(it, it + frameData.size(), std::begin(frameData));
    it += frameDataLength;

    return it;
}

void EthernetRxError::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    structLength = calculateStructLength();
    frameDataLength = static_cast<WORD>(frameData.size());

    ObjectHeader::toData(data);

    data.push_back((structLength >>  0) & 0xff);
    data.push_back((structLength >>  8) & 0xff);
    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((dir >>  8) & 0xff);
    data.push_back((hardwareChannel >>  0) & 0xff);
    data.push_back((hardwareChannel >>  8) & 0xff);
    data.push_back((fcs >>  0) & 0xff);
    data.push_back((fcs >>  8) & 0xff);
    data.push_back((fcs >> 16) & 0xff);
    data.push_back((fcs >> 24) & 0xff);
    data.push_back((frameDataLength >>  0) & 0xff);
    data.push_back((frameDataLength >>  8) & 0xff);
    data.push_back((reservedEthernetRxError >>  0) & 0xff);
    data.push_back((reservedEthernetRxError >>  8) & 0xff);
    data.push_back((error >>  0) & 0xff);
    data.push_back((error >>  8) & 0xff);
    data.push_back((error >> 16) & 0xff);
    data.push_back((error >> 24) & 0xff);
    data.insert(std::end(data), std::begin(frameData), std::end(frameData));
}

DWORD EthernetRxError::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(structLength) +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(hardwareChannel) +
        sizeof(fcs) +
        sizeof(frameDataLength) +
        sizeof(reservedEthernetRxError) +
        sizeof(error) +
        frameDataLength;
}

WORD EthernetRxError::calculateStructLength() const {
    return
        sizeof(structLength) +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(hardwareChannel) +
        sizeof(fcs) +
        sizeof(frameDataLength) +
        sizeof(reservedEthernetRxError) +
        sizeof(error);
}

}
}
