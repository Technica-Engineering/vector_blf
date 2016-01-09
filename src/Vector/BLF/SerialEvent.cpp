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

SerialEvent::SerialEvent() :
    ObjectHeader(),
    flags(),
    port(),
    baudrate(),
    reserved()
{
    objectType = ObjectType::SERIAL_EVENT;
}

SerialEvent::~SerialEvent()
{
    // @todo free memory of GeneralSerialEvent
}

void SerialEvent::read(std::istream & is)
{
    ObjectHeader::read(is);
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &port, sizeof(port));
    is.read((char *) &baudrate, sizeof(baudrate));
    is.read((char *) &reserved, sizeof(reserved));

    if ((flags & ((DWORD) Flags::SingleByte)) != 0) {
        is.read((char *) &data.singleByte.byte, sizeof(data.singleByte.byte));
    } else {
        if ((flags & ((DWORD) Flags::CompactByte)) != 0) {
            is.read((char *) &data.compact.compactLength, sizeof(data.compact.compactLength));
            is.read((char *) &data.compact.compactData, sizeof(data.compact.compactData));
        } else {
            is.read((char *) &data.general.dataLength, sizeof(data.general.dataLength));
            is.read((char *) &data.general.timeStampsLength, sizeof(data.general.timeStampsLength));
            data.general.data = new char[data.general.dataLength];
            is.read((char *) &data.general.data, data.general.dataLength);
            data.general.timeStamps = (LONGLONG *) new char[data.general.timeStampsLength];
            is.read((char *) &data.general.timeStamps, data.general.timeStampsLength);
        }
    }
}

void SerialEvent::write(std::ostream & os)
{
    ObjectHeader::write(os);
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &port, sizeof(port));
    os.write((char *) &baudrate, sizeof(baudrate));
    os.write((char *) &reserved, sizeof(reserved));

    if ((flags & ((DWORD) Flags::SingleByte)) != 0) {
        os.write((char *) &data.singleByte.byte, sizeof(data.singleByte.byte));
    } else {
        if ((flags & ((DWORD) Flags::CompactByte)) != 0) {
            os.write((char *) &data.compact.compactLength, sizeof(data.compact.compactLength));
            os.write((char *) &data.compact.compactData, sizeof(data.compact.compactData));
        } else {
            os.write((char *) &data.general.dataLength, sizeof(data.general.dataLength));
            os.write((char *) &data.general.timeStampsLength, sizeof(data.general.timeStampsLength));
            os.write((char *) &data.general.data, data.general.dataLength);
            os.write((char *) &data.general.timeStamps, data.general.timeStampsLength);
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
        size += sizeof(data.singleByte);
    else if ((flags & ((DWORD) Flags::CompactByte)) != 0)
        size += sizeof(data.compact);
    else
        size += sizeof(data.general.dataLength) +
                sizeof(data.general.timeStampsLength) +
                data.general.dataLength +
                data.general.timeStampsLength;

    return size;
}

}
}
