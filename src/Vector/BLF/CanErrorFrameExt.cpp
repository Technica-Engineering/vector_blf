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

#include <Vector/BLF/CanErrorFrameExt.h>

namespace Vector {
namespace BLF {

CanErrorFrameExt::CanErrorFrameExt() :
    ObjectHeader(ObjectType::CAN_ERROR_EXT) {
}

std::vector<uint8_t>::iterator CanErrorFrameExt::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    length =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    flags =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    ecc =
            (static_cast<BYTE>(*it++) <<  0);
    position =
            (static_cast<BYTE>(*it++) <<  0);
    dlc =
            (static_cast<BYTE>(*it++) <<  0);
    reservedCanErrorFrameExt1 =
            (static_cast<BYTE>(*it++) <<  0);
    frameLengthInNs =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    id =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    flagsExt =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedCanErrorFrameExt2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += this->data.size();

    return it;
}

void CanErrorFrameExt::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((length >>  0) & 0xff);
    data.push_back((length >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((flags >> 16) & 0xff);
    data.push_back((flags >> 24) & 0xff);
    data.push_back((ecc >>  0) & 0xff);
    data.push_back((position >>  0) & 0xff);
    data.push_back((dlc >>  0) & 0xff);
    data.push_back((reservedCanErrorFrameExt1 >>  0) & 0xff);
    data.push_back((frameLengthInNs >>  0) & 0xff);
    data.push_back((frameLengthInNs >>  8) & 0xff);
    data.push_back((frameLengthInNs >> 16) & 0xff);
    data.push_back((frameLengthInNs >> 24) & 0xff);
    data.push_back((id >>  0) & 0xff);
    data.push_back((id >>  8) & 0xff);
    data.push_back((id >> 16) & 0xff);
    data.push_back((id >> 24) & 0xff);
    data.push_back((flagsExt >>  0) & 0xff);
    data.push_back((flagsExt >>  8) & 0xff);
    data.push_back((reservedCanErrorFrameExt2 >>  0) & 0xff);
    data.push_back((reservedCanErrorFrameExt2 >>  8) & 0xff);
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
}

DWORD CanErrorFrameExt::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(length) +
        sizeof(flags) +
        sizeof(ecc) +
        sizeof(position) +
        sizeof(dlc) +
        sizeof(reservedCanErrorFrameExt1) +
        sizeof(frameLengthInNs) +
        sizeof(id) +
        sizeof(flagsExt) +
        sizeof(reservedCanErrorFrameExt2) +
        static_cast<DWORD>(data.size());
}

}
}
