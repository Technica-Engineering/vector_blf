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

#include "LinBusEvent.h"

namespace Vector {
namespace BLF {

LinBusEvent::LinBusEvent() :
    sof(),
    eventBaudrate(),
    channel(),
    reserved()
{
}

LinBusEvent::~LinBusEvent()
{
}

void LinBusEvent::read(AbstractFile & is)
{
    is.read((char *) &sof, sizeof(sof));
    is.read((char *) &eventBaudrate, sizeof(eventBaudrate));
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) reserved.data(), reserved.size());
}

void LinBusEvent::write(AbstractFile & os)
{
    os.write((char *) &sof, sizeof(sof));
    os.write((char *) &eventBaudrate, sizeof(eventBaudrate));
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) reserved.data(), reserved.size());
}

size_t LinBusEvent::calculateObjectSize()
{
    size_t size =
        sizeof(sof) +
        sizeof(eventBaudrate) +
        sizeof(channel) +
        reserved.size();

    return size;
}

}
}
