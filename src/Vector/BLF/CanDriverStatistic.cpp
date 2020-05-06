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

#include <Vector/BLF/CanDriverStatistic.h>

namespace Vector {
namespace BLF {

CanDriverStatistic::CanDriverStatistic() :
    ObjectHeader(ObjectType::CAN_STATISTIC) {
}

void CanDriverStatistic::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&busLoad), sizeof(busLoad));
    is.read(reinterpret_cast<char *>(&standardDataFrames), sizeof(standardDataFrames));
    is.read(reinterpret_cast<char *>(&extendedDataFrames), sizeof(extendedDataFrames));
    is.read(reinterpret_cast<char *>(&standardRemoteFrames), sizeof(standardRemoteFrames));
    is.read(reinterpret_cast<char *>(&extendedRemoteFrames), sizeof(extendedRemoteFrames));
    is.read(reinterpret_cast<char *>(&errorFrames), sizeof(errorFrames));
    is.read(reinterpret_cast<char *>(&overloadFrames), sizeof(overloadFrames));
    is.read(reinterpret_cast<char *>(&reservedCanDriverStatistic), sizeof(reservedCanDriverStatistic));
}

void CanDriverStatistic::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&busLoad), sizeof(busLoad));
    os.write(reinterpret_cast<char *>(&standardDataFrames), sizeof(standardDataFrames));
    os.write(reinterpret_cast<char *>(&extendedDataFrames), sizeof(extendedDataFrames));
    os.write(reinterpret_cast<char *>(&standardRemoteFrames), sizeof(standardRemoteFrames));
    os.write(reinterpret_cast<char *>(&extendedRemoteFrames), sizeof(extendedRemoteFrames));
    os.write(reinterpret_cast<char *>(&errorFrames), sizeof(errorFrames));
    os.write(reinterpret_cast<char *>(&overloadFrames), sizeof(overloadFrames));
    os.write(reinterpret_cast<char *>(&reservedCanDriverStatistic), sizeof(reservedCanDriverStatistic));
}

DWORD CanDriverStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(busLoad) +
        sizeof(standardDataFrames) +
        sizeof(extendedDataFrames) +
        sizeof(standardRemoteFrames) +
        sizeof(extendedRemoteFrames) +
        sizeof(errorFrames) +
        sizeof(overloadFrames) +
        sizeof(reservedCanDriverStatistic);
}

}
}
