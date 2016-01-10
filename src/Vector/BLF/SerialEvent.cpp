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

#include "SerialEvent.h"

namespace Vector {
namespace BLF {

SerialEvent::GeneralSerialEvent::GeneralSerialEvent() :
    dataLength(),
    timeStampsLength(),
    data(),
    timeStamps()
{
}

SerialEvent::SingleByteSerialEvent::SingleByteSerialEvent() :
    byte()
{
}

SerialEvent::CompactSerialEvent::CompactSerialEvent() :
    compactLength(),
    compactData()
{
}

SerialEvent::SerialEvent() :
    ObjectHeader(),
    flags(),
    port(),
    baudrate(),
    reserved(),
    general(),
    singleByte(),
    compact()
{
    objectType = ObjectType::SERIAL_EVENT;
}

void SerialEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &port, sizeof(port));
    is.read((char *) &baudrate, sizeof(baudrate));
    is.read((char *) &reserved, sizeof(reserved));

    if ((flags & ((DWORD) Flags::SingleByte)) != 0) {
        is.read((char *) &singleByte.byte, sizeof(singleByte.byte));
    } else {
        if ((flags & ((DWORD) Flags::CompactByte)) != 0) {
            is.read((char *) &compact.compactLength, sizeof(compact.compactLength));
            is.read((char *) &compact.compactData, sizeof(compact.compactData));
        } else {
            is.read((char *) &general.dataLength, sizeof(general.dataLength));
            is.read((char *) &general.timeStampsLength, sizeof(general.timeStampsLength));
            general.data.resize(general.dataLength);
            is.read((char *) general.data.data(), general.dataLength);
            general.timeStamps.resize(general.timeStampsLength / sizeof(LONGLONG));
            is.read((char *) general.timeStamps.data(), general.timeStampsLength);
        }
    }
}

void SerialEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &port, sizeof(port));
    os.write((char *) &baudrate, sizeof(baudrate));
    os.write((char *) &reserved, sizeof(reserved));

    if ((flags & ((DWORD) Flags::SingleByte)) != 0) {
        os.write((char *) &singleByte.byte, sizeof(singleByte.byte));
    } else {
        if ((flags & ((DWORD) Flags::CompactByte)) != 0) {
            os.write((char *) &compact.compactLength, sizeof(compact.compactLength));
            os.write((char *) &compact.compactData, sizeof(compact.compactData));
        } else {
            /* pre processing */
            general.dataLength = general.data.size();
            general.timeStampsLength = general.timeStamps.size() * sizeof(LONGLONG);

            os.write((char *) &general.dataLength, sizeof(general.dataLength));
            os.write((char *) &general.timeStampsLength, sizeof(general.timeStampsLength));
            os.write((char *) general.data.data(), general.dataLength);
            os.write((char *) general.timeStamps.data(), general.timeStampsLength);
        }
    }
}

size_t SerialEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(flags) +
        sizeof(port) +
        sizeof(baudrate) +
        sizeof(reserved);

    if ((flags & ((DWORD) Flags::SingleByte)) != 0)
        size += sizeof(singleByte);
    else if ((flags & ((DWORD) Flags::CompactByte)) != 0)
        size += sizeof(compact);
    else
        size += sizeof(general.dataLength) +
                sizeof(general.timeStampsLength) +
                general.dataLength +
                general.timeStampsLength;

    return size;
}

}
}
