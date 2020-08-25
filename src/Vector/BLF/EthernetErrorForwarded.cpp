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

#include <Vector/BLF/EthernetErrorForwarded.h>

namespace Vector {
namespace BLF {

EthernetErrorForwarded::EthernetErrorForwarded() :
    ObjectHeader(ObjectType::ETHERNET_ERROR_FORWARDED) {
}

void EthernetErrorForwarded::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&structLength), sizeof(structLength));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&hardwareChannel), sizeof(hardwareChannel));
    is.read(reinterpret_cast<char *>(&frameDuration), sizeof(frameDuration));
    is.read(reinterpret_cast<char *>(&frameChecksum), sizeof(frameChecksum));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    is.read(reinterpret_cast<char *>(&frameHandle), sizeof(frameHandle));
    is.read(reinterpret_cast<char *>(&error), sizeof(error));
    frameData.resize(frameLength);
    is.read(reinterpret_cast<char *>(frameData.data()), frameLength);
}

void EthernetErrorForwarded::write(AbstractFile & os) {
    /* pre processing */
    structLength = calculateStructLength();
    frameLength = static_cast<uint16_t>(frameData.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&structLength), sizeof(structLength));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&hardwareChannel), sizeof(hardwareChannel));
    os.write(reinterpret_cast<char *>(&frameDuration), sizeof(frameDuration));
    os.write(reinterpret_cast<char *>(&frameChecksum), sizeof(frameChecksum));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    os.write(reinterpret_cast<char *>(&frameHandle), sizeof(frameHandle));
    os.write(reinterpret_cast<char *>(&error), sizeof(error));
    os.write(reinterpret_cast<char *>(frameData.data()), frameLength);
}

uint32_t EthernetErrorForwarded::calculateObjectSize() const {
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

uint16_t EthernetErrorForwarded::calculateStructLength() const {
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
