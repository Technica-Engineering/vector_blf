/*
 * Copyright (C) 2013 Tobias Lorenz.
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

namespace Vector {
namespace BLF {

Unknown115::Unknown115() :
    ObjectHeader(ObjectType::Unknown115) {
}

void Unknown115::read(AbstractFile & is) {
    ObjectHeader::read(is);

    is.read(reinterpret_cast<char *>(&unknown0), sizeof(unknown0));
    is.read(reinterpret_cast<char *>(&unknown1), sizeof(unknown1));
    is.read(reinterpret_cast<char *>(&unknown2), sizeof(unknown2));

    uint8_t size = objectSize
            - ObjectHeader::calculateObjectSize()
            - sizeof(unknown0)
            - sizeof(unknown1)
            - sizeof(unknown2);

    while(size > 0) {
        UnknownDataBlock dataBlock;
        is.read(reinterpret_cast<char *>(&dataBlock.timeStamp), sizeof(dataBlock.timeStamp));
        is.read(reinterpret_cast<char *>(&dataBlock.uncompressedFileSize), sizeof(dataBlock.uncompressedFileSize));
        is.read(reinterpret_cast<char *>(&dataBlock.value), sizeof(dataBlock.value));
        is.read(reinterpret_cast<char *>(&dataBlock.flags), sizeof(dataBlock.flags));
        unknownData.push_back(dataBlock);
        size -=
            sizeof(dataBlock.timeStamp) +
            sizeof(dataBlock.uncompressedFileSize) +
            sizeof(dataBlock.value) +
            sizeof(dataBlock.flags);
    }
}

void Unknown115::write(AbstractFile & os) {
    ObjectHeader::write(os);

    os.write(reinterpret_cast<char *>(&unknown0), sizeof(unknown0));
    os.write(reinterpret_cast<char *>(&unknown1), sizeof(unknown1));
    os.write(reinterpret_cast<char *>(&unknown2), sizeof(unknown2));

    for (const UnknownDataBlock & dataBlock: unknownData) {
        os.write(reinterpret_cast<char *>(dataBlock.timeStamp), sizeof(dataBlock.timeStamp));
        os.write(reinterpret_cast<char *>(dataBlock.uncompressedFileSize), sizeof(dataBlock.uncompressedFileSize));
        os.write(reinterpret_cast<char *>(dataBlock.value), sizeof(dataBlock.value));
        os.write(reinterpret_cast<char *>(dataBlock.flags), sizeof(dataBlock.flags));
    }
}

DWORD Unknown115::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(unknown0) +
        sizeof(unknown1) +
        sizeof(unknown2) +
        unknownData.size() * (
                sizeof(UnknownDataBlock::timeStamp) +
                sizeof(UnknownDataBlock::uncompressedFileSize) +
                sizeof(UnknownDataBlock::value) +
                sizeof(UnknownDataBlock::flags));
}

}
}
