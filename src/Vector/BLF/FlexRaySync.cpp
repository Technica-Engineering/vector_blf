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

#include <Vector/BLF/FlexRaySync.h>

namespace Vector {
namespace BLF {

FlexRaySync::FlexRaySync() :
    ObjectHeader(ObjectType::FLEXRAY_SYNC) {
}

void FlexRaySync::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&mux), sizeof(mux));
    is.read(reinterpret_cast<char *>(&len), sizeof(len));
    is.read(reinterpret_cast<char *>(&messageId), sizeof(messageId));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&reservedFlexRaySync1), sizeof(reservedFlexRaySync1));
    is.read(reinterpret_cast<char *>(&reservedFlexRaySync2), sizeof(reservedFlexRaySync2));
    is.read(reinterpret_cast<char *>(dataBytes.data()), static_cast<std::streamsize>(dataBytes.size()));
    is.read(reinterpret_cast<char *>(&cycle), sizeof(cycle));
}

void FlexRaySync::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&mux), sizeof(mux));
    os.write(reinterpret_cast<char *>(&len), sizeof(len));
    os.write(reinterpret_cast<char *>(&messageId), sizeof(messageId));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&reservedFlexRaySync1), sizeof(reservedFlexRaySync1));
    os.write(reinterpret_cast<char *>(&reservedFlexRaySync2), sizeof(reservedFlexRaySync2));
    os.write(reinterpret_cast<char *>(dataBytes.data()), static_cast<std::streamsize>(dataBytes.size()));
    os.write(reinterpret_cast<char *>(&cycle), sizeof(cycle));
}

uint32_t FlexRaySync::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(mux) +
        sizeof(len) +
        sizeof(messageId) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(reservedFlexRaySync1) +
        sizeof(reservedFlexRaySync2) +
        static_cast<uint32_t>(dataBytes.size()) +
        sizeof(cycle);
}

}
}
