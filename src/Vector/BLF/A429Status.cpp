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

#include <Vector/BLF/A429Status.h>

namespace Vector {
namespace BLF {

A429Status::A429Status() :
    ObjectHeader()
{
    objectType = ObjectType::A429_STATUS;
}

void A429Status::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&reservedA429Status1), sizeof(reservedA429Status1));
    is.read(reinterpret_cast<char *>(&parity), sizeof(parity));
    is.read(reinterpret_cast<char *>(&reservedA429Status2), sizeof(reservedA429Status2));
    is.read(reinterpret_cast<char *>(&minGap), sizeof(minGap));
    is.read(reinterpret_cast<char *>(&bitrate), sizeof(bitrate));
    is.read(reinterpret_cast<char *>(&minBitrate), sizeof(minBitrate));
    is.read(reinterpret_cast<char *>(&maxBitrate), sizeof(maxBitrate));
}

void A429Status::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&reservedA429Status1), sizeof(reservedA429Status1));
    os.write(reinterpret_cast<char *>(&parity), sizeof(parity));
    os.write(reinterpret_cast<char *>(&reservedA429Status2), sizeof(reservedA429Status2));
    os.write(reinterpret_cast<char *>(&minGap), sizeof(minGap));
    os.write(reinterpret_cast<char *>(&bitrate), sizeof(bitrate));
    os.write(reinterpret_cast<char *>(&minBitrate), sizeof(minBitrate));
    os.write(reinterpret_cast<char *>(&maxBitrate), sizeof(maxBitrate));
}

DWORD A429Status::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reservedA429Status1) +
        sizeof(parity) +
        sizeof(reservedA429Status2) +
        sizeof(minGap) +
        sizeof(bitrate) +
        sizeof(minBitrate) +
        sizeof(maxBitrate);
}

}
}
