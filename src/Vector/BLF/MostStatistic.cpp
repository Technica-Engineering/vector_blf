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

#include <Vector/BLF/MostStatistic.h>

namespace Vector {
namespace BLF {

MostStatistic::MostStatistic() :
    ObjectHeader(ObjectType::MOST_STATISTIC) {
}

void MostStatistic::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&pktCnt), sizeof(pktCnt));
    is.read(reinterpret_cast<char *>(&frmCnt), sizeof(frmCnt));
    is.read(reinterpret_cast<char *>(&lightCnt), sizeof(lightCnt));
    is.read(reinterpret_cast<char *>(&bufferLevel), sizeof(bufferLevel));
}

void MostStatistic::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&pktCnt), sizeof(pktCnt));
    os.write(reinterpret_cast<char *>(&frmCnt), sizeof(frmCnt));
    os.write(reinterpret_cast<char *>(&lightCnt), sizeof(lightCnt));
    os.write(reinterpret_cast<char *>(&bufferLevel), sizeof(bufferLevel));
}

DWORD MostStatistic::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(pktCnt) +
        sizeof(frmCnt) +
        sizeof(lightCnt) +
        sizeof(bufferLevel);
}

}
}
