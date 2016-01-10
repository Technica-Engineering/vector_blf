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

#include "AbstractFile.h"

#include "FlexRayVFrStartCycle.h"

namespace Vector {
namespace BLF {

FlexRayVFrStartCycle::FlexRayVFrStartCycle() :
    ObjectHeader(),
    channel(),
    version(),
    channelMask(),
    dir(),
    cycle(),
    clientIndex(),
    clusterNo(),
    nmSize(),
    dataBytes(),
    reserved1(),
    tag(),
    data(),
    reserved2()
{
    objectType = ObjectType::FR_STARTCYCLE;
}

void FlexRayVFrStartCycle::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &version, sizeof(version));
    is.read((char *) &channelMask, sizeof(channelMask));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &cycle, sizeof(cycle));
    is.read((char *) &clientIndex, sizeof(clientIndex));
    is.read((char *) &clusterNo, sizeof(clusterNo));
    is.read((char *) &nmSize, sizeof(nmSize));
    is.read((char *) dataBytes.data(), dataBytes.size());
    is.read((char *) reserved1.data(), reserved1.size());
    is.read((char *) &tag, sizeof(tag));
    is.read((char *) data.data(), data.size() * sizeof(DWORD));
    is.read((char *) reserved2.data(), reserved2.size());
}

void FlexRayVFrStartCycle::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &version, sizeof(version));
    os.write((char *) &channelMask, sizeof(channelMask));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &cycle, sizeof(cycle));
    os.write((char *) &clientIndex, sizeof(clientIndex));
    os.write((char *) &clusterNo, sizeof(clusterNo));
    os.write((char *) &nmSize, sizeof(nmSize));
    os.write((char *) dataBytes.data(), dataBytes.size());
    os.write((char *) reserved1.data(), reserved1.size());
    os.write((char *) &tag, sizeof(tag));
    os.write((char *) data.data(), data.size() * sizeof(DWORD));
    os.write((char *) reserved2.data(), reserved2.size());
}

size_t FlexRayVFrStartCycle::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(dir) +
        sizeof(cycle) +
        sizeof(clientIndex) +
        sizeof(clusterNo) +
        sizeof(nmSize) +
        dataBytes.size() +
        reserved1.size() +
        sizeof(tag) +
        data.size() * sizeof(DWORD) +
        reserved2.size();

    return size;
}

}
}
