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

#include <Vector/BLF/FlexRayStatusEvent.h>

namespace Vector {
namespace BLF {

FlexRayStatusEvent::FlexRayStatusEvent() :
    ObjectHeader(),
    channel(),
    version(),
    statusType(),
    infoMask1(),
    infoMask2(),
    infoMask3(),
    reservedFlexRayStatusEvent()
{
    objectType = ObjectType::FLEXRAY_STATUS;
}

void FlexRayStatusEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&version), sizeof(version));
    is.read(reinterpret_cast<char *>(&statusType), sizeof(statusType));
    is.read(reinterpret_cast<char *>(&infoMask1), sizeof(infoMask1));
    is.read(reinterpret_cast<char *>(&infoMask2), sizeof(infoMask2));
    is.read(reinterpret_cast<char *>(&infoMask3), sizeof(infoMask3));
    is.read(reinterpret_cast<char *>(reservedFlexRayStatusEvent.data()), static_cast<std::streamsize>(reservedFlexRayStatusEvent.size() * sizeof(WORD)));
}

void FlexRayStatusEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&version), sizeof(version));
    os.write(reinterpret_cast<char *>(&statusType), sizeof(statusType));
    os.write(reinterpret_cast<char *>(&infoMask1), sizeof(infoMask1));
    os.write(reinterpret_cast<char *>(&infoMask2), sizeof(infoMask2));
    os.write(reinterpret_cast<char *>(&infoMask3), sizeof(infoMask3));
    os.write(reinterpret_cast<char *>(reservedFlexRayStatusEvent.data()), static_cast<std::streamsize>(reservedFlexRayStatusEvent.size() * sizeof(WORD)));
}

DWORD FlexRayStatusEvent::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(statusType) +
        sizeof(infoMask1) +
        sizeof(infoMask2) +
        sizeof(infoMask3) +
        static_cast<DWORD>(reservedFlexRayStatusEvent.size() * sizeof(WORD));
}

}
}
