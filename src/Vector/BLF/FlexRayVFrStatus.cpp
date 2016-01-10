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

#include "FlexRayVFrStatus.h"

namespace Vector {
namespace BLF {

FlexRayVFrStatus::FlexRayVFrStatus() :
    ObjectHeader(),
    channel(),
    version(),
    channelMask(),
    cycle(),
    reserved1(),
    clientIndex(),
    clusterNo(),
    wus(),
    ccSyncState(),
    tag(),
    data(),
    reserved2()
{
    objectType = ObjectType::FR_STATUS;
}

void FlexRayVFrStatus::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &version, sizeof(version));
    is.read((char *) &channelMask, sizeof(channelMask));
    is.read((char *) &cycle, sizeof(cycle));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &clientIndex, sizeof(clientIndex));
    is.read((char *) &clusterNo, sizeof(clusterNo));
    is.read((char *) &wus, sizeof(wus));
    is.read((char *) &ccSyncState, sizeof(ccSyncState));
    is.read((char *) &tag, sizeof(tag));
    is.read((char *) data.data(), data.size());
    is.read((char *) reserved2.data(), reserved2.size());
}

void FlexRayVFrStatus::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &version, sizeof(version));
    os.write((char *) &channelMask, sizeof(channelMask));
    os.write((char *) &cycle, sizeof(cycle));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &clientIndex, sizeof(clientIndex));
    os.write((char *) &clusterNo, sizeof(clusterNo));
    os.write((char *) &wus, sizeof(wus));
    os.write((char *) &ccSyncState, sizeof(ccSyncState));
    os.write((char *) &tag, sizeof(tag));
    os.write((char *) data.data(), data.size());
    os.write((char *) reserved2.data(), reserved2.size());
}

size_t FlexRayVFrStatus::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(cycle) +
        sizeof(reserved1) +
        sizeof(clientIndex) +
        sizeof(clusterNo) +
        sizeof(wus) +
        sizeof(ccSyncState) +
        sizeof(tag) +
        data.size() * sizeof(DWORD) +
        reserved2.size() * sizeof(WORD);

    return size;
}

}
}
