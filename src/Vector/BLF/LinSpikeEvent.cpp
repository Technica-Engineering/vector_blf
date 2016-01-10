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

#include "LinSpikeEvent.h"

namespace Vector {
namespace BLF {

LinSpikeEvent::LinSpikeEvent() :
    ObjectHeader(),
    channel(),
    width(),
    reserved()
{
    objectType = ObjectType::LIN_SPIKE_EVENT;
}

void LinSpikeEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &width, sizeof(width));
    is.read((char *) reserved.data(), reserved.size());
}

void LinSpikeEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &width, sizeof(width));
    os.write((char *) reserved.data(), reserved.size());
}

size_t LinSpikeEvent::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(width) +
        reserved.size();

    return size;
}

}
}
