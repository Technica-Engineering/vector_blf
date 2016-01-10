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

#include "MostNetState.h"

namespace Vector {
namespace BLF {

MostNetState::MostNetState() :
    ObjectHeader2(),
    channel(),
    stateNew(),
    stateOld(),
    reserved()
{
    objectType = ObjectType::MOST_NETSTATE;
}

void MostNetState::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &stateNew, sizeof(stateNew));
    is.read((char *) &stateOld, sizeof(stateOld));
    is.read((char *) &reserved, sizeof(reserved));
}

void MostNetState::write(AbstractFile & os)
{
    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &stateNew, sizeof(stateNew));
    os.write((char *) &stateOld, sizeof(stateOld));
    os.write((char *) &reserved, sizeof(reserved));
}

size_t MostNetState::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(stateNew) +
        sizeof(stateOld) +
        sizeof(reserved);

    return size;
}

}
}
