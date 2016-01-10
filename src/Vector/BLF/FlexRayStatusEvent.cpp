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

#include "FlexRayStatusEvent.h"

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
    reserved()
{
    objectType = ObjectType::FLEXRAY_STATUS;
}

void FlexRayStatusEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &version, sizeof(version));
    is.read((char *) &statusType, sizeof(statusType));
    is.read((char *) &infoMask1, sizeof(infoMask1));
    is.read((char *) &infoMask2, sizeof(infoMask2));
    is.read((char *) &infoMask3, sizeof(infoMask3));
    is.read((char *) reserved.data(), reserved.size());
}

void FlexRayStatusEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &version, sizeof(version));
    os.write((char *) &statusType, sizeof(statusType));
    os.write((char *) &infoMask1, sizeof(infoMask1));
    os.write((char *) &infoMask2, sizeof(infoMask2));
    os.write((char *) &infoMask3, sizeof(infoMask3));
    os.write((char *) reserved.data(), reserved.size());
}

size_t FlexRayStatusEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(version) +
        sizeof(statusType) +
        sizeof(infoMask1) +
        sizeof(infoMask2) +
        sizeof(infoMask3) +
        reserved.size() * sizeof(WORD);

    return size;
}

}
}
