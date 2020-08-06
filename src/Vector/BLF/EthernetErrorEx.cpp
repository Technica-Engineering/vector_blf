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

#include <Vector/BLF/EthernetErrorEx.h>

namespace Vector {
namespace BLF {

EthernetErrorEx::EthernetErrorEx() :
    ObjectHeader(ObjectType::ETHERNET_ERROR_EX) {
}

std::vector<uint8_t>::iterator EthernetErrorEx::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    structLength =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    flags =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    hardwareChannel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    frameDuration =
        (static_cast<UINT64>(*it++) <<  0) |
        (static_cast<UINT64>(*it++) <<  8) |
        (static_cast<UINT64>(*it++) << 16) |
        (static_cast<UINT64>(*it++) << 24) |
        (static_cast<UINT64>(*it++) << 32) |
        (static_cast<UINT64>(*it++) << 40) |
        (static_cast<UINT64>(*it++) << 48) |
        (static_cast<UINT64>(*it++) << 56);
    frameChecksum =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    dir =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    frameLength =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    frameHandle =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    error =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameData.resize(frameLength);
    std::copy(it, it + frameData.size(), std::begin(frameData));
    it += frameLength;

    return it;
}

void EthernetErrorEx::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    structLength = calculateStructLength();
    frameLength = static_cast<WORD>(frameData.size());

    ObjectHeader::toData(data);

    data.push_back((structLength >>  0) & 0xff);
    data.push_back((structLength >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((hardwareChannel >>  0) & 0xff);
    data.push_back((hardwareChannel >>  8) & 0xff);
    data.push_back((frameDuration >>  0) & 0xff);
    data.push_back((frameDuration >>  8) & 0xff);
    data.push_back((frameDuration >> 16) & 0xff);
    data.push_back((frameDuration >> 24) & 0xff);
    data.push_back((frameDuration >> 32) & 0xff);
    data.push_back((frameDuration >> 40) & 0xff);
    data.push_back((frameDuration >> 48) & 0xff);
    data.push_back((frameDuration >> 56) & 0xff);
    data.push_back((frameChecksum >>  0) & 0xff);
    data.push_back((frameChecksum >>  8) & 0xff);
    data.push_back((frameChecksum >> 16) & 0xff);
    data.push_back((frameChecksum >> 24) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((dir >>  8) & 0xff);
    data.push_back((frameLength >>  0) & 0xff);
    data.push_back((frameLength >>  8) & 0xff);
    data.push_back((frameHandle >>  0) & 0xff);
    data.push_back((frameHandle >>  8) & 0xff);
    data.push_back((frameHandle >> 16) & 0xff);
    data.push_back((frameHandle >> 24) & 0xff);
    data.push_back((error >>  0) & 0xff);
    data.push_back((error >>  8) & 0xff);
    data.push_back((error >> 16) & 0xff);
    data.push_back((error >> 24) & 0xff);
    data.insert(std::end(data), std::begin(frameData), std::end(frameData));
}

DWORD EthernetErrorEx::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(structLength) +
        sizeof(flags) +
        sizeof(channel) +
        sizeof(hardwareChannel) +
        sizeof(frameDuration) +
        sizeof(frameChecksum) +
        sizeof(dir) +
        sizeof(frameLength) +
        sizeof(frameHandle) +
        sizeof(error) +
        frameLength;
}

WORD EthernetErrorEx::calculateStructLength() const {
    return
        sizeof(flags) +
        sizeof(channel) +
        sizeof(hardwareChannel) +
        sizeof(frameDuration) +
        sizeof(frameChecksum) +
        sizeof(dir) +
        sizeof(frameLength) +
        sizeof(frameHandle) +
        sizeof(error);
}

}
}
