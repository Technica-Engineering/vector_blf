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

#include "FlexRayV6Message.h"

namespace Vector {
namespace BLF {

FlexRayV6Message::FlexRayV6Message() :
    ObjectHeader(),
    channel(),
    dir(),
    lowTime(),
    fpgaTick(),
    fpgaTickOverflow(),
    clientIndex(),
    clusterTime(),
    frameId(),
    headerCrc(),
    frameState(),
    length(),
    cycle(),
    headerBitMask(),
    reserved1(),
    reserved2(),
    dataBytes()
{
    objectType = ObjectType::FLEXRAY_MESSAGE;
}

void FlexRayV6Message::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&lowTime), sizeof(lowTime));
    is.read(reinterpret_cast<char *>(&fpgaTick), sizeof(fpgaTick));
    is.read(reinterpret_cast<char *>(&fpgaTickOverflow), sizeof(fpgaTickOverflow));
    is.read(reinterpret_cast<char *>(&clientIndex), sizeof(clientIndex));
    is.read(reinterpret_cast<char *>(&clusterTime), sizeof(clusterTime));
    is.read(reinterpret_cast<char *>(&frameId), sizeof(frameId));
    is.read(reinterpret_cast<char *>(&headerCrc), sizeof(headerCrc));
    is.read(reinterpret_cast<char *>(&frameState), sizeof(frameState));
    is.read(reinterpret_cast<char *>(&length), sizeof(length));
    is.read(reinterpret_cast<char *>(&cycle), sizeof(cycle));
    is.read(reinterpret_cast<char *>(&headerBitMask), sizeof(headerBitMask));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    is.read(reinterpret_cast<char *>(dataBytes.data()), dataBytes.size());
}

void FlexRayV6Message::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&lowTime), sizeof(lowTime));
    os.write(reinterpret_cast<char *>(&fpgaTick), sizeof(fpgaTick));
    os.write(reinterpret_cast<char *>(&fpgaTickOverflow), sizeof(fpgaTickOverflow));
    os.write(reinterpret_cast<char *>(&clientIndex), sizeof(clientIndex));
    os.write(reinterpret_cast<char *>(&clusterTime), sizeof(clusterTime));
    os.write(reinterpret_cast<char *>(&frameId), sizeof(frameId));
    os.write(reinterpret_cast<char *>(&headerCrc), sizeof(headerCrc));
    os.write(reinterpret_cast<char *>(&frameState), sizeof(frameState));
    os.write(reinterpret_cast<char *>(&length), sizeof(length));
    os.write(reinterpret_cast<char *>(&cycle), sizeof(cycle));
    os.write(reinterpret_cast<char *>(&headerBitMask), sizeof(headerBitMask));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    os.write(reinterpret_cast<char *>(dataBytes.data()), dataBytes.size());
}

size_t FlexRayV6Message::calculateObjectSize()
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
        sizeof(frameId) +
        sizeof(headerCrc) +
        sizeof(frameState) +
        sizeof(length) +
        sizeof(cycle) +
        sizeof(headerBitMask) +
        sizeof(reserved1) +
        sizeof(reserved2) +
        dataBytes.size();

    return size;
}

}
}
