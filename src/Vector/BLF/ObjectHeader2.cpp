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

#include "ObjectHeader2.h"

namespace Vector {
namespace BLF {

ObjectHeader2::ObjectHeader2() :
    ObjectHeaderBase(),
    objectFlags(),
    timeStampStatus(),
    reserved(),
    objectVersion(),
    objectTimeStamp(),
    originalTimeStamp(),
    alreadyRead(false)
{
}

void ObjectHeader2::read(std::istream & is)
{
    if (alreadyRead)
        return;

    ObjectHeaderBase::read(is);

    const std::streamsize size =
            sizeof(objectFlags) +
            sizeof(timeStampStatus) +
            sizeof(reserved) +
            sizeof(objectVersion) +
            sizeof(objectTimeStamp) +
            sizeof(originalTimeStamp);
    is.read((char *) &objectFlags, size);
    remainingSize -= size;
    alreadyRead = true;
}

}
}
