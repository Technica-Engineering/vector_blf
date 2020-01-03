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

#include <Vector/BLF/WlanStatistic.h>

namespace Vector {
namespace BLF {

WlanStatistic::WlanStatistic() :
    ObjectHeader() {
    objectType = ObjectType::WLAN_STATISTIC;
}

void WlanStatistic::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&rxPacketCount), sizeof(rxPacketCount));
    is.read(reinterpret_cast<char *>(&rxByteCount), sizeof(rxByteCount));
    is.read(reinterpret_cast<char *>(&txPacketCount), sizeof(txPacketCount));
    is.read(reinterpret_cast<char *>(&txByteCount), sizeof(txByteCount));
    is.read(reinterpret_cast<char *>(&collisionCount), sizeof(collisionCount));
    is.read(reinterpret_cast<char *>(&errorCount), sizeof(errorCount));
    is.read(reinterpret_cast<char *>(&reservedWlanStatistic), sizeof(reservedWlanStatistic));
    // @note might be extended in future versions
}

void WlanStatistic::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&rxPacketCount), sizeof(rxPacketCount));
    os.write(reinterpret_cast<char *>(&rxByteCount), sizeof(rxByteCount));
    os.write(reinterpret_cast<char *>(&txPacketCount), sizeof(txPacketCount));
    os.write(reinterpret_cast<char *>(&txByteCount), sizeof(txByteCount));
    os.write(reinterpret_cast<char *>(&collisionCount), sizeof(collisionCount));
    os.write(reinterpret_cast<char *>(&errorCount), sizeof(errorCount));
    os.write(reinterpret_cast<char *>(&reservedWlanStatistic), sizeof(reservedWlanStatistic));
}

DWORD WlanStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(rxPacketCount) +
        sizeof(rxByteCount) +
        sizeof(txPacketCount) +
        sizeof(txByteCount) +
        sizeof(collisionCount) +
        sizeof(errorCount) +
        sizeof(reservedWlanStatistic);
}

}
}
