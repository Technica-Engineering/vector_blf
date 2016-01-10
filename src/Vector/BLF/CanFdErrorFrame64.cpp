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

#include "CanFdErrorFrame64.h"

namespace Vector {
namespace BLF {

CanFdErrorFrame64::CanFdErrorFrame64() :
    ObjectHeader(),
    channel(),
    dlc(),
    validDataBytes(),
    ecc(),
    flags(),
    errorCodeExt(),
    extFlags(),
    reserved1(),
    id(),
    frameLength(),
    btrCfgArb(),
    btrCfgData(),
    timeOffsetBrsNs(),
    timeOffsetCrcDelNs(),
    crc(),
    errorPosition(),
    reserved2(),
    data()
{
    objectType = ObjectType::CAN_FD_ERROR_64;
}

void CanFdErrorFrame64::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &dlc, sizeof(dlc));
    is.read((char *) &validDataBytes, sizeof(validDataBytes));
    is.read((char *) &ecc, sizeof(ecc));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &errorCodeExt, sizeof(errorCodeExt));
    is.read((char *) &extFlags, sizeof(extFlags));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &id, sizeof(id));
    is.read((char *) &frameLength, sizeof(frameLength));
    is.read((char *) &btrCfgArb, sizeof(btrCfgArb));
    is.read((char *) &btrCfgData, sizeof(btrCfgData));
    is.read((char *) &timeOffsetBrsNs, sizeof(timeOffsetBrsNs));
    is.read((char *) &timeOffsetCrcDelNs, sizeof(timeOffsetCrcDelNs));
    is.read((char *) &crc, sizeof(crc));
    is.read((char *) &errorPosition, sizeof(errorPosition));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) data.data(), data.size());
}

void CanFdErrorFrame64::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &dlc, sizeof(dlc));
    os.write((char *) &validDataBytes, sizeof(validDataBytes));
    os.write((char *) &ecc, sizeof(ecc));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &errorCodeExt, sizeof(errorCodeExt));
    os.write((char *) &extFlags, sizeof(extFlags));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &id, sizeof(id));
    os.write((char *) &frameLength, sizeof(frameLength));
    os.write((char *) &btrCfgArb, sizeof(btrCfgArb));
    os.write((char *) &btrCfgData, sizeof(btrCfgData));
    os.write((char *) &timeOffsetBrsNs, sizeof(timeOffsetBrsNs));
    os.write((char *) &timeOffsetCrcDelNs, sizeof(timeOffsetCrcDelNs));
    os.write((char *) &crc, sizeof(crc));
    os.write((char *) &errorPosition, sizeof(errorPosition));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) data.data(), data.size());
}

size_t CanFdErrorFrame64::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dlc) +
        sizeof(validDataBytes) +
        sizeof(ecc) +
        sizeof(flags) +
        sizeof(errorCodeExt) +
        sizeof(extFlags) +
        sizeof(reserved1) +
        sizeof(id) +
        sizeof(frameLength) +
        sizeof(btrCfgArb) +
        sizeof(btrCfgData) +
        sizeof(timeOffsetBrsNs) +
        sizeof(timeOffsetCrcDelNs) +
        sizeof(crc) +
        sizeof(errorPosition) +
        sizeof(reserved2) +
        data.size();

    return size;
}

}
}
