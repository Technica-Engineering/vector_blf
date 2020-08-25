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

#include <Vector/BLF/MostDataLost.h>

namespace Vector {
namespace BLF {

MostDataLost::MostDataLost() :
    ObjectHeader2(ObjectType::MOST_DATALOST) {
}

void MostDataLost::read(AbstractFile & is) {
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&reservedMostDataLost), sizeof(reservedMostDataLost));
    is.read(reinterpret_cast<char *>(&info), sizeof(info));
    is.read(reinterpret_cast<char *>(&lostMsgsCtrl), sizeof(lostMsgsCtrl));
    is.read(reinterpret_cast<char *>(&lostMsgsAsync), sizeof(lostMsgsAsync));
    is.read(reinterpret_cast<char *>(&lastGoodTimeStampNs), sizeof(lastGoodTimeStampNs));
    is.read(reinterpret_cast<char *>(&nextGoodTimeStampNs), sizeof(nextGoodTimeStampNs));
}

void MostDataLost::write(AbstractFile & os) {
    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&reservedMostDataLost), sizeof(reservedMostDataLost));
    os.write(reinterpret_cast<char *>(&info), sizeof(info));
    os.write(reinterpret_cast<char *>(&lostMsgsCtrl), sizeof(lostMsgsCtrl));
    os.write(reinterpret_cast<char *>(&lostMsgsAsync), sizeof(lostMsgsAsync));
    os.write(reinterpret_cast<char *>(&lastGoodTimeStampNs), sizeof(lastGoodTimeStampNs));
    os.write(reinterpret_cast<char *>(&nextGoodTimeStampNs), sizeof(nextGoodTimeStampNs));
}

uint32_t MostDataLost::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedMostDataLost) +
        sizeof(info) +
        sizeof(lostMsgsCtrl) +
        sizeof(lostMsgsAsync) +
        sizeof(lastGoodTimeStampNs) +
        sizeof(nextGoodTimeStampNs);
}

}
}
