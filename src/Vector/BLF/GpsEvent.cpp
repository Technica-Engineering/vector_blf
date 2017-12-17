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

#include <Vector/BLF/GpsEvent.h>

namespace Vector {
namespace BLF {

GpsEvent::GpsEvent() :
    ObjectHeader(),
    flags(),
    channel(),
    reservedGpsEvent(),
    latitude(),
    longitude(),
    altitude(),
    speed(),
    course()
{
    objectType = ObjectType::GPS_EVENT;
}

void GpsEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&reservedGpsEvent), sizeof(reservedGpsEvent));
    is.read(reinterpret_cast<char *>(&latitude), sizeof(latitude));
    is.read(reinterpret_cast<char *>(&longitude), sizeof(longitude));
    is.read(reinterpret_cast<char *>(&altitude), sizeof(altitude));
    is.read(reinterpret_cast<char *>(&speed), sizeof(speed));
    is.read(reinterpret_cast<char *>(&course), sizeof(course));
}

void GpsEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&reservedGpsEvent), sizeof(reservedGpsEvent));
    os.write(reinterpret_cast<char *>(&latitude), sizeof(latitude));
    os.write(reinterpret_cast<char *>(&longitude), sizeof(longitude));
    os.write(reinterpret_cast<char *>(&altitude), sizeof(altitude));
    os.write(reinterpret_cast<char *>(&speed), sizeof(speed));
    os.write(reinterpret_cast<char *>(&course), sizeof(course));
}

DWORD GpsEvent::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(flags) +
        sizeof(channel) +
        sizeof(reservedGpsEvent) +
        sizeof(latitude) +
        sizeof(longitude) +
        sizeof(altitude) +
        sizeof(speed) +
        sizeof(course);
}

}
}
