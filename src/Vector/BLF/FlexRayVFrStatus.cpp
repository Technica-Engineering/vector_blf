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

#include <Vector/BLF/FlexRayVFrStatus.h>

namespace Vector {
namespace BLF {

FlexRayVFrStatus::FlexRayVFrStatus() :
    ObjectHeader()
{
    objectType = ObjectType::FR_STATUS;
}

void FlexRayVFrStatus::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&version), sizeof(version));
    is.read(reinterpret_cast<char *>(&channelMask), sizeof(channelMask));
    is.read(reinterpret_cast<char *>(&cycle), sizeof(cycle));
    is.read(reinterpret_cast<char *>(&reservedFlexRayVFrStatus1), sizeof(reservedFlexRayVFrStatus1));
    is.read(reinterpret_cast<char *>(&clientIndexFlexRayVFrStatus), sizeof(clientIndexFlexRayVFrStatus));
    is.read(reinterpret_cast<char *>(&clusterNo), sizeof(clusterNo));
    is.read(reinterpret_cast<char *>(&wus), sizeof(wus));
    is.read(reinterpret_cast<char *>(&ccSyncState), sizeof(ccSyncState));
    is.read(reinterpret_cast<char *>(&tag), sizeof(tag));
    is.read(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size() * sizeof(DWORD)));
    is.read(reinterpret_cast<char *>(reservedFlexRayVFrStatus2.data()), static_cast<std::streamsize>(reservedFlexRayVFrStatus2.size() * sizeof(WORD)));
}

void FlexRayVFrStatus::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&version), sizeof(version));
    os.write(reinterpret_cast<char *>(&channelMask), sizeof(channelMask));
    os.write(reinterpret_cast<char *>(&cycle), sizeof(cycle));
    os.write(reinterpret_cast<char *>(&reservedFlexRayVFrStatus1), sizeof(reservedFlexRayVFrStatus1));
    os.write(reinterpret_cast<char *>(&clientIndexFlexRayVFrStatus), sizeof(clientIndexFlexRayVFrStatus));
    os.write(reinterpret_cast<char *>(&clusterNo), sizeof(clusterNo));
    os.write(reinterpret_cast<char *>(&wus), sizeof(wus));
    os.write(reinterpret_cast<char *>(&ccSyncState), sizeof(ccSyncState));
    os.write(reinterpret_cast<char *>(&tag), sizeof(tag));
    os.write(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size() * sizeof(DWORD)));
    os.write(reinterpret_cast<char *>(reservedFlexRayVFrStatus2.data()), static_cast<std::streamsize>(reservedFlexRayVFrStatus2.size() * sizeof(WORD)));
}

DWORD FlexRayVFrStatus::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(cycle) +
        sizeof(reservedFlexRayVFrStatus1) +
        sizeof(clientIndexFlexRayVFrStatus) +
        sizeof(clusterNo) +
        sizeof(wus) +
        sizeof(ccSyncState) +
        sizeof(tag) +
        static_cast<DWORD>(data.size() * sizeof(DWORD)) +
        static_cast<DWORD>(reservedFlexRayVFrStatus2.size() * sizeof(WORD));
}

}
}
