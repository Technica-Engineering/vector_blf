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

#include "FlexRayVFrReceiveMsg.h"

namespace Vector {
namespace BLF {

FlexRayVFrReceiveMsg::FlexRayVFrReceiveMsg() :
    ObjectHeader(),
    channel(),
    version(),
    channelMask(),
    dir(),
    reserved1(),
    clientIndex(),
    clusterNo(),
    frameId(),
    headerCrc1(),
    headerCrc2(),
    byteCount(),
    dataCount(),
    cycle(),
    reserved2(),
    tag(),
    data(),
    frameFlags(),
    appParameter(),
    dataBytes()
{
    objectType = ObjectType::FR_RCVMESSAGE;
}

void FlexRayVFrReceiveMsg::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &version, sizeof(version));
    is.read((char *) &channelMask, sizeof(channelMask));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &clientIndex, sizeof(clientIndex));
    is.read((char *) &clusterNo, sizeof(clusterNo));
    is.read((char *) &frameId, sizeof(frameId));
    is.read((char *) &headerCrc1, sizeof(headerCrc1));
    is.read((char *) &headerCrc2, sizeof(headerCrc2));
    is.read((char *) &byteCount, sizeof(byteCount));
    is.read((char *) &dataCount, sizeof(dataCount));
    is.read((char *) &cycle, sizeof(cycle));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) &tag, sizeof(tag));
    is.read((char *) &data, sizeof(data));
    is.read((char *) &frameFlags, sizeof(frameFlags));
    is.read((char *) &appParameter, sizeof(appParameter));
    is.read((char *) dataBytes.data(), dataBytes.size());
}

void FlexRayVFrReceiveMsg::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &version, sizeof(version));
    os.write((char *) &channelMask, sizeof(channelMask));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &clientIndex, sizeof(clientIndex));
    os.write((char *) &clusterNo, sizeof(clusterNo));
    os.write((char *) &frameId, sizeof(frameId));
    os.write((char *) &headerCrc1, sizeof(headerCrc1));
    os.write((char *) &headerCrc2, sizeof(headerCrc2));
    os.write((char *) &byteCount, sizeof(byteCount));
    os.write((char *) &dataCount, sizeof(dataCount));
    os.write((char *) &cycle, sizeof(cycle));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) &tag, sizeof(tag));
    os.write((char *) &data, sizeof(data));
    os.write((char *) &frameFlags, sizeof(frameFlags));
    os.write((char *) &appParameter, sizeof(appParameter));
    os.write((char *) dataBytes.data(), dataBytes.size());
}

size_t FlexRayVFrReceiveMsg::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(dir) +
        sizeof(reserved1) +
        sizeof(clientIndex) +
        sizeof(clusterNo) +
        sizeof(frameId) +
        sizeof(headerCrc1) +
        sizeof(headerCrc2) +
        sizeof(byteCount) +
        sizeof(dataCount) +
        sizeof(cycle) +
        sizeof(reserved2) +
        sizeof(tag) +
        sizeof(data) +
        sizeof(frameFlags) +
        sizeof(appParameter) +
        dataBytes.size();

    return size;
}

}
}
