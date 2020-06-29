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

#include <Vector/BLF/CanFdErrorFrame64.h>

namespace Vector {
namespace BLF {

CanFdErrorFrame64::CanFdErrorFrame64() :
    ObjectHeader(ObjectType::CAN_FD_ERROR_64) {
}

std::vector<uint8_t>::iterator CanFdErrorFrame64::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
            (static_cast<BYTE>(*it++) <<  0);
    dlc =
            (static_cast<BYTE>(*it++) <<  0);
    validDataBytes =
            (static_cast<BYTE>(*it++) <<  0);
    ecc =
            (static_cast<BYTE>(*it++) <<  0);
    flags =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    errorCodeExt =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    extFlags =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    extDataOffset =
            (static_cast<BYTE>(*it++) <<  0);
    reservedCanFdErrorFrame1 =
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
    crc =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    errorPosition =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedCanFdErrorFrame2 =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    this->data.resize(validDataBytes);
    std::copy(it, it + this->data.size(), std::begin(this->data));
    it += this->data.size();
    if (hasExtData()) {
        it = CanFdExtFrameData::fromData(it);
    }
    // @note reservedCanFdExtFrameData is read here as CanFdExtFrameData doesn't know the objectSize
    reservedCanFdExtFrameData.resize(objectSize - calculateObjectSize());
    std::copy(it, it + reservedCanFdExtFrameData.size(), std::begin(reservedCanFdExtFrameData));
    it += reservedCanFdExtFrameData.size();

    return it;
}

void CanFdErrorFrame64::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    validDataBytes = static_cast<WORD>(data.size());

    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((dlc >>  0) & 0xff);
    data.push_back((validDataBytes >>  0) & 0xff);
    data.push_back((ecc >>  0) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((errorCodeExt >>  0) & 0xff);
    data.push_back((errorCodeExt >>  8) & 0xff);
    data.push_back((extFlags >>  0) & 0xff);
    data.push_back((extFlags >>  8) & 0xff);
    data.push_back((extDataOffset >>  0) & 0xff);
    data.push_back((reservedCanFdErrorFrame1 >>  0) & 0xff);
    data.push_back((id >>  0) & 0xff);
    data.push_back((id >>  8) & 0xff);
    data.push_back((id >> 16) & 0xff);
    data.push_back((id >> 24) & 0xff);
    data.push_back((frameLength >>  0) & 0xff);
    data.push_back((frameLength >>  8) & 0xff);
    data.push_back((frameLength >> 16) & 0xff);
    data.push_back((frameLength >> 24) & 0xff);
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
    data.push_back((crc >>  0) & 0xff);
    data.push_back((crc >>  8) & 0xff);
    data.push_back((crc >> 16) & 0xff);
    data.push_back((crc >> 24) & 0xff);
    data.push_back((errorPosition >>  0) & 0xff);
    data.push_back((errorPosition >>  8) & 0xff);
    data.push_back((reservedCanFdErrorFrame2 >>  0) & 0xff);
    data.push_back((reservedCanFdErrorFrame2 >>  8) & 0xff);
    data.insert(std::end(data), std::begin(this->data), std::end(this->data));
    if (hasExtData()) {
        CanFdExtFrameData::toData(data);
    }
}

bool CanFdErrorFrame64::hasExtData() const {
    return
        (extDataOffset != 0) &&
        (objectSize >= extDataOffset + CanFdExtFrameData::calculateObjectSize());
}

DWORD CanFdErrorFrame64::calculateObjectSize() const {
    DWORD size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dlc) +
        sizeof(validDataBytes) +
        sizeof(ecc) +
        sizeof(flags) +
        sizeof(errorCodeExt) +
        sizeof(extFlags) +
        sizeof(extDataOffset) +
        sizeof(reservedCanFdErrorFrame1) +
        sizeof(id) +
        sizeof(frameLength) +
        sizeof(btrCfgArb) +
        sizeof(btrCfgData) +
        sizeof(timeOffsetBrsNs) +
        sizeof(timeOffsetCrcDelNs) +
        sizeof(crc) +
        sizeof(errorPosition) +
        sizeof(reservedCanFdErrorFrame2) +
        static_cast<DWORD>(data.size());
    if (hasExtData())
        size += CanFdExtFrameData::calculateObjectSize();
    return size;
}

}
}
