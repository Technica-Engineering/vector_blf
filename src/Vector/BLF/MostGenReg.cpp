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

#include "MostGenReg.h"

namespace Vector {
namespace BLF {

MostGenReg::MostGenReg() :
    ObjectHeader2(),
    channel(),
    subType(),
    reserved1(),
    handle(),
    regId(),
    reserved2(),
    reserved3(),
    regValue()
{
    objectType = ObjectType::MOST_GENREG;
}

void MostGenReg::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &subType, sizeof(subType));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &handle, sizeof(handle));
    is.read((char *) &regId, sizeof(regId));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) &reserved3, sizeof(reserved3));
    is.read((char *) &regValue, sizeof(regValue));
}

void MostGenReg::write(AbstractFile & os)
{
    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &subType, sizeof(subType));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &handle, sizeof(handle));
    os.write((char *) &regId, sizeof(regId));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) &reserved3, sizeof(reserved3));
    os.write((char *) &regValue, sizeof(regValue));
}

size_t MostGenReg::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(subType) +
        sizeof(reserved1) +
        sizeof(handle) +
        sizeof(regId) +
        sizeof(reserved2) +
        sizeof(reserved3) +
        sizeof(regValue);

    return size;
}

}
}
