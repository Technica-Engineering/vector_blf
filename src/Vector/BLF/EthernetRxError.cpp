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

#include <Vector/BLF/EthernetRxError.h>

namespace Vector {
namespace BLF {

EthernetRxError::EthernetRxError() :
    ObjectHeader(ObjectType::ETHERNET_RX_ERROR) {
}

void EthernetRxError::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&structLength), sizeof(structLength));
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&hardwareChannel), sizeof(hardwareChannel));
    is.read(reinterpret_cast<char *>(&fcs), sizeof(fcs));
    is.read(reinterpret_cast<char *>(&frameDataLength), sizeof(frameDataLength));
    is.read(reinterpret_cast<char *>(&reservedEthernetRxError), sizeof(reservedEthernetRxError));
    is.read(reinterpret_cast<char *>(&error), sizeof(error));
    frameData.resize(frameDataLength);
    is.read(reinterpret_cast<char *>(frameData.data()), frameDataLength);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void EthernetRxError::write(AbstractFile & os) {
    /* pre processing */
    structLength = calculateStructLength();
    frameDataLength = static_cast<WORD>(frameData.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&structLength), sizeof(structLength));
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&hardwareChannel), sizeof(hardwareChannel));
    os.write(reinterpret_cast<char *>(&fcs), sizeof(fcs));
    os.write(reinterpret_cast<char *>(&frameDataLength), sizeof(frameDataLength));
    os.write(reinterpret_cast<char *>(&reservedEthernetRxError), sizeof(reservedEthernetRxError));
    os.write(reinterpret_cast<char *>(&error), sizeof(error));
    os.write(reinterpret_cast<char *>(frameData.data()), frameDataLength);

    /* skip padding */
    os.seekp(objectSize % 4, std::ios_base::cur);
}

DWORD EthernetRxError::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(structLength) +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(hardwareChannel) +
        sizeof(fcs) +
        sizeof(frameDataLength) +
        sizeof(reservedEthernetRxError) +
        sizeof(error) +
        frameDataLength;
}

WORD EthernetRxError::calculateStructLength() const {
    return
        sizeof(structLength) +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(hardwareChannel) +
        sizeof(fcs) +
        sizeof(frameDataLength) +
        sizeof(reservedEthernetRxError) +
        sizeof(error);
}

}
}
