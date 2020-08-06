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

#include <Vector/BLF/CanFdMessage64.h>

namespace Vector {
namespace BLF {

CanFdMessage64::CanFdMessage64() :
    ObjectHeader(ObjectType::CAN_FD_MESSAGE_64) {
}

std::vector<uint8_t>::iterator CanFdMessage64::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<BYTE>(*it++) <<  0);
    dlc =
        (static_cast<BYTE>(*it++) <<  0);
    validDataBytes =
        (static_cast<BYTE>(*it++) <<  0);
    txCount =
        (static_cast<BYTE>(*it++) <<  0);
    id =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    frameLength =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    flags =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    btrCfgArb =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    btrCfgData =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    timeOffsetBrsNs =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    timeOffsetCrcDelNs =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    bitCount =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    dir =
        (static_cast<BYTE>(*it++) <<  0);
    extDataOffset =
        (static_cast<BYTE>(*it++) <<  0);
    crc =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    this->data.resize(validDataBytes);
    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += validDataBytes;
    if (hasExtData()) {
        it = CanFdExtFrameData::fromData(it);
    }
    // @note reservedCanFdExtFrameData is read here as CanFdExtFrameData doesn't know the objectSize
    reservedCanFdExtFrameData.resize(objectSize - calculateObjectSize());
    std::copy(it, it + reservedCanFdExtFrameData.size(), std::begin(reservedCanFdExtFrameData));
    it += objectSize - calculateObjectSize();

    return it;
}

void CanFdMessage64::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    validDataBytes = static_cast<WORD>(this->data.size());

    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((dlc >>  0) & 0xff);
    data.push_back((validDataBytes >>  0) & 0xff);
    data.push_back((txCount >>  0) & 0xff);
    data.push_back((id >>  0) & 0xff);
    data.push_back((id >>  8) & 0xff);
    data.push_back((id >> 16) & 0xff);
    data.push_back((id >> 24) & 0xff);
    data.push_back((frameLength >>  0) & 0xff);
    data.push_back((frameLength >>  8) & 0xff);
    data.push_back((frameLength >> 16) & 0xff);
    data.push_back((frameLength >> 24) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((flags >> 16) & 0xff);
    data.push_back((flags >> 24) & 0xff);
    data.push_back((btrCfgArb >>  0) & 0xff);
    data.push_back((btrCfgArb >>  8) & 0xff);
    data.push_back((btrCfgArb >> 16) & 0xff);
    data.push_back((btrCfgArb >> 24) & 0xff);
    data.push_back((btrCfgData >>  0) & 0xff);
    data.push_back((btrCfgData >>  8) & 0xff);
    data.push_back((btrCfgData >> 16) & 0xff);
    data.push_back((btrCfgData >> 24) & 0xff);
    data.push_back((timeOffsetBrsNs >>  0) & 0xff);
    data.push_back((timeOffsetBrsNs >>  8) & 0xff);
    data.push_back((timeOffsetBrsNs >> 16) & 0xff);
    data.push_back((timeOffsetBrsNs >> 24) & 0xff);
    data.push_back((timeOffsetCrcDelNs >>  0) & 0xff);
    data.push_back((timeOffsetCrcDelNs >>  8) & 0xff);
    data.push_back((timeOffsetCrcDelNs >> 16) & 0xff);
    data.push_back((timeOffsetCrcDelNs >> 24) & 0xff);
    data.push_back((bitCount >>  0) & 0xff);
    data.push_back((bitCount >>  8) & 0xff);
    data.push_back((dir >>  0) & 0xff);
    data.push_back((extDataOffset >>  0) & 0xff);
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((crc >> 16) & 0xff);
    data.push_back((crc >> 24) & 0xff);
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
    if (hasExtData()) {
        CanFdExtFrameData::toData(data);
    }
}

bool CanFdMessage64::hasExtData() const {
    return
        (extDataOffset != 0) &&
        (objectSize >= extDataOffset + CanFdExtFrameData::calculateObjectSize());
}

DWORD CanFdMessage64::calculateObjectSize() const {
    DWORD size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dlc) +
        sizeof(validDataBytes) +
        sizeof(txCount) +
        sizeof(id) +
        sizeof(frameLength) +
        sizeof(flags) +
        sizeof(btrCfgArb) +
        sizeof(btrCfgData) +
        sizeof(timeOffsetBrsNs) +
        sizeof(timeOffsetCrcDelNs) +
        sizeof(bitCount) +
        sizeof(dir) +
        sizeof(extDataOffset) +
        sizeof(crc) +
        static_cast<DWORD>(data.size());
    if (hasExtData())
        size += CanFdExtFrameData::calculateObjectSize();
    return size;
}

}
}
