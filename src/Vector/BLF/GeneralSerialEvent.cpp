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

#include <Vector/BLF/GeneralSerialEvent.h>

namespace Vector {
namespace BLF {

GeneralSerialEvent::GeneralSerialEvent() :
    dataLength(),
    timeStampsLength(),
    reservedGeneralSerialEvent(),
    data(),
    timeStamps()
{
}

GeneralSerialEvent::~GeneralSerialEvent()
{
}

void GeneralSerialEvent::read(AbstractFile & is)
{
    is.read(reinterpret_cast<char *>(&dataLength), sizeof(dataLength));
    is.read(reinterpret_cast<char *>(&timeStampsLength), sizeof(timeStampsLength));
    is.read(reinterpret_cast<char *>(&reservedGeneralSerialEvent), sizeof(reservedGeneralSerialEvent));
    data.resize(dataLength);
    is.read(reinterpret_cast<char *>(data.data()), dataLength);
    timeStamps.resize(timeStampsLength / sizeof(LONGLONG));
    is.read(reinterpret_cast<char *>(timeStamps.data()), timeStampsLength);
}

void GeneralSerialEvent::write(AbstractFile & os)
{
    /* pre processing */
    dataLength = static_cast<DWORD>(data.size());
    timeStampsLength = static_cast<DWORD>(timeStamps.size() * sizeof(LONGLONG));

    os.write(reinterpret_cast<char *>(&dataLength), sizeof(dataLength));
    os.write(reinterpret_cast<char *>(&timeStampsLength), sizeof(timeStampsLength));
    os.write(reinterpret_cast<char *>(&reservedGeneralSerialEvent), sizeof(reservedGeneralSerialEvent));
    os.write(reinterpret_cast<char *>(data.data()), dataLength);
    os.write(reinterpret_cast<char *>(timeStamps.data()), timeStampsLength);
}

DWORD GeneralSerialEvent::calculateObjectSize() const
{
    return
        sizeof(dataLength) +
        sizeof(timeStampsLength) +
        sizeof(reservedGeneralSerialEvent) +
        dataLength +
        timeStampsLength;
}

}
}
