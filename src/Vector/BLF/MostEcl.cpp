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

#include "MostEcl.h"

namespace Vector {
namespace BLF {

MostEcl::MostEcl() :
    ObjectHeader2(),
    channel(),
    mode(),
    eclState(),
    reserved()
{
    objectType = ObjectType::MOST_ECL;
}

void MostEcl::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &mode, sizeof(mode));
    is.read((char *) &eclState, sizeof(eclState));
    is.read((char *) &reserved, sizeof(reserved));
}

void MostEcl::write(AbstractFile & os)
{
    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &mode, sizeof(mode));
    os.write((char *) &eclState, sizeof(eclState));
    os.write((char *) &reserved, sizeof(reserved));
}

size_t MostEcl::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(mode) +
        sizeof(eclState) +
        sizeof(reserved);

    return size;
}

}
}
