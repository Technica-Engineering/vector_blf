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

#include <Vector/BLF/WlanFrame.h>

namespace Vector {
namespace BLF {

WlanFrame::WlanFrame() :
    ObjectHeader(ObjectType::WLAN_FRAME) {
}

std::vector<uint8_t>::iterator WlanFrame::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    flags =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    radioChannel =
        (static_cast<BYTE>(*it++) <<  0);
    signalStrength =
        (static_cast<SHORT>(*it++) <<  0) |
        (static_cast<SHORT>(*it++) <<  8);
    signalQuality =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    frameLength =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    reservedWlanFrame =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameData.resize(frameLength);
    std::copy(it, it + frameData.size(), std::begin(frameData));
    it += frameLength;

    return it;
}

void WlanFrame::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    frameLength = static_cast<WORD>(frameData.size());

    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((radioChannel >>  0) & 0xff);
    data.push_back((signalStrength >>  0) & 0xff);
    data.push_back((signalStrength >>  8) & 0xff);
    data.push_back((signalQuality >>  0) & 0xff);
    data.push_back((signalQuality >>  8) & 0xff);
    data.push_back((frameLength >>  0) & 0xff);
    data.push_back((frameLength >>  8) & 0xff);
    data.push_back((reservedWlanFrame >>  0) & 0xff);
    data.push_back((reservedWlanFrame >>  8) & 0xff);
    data.push_back((reservedWlanFrame >> 16) & 0xff);
    data.push_back((reservedWlanFrame >> 24) & 0xff);
    data.insert(std::end(data), std::begin(frameData), std::end(frameData));
}

DWORD WlanFrame::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(dir) +
        sizeof(radioChannel) +
        sizeof(signalStrength) +
        sizeof(signalQuality) +
        sizeof(frameLength) +
        sizeof(reservedWlanFrame) +
        frameLength;
}

}
}
