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

#include <Vector/BLF/EthernetFrame.h>

namespace Vector {
namespace BLF {

EthernetFrame::EthernetFrame() :
    ObjectHeader(ObjectType::ETHERNET_FRAME) {
}

void EthernetFrame::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(sourceAddress.data()), static_cast<std::streamsize>(sourceAddress.size()));
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(destinationAddress.data()), static_cast<std::streamsize>(destinationAddress.size()));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&type), sizeof(type));
    is.read(reinterpret_cast<char *>(&tpid), sizeof(tpid));
    is.read(reinterpret_cast<char *>(&tci), sizeof(tci));
    is.read(reinterpret_cast<char *>(&payLoadLength), sizeof(payLoadLength));
    is.read(reinterpret_cast<char *>(&reservedEthernetFrame), sizeof(reservedEthernetFrame));
    payLoad.resize(payLoadLength);
    is.read(reinterpret_cast<char *>(payLoad.data()), payLoadLength);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void EthernetFrame::write(AbstractFile & os) {
    /* pre processing */
    payLoadLength = static_cast<uint16_t>(payLoad.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(sourceAddress.data()), static_cast<std::streamsize>(sourceAddress.size()));
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(destinationAddress.data()), static_cast<std::streamsize>(destinationAddress.size()));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&type), sizeof(type));
    os.write(reinterpret_cast<char *>(&tpid), sizeof(tpid));
    os.write(reinterpret_cast<char *>(&tci), sizeof(tci));
    os.write(reinterpret_cast<char *>(&payLoadLength), sizeof(payLoadLength));
    os.write(reinterpret_cast<char *>(&reservedEthernetFrame), sizeof(reservedEthernetFrame));
    os.write(reinterpret_cast<char *>(payLoad.data()), payLoadLength);

    /* skip padding */
    os.skipp(objectSize % 4);
}

uint32_t EthernetFrame::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        static_cast<uint32_t>(sourceAddress.size()) +
        sizeof(channel) +
        static_cast<uint32_t>(destinationAddress.size()) +
        sizeof(dir) +
        sizeof(type) +
        sizeof(tpid) +
        sizeof(tci) +
        sizeof(payLoadLength) +
        sizeof(reservedEthernetFrame) +
        payLoadLength;
}

}
}
