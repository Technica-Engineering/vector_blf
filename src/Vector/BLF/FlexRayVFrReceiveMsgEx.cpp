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

#include <Vector/BLF/FlexRayVFrReceiveMsgEx.h>

namespace Vector {
namespace BLF {

FlexRayVFrReceiveMsgEx::FlexRayVFrReceiveMsgEx() :
    ObjectHeader(),
    channel(),
    version(),
    channelMask(),
    dir(),
    clientIndexFlexRayVFrReceiveMsgEx(),
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
    reservedFlexRayVFrReceiveMsgEx(),
    dataBytes()
{
    objectType = ObjectType::FR_RCVMESSAGE_EX;
}

void FlexRayVFrReceiveMsgEx::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&version), sizeof(version));
    is.read(reinterpret_cast<char *>(&channelMask), sizeof(channelMask));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&clientIndexFlexRayVFrReceiveMsgEx), sizeof(clientIndexFlexRayVFrReceiveMsgEx));
    is.read(reinterpret_cast<char *>(&clusterNo), sizeof(clusterNo));
    is.read(reinterpret_cast<char *>(&frameId), sizeof(frameId));
    is.read(reinterpret_cast<char *>(&headerCrc1), sizeof(headerCrc1));
    is.read(reinterpret_cast<char *>(&headerCrc2), sizeof(headerCrc2));
    is.read(reinterpret_cast<char *>(&byteCount), sizeof(byteCount));
    is.read(reinterpret_cast<char *>(&dataCount), sizeof(dataCount));
    is.read(reinterpret_cast<char *>(&cycle), sizeof(cycle));
    is.read(reinterpret_cast<char *>(&tag), sizeof(tag));
    is.read(reinterpret_cast<char *>(&data), sizeof(data));
    is.read(reinterpret_cast<char *>(&frameFlags), sizeof(frameFlags));
    is.read(reinterpret_cast<char *>(&appParameter), sizeof(appParameter));
    is.read(reinterpret_cast<char *>(&frameCrc), sizeof(frameCrc));
    is.read(reinterpret_cast<char *>(&frameLengthNs), sizeof(frameLengthNs));
    is.read(reinterpret_cast<char *>(&frameId1), sizeof(frameId1));
    is.read(reinterpret_cast<char *>(&pduOffset), sizeof(pduOffset));
    is.read(reinterpret_cast<char *>(&blfLogMask), sizeof(blfLogMask));
    is.read(reinterpret_cast<char *>(reservedFlexRayVFrReceiveMsgEx.data()), static_cast<std::streamsize>(reservedFlexRayVFrReceiveMsgEx.size() * sizeof(WORD)));
    dataBytes.resize(dataCount);
    is.read(reinterpret_cast<char *>(dataBytes.data()), static_cast<std::streamsize>(dataCount));

    /* skip padding */
    uint8_t padding = (dataCount + 4) % 8;
    if (padding != 0) {
        is.seekg((8 - padding), std::ios_base::cur);
    }
}

void FlexRayVFrReceiveMsgEx::write(AbstractFile & os)
{
    /* pre processing */
    dataCount = static_cast<WORD>(dataBytes.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&version), sizeof(version));
    os.write(reinterpret_cast<char *>(&channelMask), sizeof(channelMask));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&clientIndexFlexRayVFrReceiveMsgEx), sizeof(clientIndexFlexRayVFrReceiveMsgEx));
    os.write(reinterpret_cast<char *>(&clusterNo), sizeof(clusterNo));
    os.write(reinterpret_cast<char *>(&frameId), sizeof(frameId));
    os.write(reinterpret_cast<char *>(&headerCrc1), sizeof(headerCrc1));
    os.write(reinterpret_cast<char *>(&headerCrc2), sizeof(headerCrc2));
    os.write(reinterpret_cast<char *>(&byteCount), sizeof(byteCount));
    os.write(reinterpret_cast<char *>(&dataCount), sizeof(dataCount));
    os.write(reinterpret_cast<char *>(&cycle), sizeof(cycle));
    os.write(reinterpret_cast<char *>(&tag), sizeof(tag));
    os.write(reinterpret_cast<char *>(&data), sizeof(data));
    os.write(reinterpret_cast<char *>(&frameFlags), sizeof(frameFlags));
    os.write(reinterpret_cast<char *>(&appParameter), sizeof(appParameter));
    os.write(reinterpret_cast<char *>(&frameCrc), sizeof(frameCrc));
    os.write(reinterpret_cast<char *>(&frameLengthNs), sizeof(frameLengthNs));
    os.write(reinterpret_cast<char *>(&frameId1), sizeof(frameId1));
    os.write(reinterpret_cast<char *>(&pduOffset), sizeof(pduOffset));
    os.write(reinterpret_cast<char *>(&blfLogMask), sizeof(blfLogMask));
    os.write(reinterpret_cast<char *>(reservedFlexRayVFrReceiveMsgEx.data()), static_cast<std::streamsize>(reservedFlexRayVFrReceiveMsgEx.size() * sizeof(WORD)));
    os.write(reinterpret_cast<char *>(dataBytes.data()), static_cast<std::streamsize>(dataCount));

    /* skip padding */
    uint8_t padding = (dataCount + 4) % 8;
    if (padding != 0) {
        os.seekp((8 - padding), std::ios_base::cur);
    }
}

DWORD FlexRayVFrReceiveMsgEx::calculateObjectSize() const
{
    DWORD size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(channelMask) +
        sizeof(dir) +
        sizeof(clientIndexFlexRayVFrReceiveMsgEx) +
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
        static_cast<DWORD>(reservedFlexRayVFrReceiveMsgEx.size() * sizeof(WORD)) +
        dataCount;

    /* skip padding */
    if (size % 8 != 0) {
        size += (8 - size % 8);
    }

    return size;
}

}
}
