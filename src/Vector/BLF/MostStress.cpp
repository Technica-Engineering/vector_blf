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

#include "MostStress.h"

namespace Vector {
namespace BLF {

MostStress::MostStress() :
    ObjectHeader2(),
    channel(),
    state(),
    mode(),
    reserved()
{
    objectType = ObjectType::MOST_STRESS;
}

void MostStress::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &state, sizeof(state));
    is.read((char *) &mode, sizeof(mode));
    is.read((char *) &reserved, sizeof(reserved));
}

void MostStress::write(AbstractFile & os)
{
    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &state, sizeof(state));
    os.write((char *) &mode, sizeof(mode));
    os.write((char *) &reserved, sizeof(reserved));
}

size_t MostStress::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(state) +
        sizeof(mode) +
        sizeof(reserved);

    return size;
}

}
}
