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

#include "CanFdMessage64.h"

namespace Vector {
namespace BLF {

CanFdMessage64::CanFdMessage64() :
    ObjectHeader(),
    channel(),
    dlc(),
    validDataBytes(),
    txCount(),
    id(),
    frameLength(),
    flags(),
    btrCfgArb(),
    btrCfgData(),
    timeOffsetBrsNs(),
    timeOffsetCrcDelNs(),
    bitCount(),
    dir(),
    reserved1(),
    reserved2(),
    data()
{
    objectType = ObjectType::CAN_FD_MESSAGE_64;
}

void CanFdMessage64::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &dlc, sizeof(dlc));
    is.read((char *) &validDataBytes, sizeof(validDataBytes));
    is.read((char *) &txCount, sizeof(txCount));
    is.read((char *) &id, sizeof(id));
    is.read((char *) &frameLength, sizeof(frameLength));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &btrCfgArb, sizeof(btrCfgArb));
    is.read((char *) &btrCfgData, sizeof(btrCfgData));
    is.read((char *) &timeOffsetBrsNs, sizeof(timeOffsetBrsNs));
    is.read((char *) &timeOffsetCrcDelNs, sizeof(timeOffsetCrcDelNs));
    is.read((char *) &bitCount, sizeof(bitCount));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) data.data(), data.size());
}

void CanFdMessage64::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &dlc, sizeof(dlc));
    os.write((char *) &validDataBytes, sizeof(validDataBytes));
    os.write((char *) &txCount, sizeof(txCount));
    os.write((char *) &id, sizeof(id));
    os.write((char *) &frameLength, sizeof(frameLength));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &btrCfgArb, sizeof(btrCfgArb));
    os.write((char *) &btrCfgData, sizeof(btrCfgData));
    os.write((char *) &timeOffsetBrsNs, sizeof(timeOffsetBrsNs));
    os.write((char *) &timeOffsetCrcDelNs, sizeof(timeOffsetCrcDelNs));
    os.write((char *) &bitCount, sizeof(bitCount));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) data.data(), data.size());
}

size_t CanFdMessage64::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dlc) +
        sizeof(validDataBytes) +
        sizeof(txCount) +
        sizeof(id) +
        sizeof(frameLength) +
        sizeof(flags) +
        sizeof(btrCfgArb) +
        sizeof(btrCfgData) +
        sizeof(timeOffsetBrsNs) +
        sizeof(timeOffsetCrcDelNs) +
        sizeof(bitCount) +
        sizeof(dir) +
        sizeof(reserved1) +
        sizeof(reserved2) +
        data.size();

    return size;
}

}
}
