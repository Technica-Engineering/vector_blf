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

#include "FlexRayV6StartCycleEvent.h"

namespace Vector {
namespace BLF {

FlexRayV6StartCycleEvent::FlexRayV6StartCycleEvent() :
    ObjectHeader(),
    channel(),
    dir(),
    lowTime(),
    fpgaTick(),
    fpgaTickOverflow(),
    clientIndex(),
    clusterTime(),
    dataBytes(),
    reserved()
{
    objectType = ObjectType::FLEXRAY_CYCLE;
}

void FlexRayV6StartCycleEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &lowTime, sizeof(lowTime));
    is.read((char *) &fpgaTick, sizeof(fpgaTick));
    is.read((char *) &fpgaTickOverflow, sizeof(fpgaTickOverflow));
    is.read((char *) &clientIndex, sizeof(clientIndex));
    is.read((char *) &clusterTime, sizeof(clusterTime));
    is.read((char *) dataBytes.data(), dataBytes.size());
    is.read((char *) reserved.data(), reserved.size());
}

void FlexRayV6StartCycleEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &lowTime, sizeof(lowTime));
    os.write((char *) &fpgaTick, sizeof(fpgaTick));
    os.write((char *) &fpgaTickOverflow, sizeof(fpgaTickOverflow));
    os.write((char *) &clientIndex, sizeof(clientIndex));
    os.write((char *) &clusterTime, sizeof(clusterTime));
    os.write((char *) dataBytes.data(), dataBytes.size());
    os.write((char *) reserved.data(), reserved.size());
}

size_t FlexRayV6StartCycleEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(lowTime) +
        sizeof(fpgaTick) +
        sizeof(fpgaTickOverflow) +
        sizeof(clientIndex) +
        sizeof(clusterTime) +
        dataBytes.size() +
        reserved.size();

    return size;
}

}
}
