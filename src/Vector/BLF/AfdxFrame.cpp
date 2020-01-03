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

#include <Vector/BLF/AfdxFrame.h>

namespace Vector {
namespace BLF {

AfdxFrame::AfdxFrame() :
    ObjectHeader() {
    objectType = ObjectType::AFDX_FRAME;
}

void AfdxFrame::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(sourceAddress.data()), static_cast<std::streamsize>(sourceAddress.size()));
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(destinationAddress.data()), static_cast<std::streamsize>(destinationAddress.size()));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&type), sizeof(type));
    is.read(reinterpret_cast<char *>(&tpid), sizeof(tpid));
    is.read(reinterpret_cast<char *>(&tci), sizeof(tci));
    is.read(reinterpret_cast<char *>(&ethChannel), sizeof(ethChannel));
    is.read(reinterpret_cast<char *>(&reservedAfdxFrame1), sizeof(reservedAfdxFrame1));
    is.read(reinterpret_cast<char *>(&afdxFlags), sizeof(afdxFlags));
    is.read(reinterpret_cast<char *>(&reservedAfdxFrame2), sizeof(reservedAfdxFrame2));
    is.read(reinterpret_cast<char *>(&bagUsec), sizeof(bagUsec));
    is.read(reinterpret_cast<char *>(&payLoadLength), sizeof(payLoadLength));
    is.read(reinterpret_cast<char *>(&reservedAfdxFrame3), sizeof(reservedAfdxFrame3));
    is.read(reinterpret_cast<char *>(&reservedAfdxFrame4), sizeof(reservedAfdxFrame4));
    payLoad.resize(payLoadLength);
    is.read(reinterpret_cast<char *>(payLoad.data()), payLoadLength);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void AfdxFrame::write(AbstractFile & os) {
    /* pre processing */
    payLoadLength = static_cast<WORD>(payLoad.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(sourceAddress.data()), static_cast<std::streamsize>(sourceAddress.size()));
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(destinationAddress.data()), static_cast<std::streamsize>(destinationAddress.size()));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&type), sizeof(type));
    os.write(reinterpret_cast<char *>(&tpid), sizeof(tpid));
    os.write(reinterpret_cast<char *>(&tci), sizeof(tci));
    os.write(reinterpret_cast<char *>(&ethChannel), sizeof(ethChannel));
    os.write(reinterpret_cast<char *>(&reservedAfdxFrame1), sizeof(reservedAfdxFrame1));
    os.write(reinterpret_cast<char *>(&afdxFlags), sizeof(afdxFlags));
    os.write(reinterpret_cast<char *>(&reservedAfdxFrame2), sizeof(reservedAfdxFrame2));
    os.write(reinterpret_cast<char *>(&bagUsec), sizeof(bagUsec));
    os.write(reinterpret_cast<char *>(&payLoadLength), sizeof(payLoadLength));
    os.write(reinterpret_cast<char *>(&reservedAfdxFrame3), sizeof(reservedAfdxFrame3));
    os.write(reinterpret_cast<char *>(&reservedAfdxFrame4), sizeof(reservedAfdxFrame4));
    os.write(reinterpret_cast<char *>(payLoad.data()), payLoadLength);

    /* skip padding */
    os.skipp(objectSize % 4);
}

DWORD AfdxFrame::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        static_cast<DWORD>(sourceAddress.size()) +
        sizeof(channel) +
        static_cast<DWORD>(destinationAddress.size()) +
        sizeof(dir) +
        sizeof(type) +
        sizeof(tpid) +
        sizeof(tci) +
        sizeof(ethChannel) +
        sizeof(reservedAfdxFrame1) +
        sizeof(afdxFlags) +
        sizeof(reservedAfdxFrame2) +
        sizeof(bagUsec) +
        sizeof(payLoadLength) +
        sizeof(reservedAfdxFrame3) +
        sizeof(reservedAfdxFrame4) +
        payLoadLength;
}

}
}
