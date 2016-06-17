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
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    is.read(reinterpret_cast<char *>(&validDataBytes), sizeof(validDataBytes));
    is.read(reinterpret_cast<char *>(&ecc), sizeof(ecc));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&errorCodeExt), sizeof(errorCodeExt));
    is.read(reinterpret_cast<char *>(&extFlags), sizeof(extFlags));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&id), sizeof(id));
    is.read(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    is.read(reinterpret_cast<char *>(&btrCfgArb), sizeof(btrCfgArb));
    is.read(reinterpret_cast<char *>(&btrCfgData), sizeof(btrCfgData));
    is.read(reinterpret_cast<char *>(&timeOffsetBrsNs), sizeof(timeOffsetBrsNs));
    is.read(reinterpret_cast<char *>(&timeOffsetCrcDelNs), sizeof(timeOffsetCrcDelNs));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&errorPosition), sizeof(errorPosition));
    is.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    is.read(reinterpret_cast<char *>(data.data()), data.size());
}

void CanFdErrorFrame64::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dlc), sizeof(dlc));
    os.write(reinterpret_cast<char *>(&validDataBytes), sizeof(validDataBytes));
    os.write(reinterpret_cast<char *>(&ecc), sizeof(ecc));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&errorCodeExt), sizeof(errorCodeExt));
    os.write(reinterpret_cast<char *>(&extFlags), sizeof(extFlags));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&id), sizeof(id));
    os.write(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    os.write(reinterpret_cast<char *>(&btrCfgArb), sizeof(btrCfgArb));
    os.write(reinterpret_cast<char *>(&btrCfgData), sizeof(btrCfgData));
    os.write(reinterpret_cast<char *>(&timeOffsetBrsNs), sizeof(timeOffsetBrsNs));
    os.write(reinterpret_cast<char *>(&timeOffsetCrcDelNs), sizeof(timeOffsetCrcDelNs));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&errorPosition), sizeof(errorPosition));
    os.write(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    os.write(reinterpret_cast<char *>(data.data()), data.size());
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
