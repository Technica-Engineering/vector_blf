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

#include "FlexRayVFrReceiveMsgEx.h"

namespace Vector {
namespace BLF {

FlexRayVFrReceiveMsgEx::FlexRayVFrReceiveMsgEx() :
    ObjectHeader(),
    channel(),
    version(),
    channelMask(),
    dir(),
    clientIndex(),
    clusterNo(),
    frameId(),
    headerCrc1(),
    headerCrc2(),
    byteCount(),
    dataCount(),
    cycle(),
    tag(),
    data(),
    frameFlags(),
    appParameter(),
    frameCrc(),
    frameLengthNs(),
    frameId1(),
    pduOffset(),
    blfLogMask(),
    reserved(),
    dataBytes()
{
    objectType = ObjectType::FR_RCVMESSAGE_EX;
}

void FlexRayVFrReceiveMsgEx::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &version, sizeof(version));
    is.read((char *) &channelMask, sizeof(channelMask));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &clientIndex, sizeof(clientIndex));
    is.read((char *) &clusterNo, sizeof(clusterNo));
    is.read((char *) &frameId, sizeof(frameId));
    is.read((char *) &headerCrc1, sizeof(headerCrc1));
    is.read((char *) &headerCrc2, sizeof(headerCrc2));
    is.read((char *) &byteCount, sizeof(byteCount));
    is.read((char *) &dataCount, sizeof(dataCount));
    is.read((char *) &cycle, sizeof(cycle));
    is.read((char *) &tag, sizeof(tag));
    is.read((char *) &data, sizeof(data));
    is.read((char *) &frameFlags, sizeof(frameFlags));
    is.read((char *) &appParameter, sizeof(appParameter));
    is.read((char *) &frameCrc, sizeof(frameCrc));
    is.read((char *) &frameLengthNs, sizeof(frameLengthNs));
    is.read((char *) &frameId1, sizeof(frameId1));
    is.read((char *) &pduOffset, sizeof(pduOffset));
    is.read((char *) &blfLogMask, sizeof(blfLogMask));
    is.read((char *) reserved.data(), reserved.size());
    dataBytes.resize(dataCount);
    is.read((char *) dataBytes.data(), dataCount);
}

void FlexRayVFrReceiveMsgEx::write(AbstractFile & os)
{
    /* pre processing */
    dataCount = dataBytes.size();

    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &version, sizeof(version));
    os.write((char *) &channelMask, sizeof(channelMask));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &clientIndex, sizeof(clientIndex));
    os.write((char *) &clusterNo, sizeof(clusterNo));
    os.write((char *) &frameId, sizeof(frameId));
    os.write((char *) &headerCrc1, sizeof(headerCrc1));
    os.write((char *) &headerCrc2, sizeof(headerCrc2));
    os.write((char *) &byteCount, sizeof(byteCount));
    os.write((char *) &dataCount, sizeof(dataCount));
    os.write((char *) &cycle, sizeof(cycle));
    os.write((char *) &tag, sizeof(tag));
    os.write((char *) &data, sizeof(data));
    os.write((char *) &frameFlags, sizeof(frameFlags));
    os.write((char *) &appParameter, sizeof(appParameter));
    os.write((char *) &frameCrc, sizeof(frameCrc));
    os.write((char *) &frameLengthNs, sizeof(frameLengthNs));
    os.write((char *) &frameId1, sizeof(frameId1));
    os.write((char *) &pduOffset, sizeof(pduOffset));
    os.write((char *) &blfLogMask, sizeof(blfLogMask));
    os.write((char *) reserved.data(), reserved.size());
    os.write((char *) dataBytes.data(), dataCount);
}

size_t FlexRayVFrReceiveMsgEx::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(dir) +
        sizeof(clientIndex) +
        sizeof(clusterNo) +
        sizeof(frameId) +
        sizeof(headerCrc1) +
        sizeof(headerCrc2) +
        sizeof(byteCount) +
        sizeof(dataCount) +
        sizeof(cycle) +
        sizeof(tag) +
        sizeof(data) +
        sizeof(frameFlags) +
        sizeof(appParameter) +
        sizeof(frameCrc) +
        sizeof(frameLengthNs) +
        sizeof(frameId1) +
        sizeof(pduOffset) +
        sizeof(blfLogMask) +
        reserved.size() +
        dataCount;

    return size;
}

}
}
