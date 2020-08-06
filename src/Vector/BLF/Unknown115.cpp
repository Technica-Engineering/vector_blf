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

#include <Vector/BLF/Unknown115.h>

#include <algorithm>

namespace Vector {
namespace BLF {

DWORD Unknown115::UnknownDataBlock::calculateObjectSize() {
    return
        sizeof(UnknownDataBlock::timeStamp) +
        sizeof(UnknownDataBlock::uncompressedFileSize) +
        sizeof(UnknownDataBlock::value) +
        sizeof(UnknownDataBlock::flags);
}

Unknown115::Unknown115() :
    ObjectHeader(ObjectType::Unknown115) {
}

std::vector<uint8_t>::iterator Unknown115::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    unknown0 =
        (static_cast<uint64_t>(*it++) <<  0) |
        (static_cast<uint64_t>(*it++) <<  8) |
        (static_cast<uint64_t>(*it++) << 16) |
        (static_cast<uint64_t>(*it++) << 24) |
        (static_cast<uint64_t>(*it++) << 32) |
        (static_cast<uint64_t>(*it++) << 40) |
        (static_cast<uint64_t>(*it++) << 48) |
        (static_cast<uint64_t>(*it++) << 56);
    unknown1 =
        (static_cast<uint64_t>(*it++) <<  0) |
        (static_cast<uint64_t>(*it++) <<  8) |
        (static_cast<uint64_t>(*it++) << 16) |
        (static_cast<uint64_t>(*it++) << 24) |
        (static_cast<uint64_t>(*it++) << 32) |
        (static_cast<uint64_t>(*it++) << 40) |
        (static_cast<uint64_t>(*it++) << 48) |
        (static_cast<uint64_t>(*it++) << 56);
    unknown2 =
        (static_cast<uint64_t>(*it++) <<  0) |
        (static_cast<uint64_t>(*it++) <<  8) |
        (static_cast<uint64_t>(*it++) << 16) |
        (static_cast<uint64_t>(*it++) << 24) |
        (static_cast<uint64_t>(*it++) << 32) |
        (static_cast<uint64_t>(*it++) << 40) |
        (static_cast<uint64_t>(*it++) << 48) |
        (static_cast<uint64_t>(*it++) << 56);
    DWORD size = objectSize
                 - ObjectHeader::calculateObjectSize()
                 - sizeof(unknown0)
                 - sizeof(unknown1)
                 - sizeof(unknown2);
    while(size >= UnknownDataBlock::calculateObjectSize()) {
        UnknownDataBlock dataBlock;
        dataBlock.timeStamp =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
        dataBlock.uncompressedFileSize =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24) |
            (static_cast<uint64_t>(*it++) << 32) |
            (static_cast<uint64_t>(*it++) << 40) |
            (static_cast<uint64_t>(*it++) << 48) |
            (static_cast<uint64_t>(*it++) << 56);
        dataBlock.value =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24);
        dataBlock.flags =
            (static_cast<uint64_t>(*it++) <<  0) |
            (static_cast<uint64_t>(*it++) <<  8) |
            (static_cast<uint64_t>(*it++) << 16) |
            (static_cast<uint64_t>(*it++) << 24);
        unknownData.push_back(dataBlock);
        size -= UnknownDataBlock::calculateObjectSize();
    }
    reservedUnknown115.resize(size);
    std::copy(it, it + reservedUnknown115.size(), std::begin(reservedUnknown115));
    it += size;

    return it;
}

void Unknown115::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((unknown0 >>  0) & 0xff);
    data.push_back((unknown0 >>  8) & 0xff);
    data.push_back((unknown0 >> 16) & 0xff);
    data.push_back((unknown0 >> 24) & 0xff);
    data.push_back((unknown0 >> 32) & 0xff);
    data.push_back((unknown0 >> 40) & 0xff);
    data.push_back((unknown0 >> 48) & 0xff);
    data.push_back((unknown0 >> 56) & 0xff);
    data.push_back((unknown1 >>  0) & 0xff);
    data.push_back((unknown1 >>  8) & 0xff);
    data.push_back((unknown1 >> 16) & 0xff);
    data.push_back((unknown1 >> 24) & 0xff);
    data.push_back((unknown1 >> 32) & 0xff);
    data.push_back((unknown1 >> 40) & 0xff);
    data.push_back((unknown1 >> 48) & 0xff);
    data.push_back((unknown1 >> 56) & 0xff);
    data.push_back((unknown2 >>  0) & 0xff);
    data.push_back((unknown2 >>  8) & 0xff);
    data.push_back((unknown2 >> 16) & 0xff);
    data.push_back((unknown2 >> 24) & 0xff);
    data.push_back((unknown2 >> 32) & 0xff);
    data.push_back((unknown2 >> 40) & 0xff);
    data.push_back((unknown2 >> 48) & 0xff);
    data.push_back((unknown2 >> 56) & 0xff);
    std::for_each(unknownData.begin(), unknownData.end(), [&data](const UnknownDataBlock & d) {
        data.push_back((d.timeStamp >>  0) & 0xff);
        data.push_back((d.timeStamp >>  8) & 0xff);
        data.push_back((d.timeStamp >> 16) & 0xff);
        data.push_back((d.timeStamp >> 24) & 0xff);
        data.push_back((d.timeStamp >> 32) & 0xff);
        data.push_back((d.timeStamp >> 40) & 0xff);
        data.push_back((d.timeStamp >> 48) & 0xff);
        data.push_back((d.timeStamp >> 56) & 0xff);
        data.push_back((d.uncompressedFileSize >>  0) & 0xff);
        data.push_back((d.uncompressedFileSize >>  8) & 0xff);
        data.push_back((d.uncompressedFileSize >> 16) & 0xff);
        data.push_back((d.uncompressedFileSize >> 24) & 0xff);
        data.push_back((d.uncompressedFileSize >> 32) & 0xff);
        data.push_back((d.uncompressedFileSize >> 40) & 0xff);
        data.push_back((d.uncompressedFileSize >> 48) & 0xff);
        data.push_back((d.uncompressedFileSize >> 56) & 0xff);
        data.push_back((d.value >>  0) & 0xff);
        data.push_back((d.value >>  8) & 0xff);
        data.push_back((d.value >> 16) & 0xff);
        data.push_back((d.value >> 24) & 0xff);
        data.push_back((d.flags >>  0) & 0xff);
        data.push_back((d.flags >>  8) & 0xff);
        data.push_back((d.flags >> 16) & 0xff);
        data.push_back((d.flags >> 24) & 0xff);
    });
    data.insert(std::end(data), std::begin(reservedUnknown115), std::end(reservedUnknown115));
}

DWORD Unknown115::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(unknown0) +
        sizeof(unknown1) +
        sizeof(unknown2) +
        unknownData.size() * UnknownDataBlock::calculateObjectSize() +
        static_cast<DWORD>(reservedUnknown115.size());
}

}
}
