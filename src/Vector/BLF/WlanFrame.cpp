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

#include <Vector/BLF/WlanFrame.h>

namespace Vector {
namespace BLF {

WlanFrame::WlanFrame() :
    ObjectHeader(ObjectType::WLAN_FRAME) {
}

void WlanFrame::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&radioChannel), sizeof(radioChannel));
    is.read(reinterpret_cast<char *>(&signalStrength), sizeof(signalStrength));
    is.read(reinterpret_cast<char *>(&signalQuality), sizeof(signalQuality));
    is.read(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    is.read(reinterpret_cast<char *>(&reservedWlanFrame), sizeof(reservedWlanFrame));
    frameData.resize(frameLength);
    is.read(reinterpret_cast<char *>(frameData.data()), frameLength);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void WlanFrame::write(AbstractFile & os) {
    /* pre processing */
    frameLength = static_cast<WORD>(frameData.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&radioChannel), sizeof(radioChannel));
    os.write(reinterpret_cast<char *>(&signalStrength), sizeof(signalStrength));
    os.write(reinterpret_cast<char *>(&signalQuality), sizeof(signalQuality));
    os.write(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    os.write(reinterpret_cast<char *>(&reservedWlanFrame), sizeof(reservedWlanFrame));
    os.write(reinterpret_cast<char *>(frameData.data()), frameLength);

    /* skip padding */
    os.seekp(objectSize % 4, std::ios_base::cur);
}

DWORD WlanFrame::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(dir) +
        sizeof(radioChannel) +
        sizeof(signalStrength) +
        sizeof(signalQuality) +
        sizeof(frameLength) +
        sizeof(reservedWlanFrame) +
        frameLength;
}

}
}
