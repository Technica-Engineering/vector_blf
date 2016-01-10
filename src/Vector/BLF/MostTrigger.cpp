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

#include "MostTrigger.h"

namespace Vector {
namespace BLF {

MostTrigger::MostTrigger() :
    ObjectHeader2(),
    channel(),
    reserved(),
    mode(),
    hw(),
    previousTriggerValue(),
    currentTriggerValue()
{
    objectType = ObjectType::MOST_TRIGGER;
}

void MostTrigger::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &reserved, sizeof(reserved));
    is.read((char *) &mode, sizeof(mode));
    is.read((char *) &hw, sizeof(hw));
    is.read((char *) &previousTriggerValue, sizeof(previousTriggerValue));
    is.read((char *) &currentTriggerValue, sizeof(currentTriggerValue));
}

void MostTrigger::write(AbstractFile & os)
{
    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &reserved, sizeof(reserved));
    os.write((char *) &mode, sizeof(mode));
    os.write((char *) &hw, sizeof(hw));
    os.write((char *) &previousTriggerValue, sizeof(previousTriggerValue));
    os.write((char *) &currentTriggerValue, sizeof(currentTriggerValue));
}

size_t MostTrigger::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reserved) +
        sizeof(mode) +
        sizeof(hw) +
        sizeof(previousTriggerValue) +
        sizeof(currentTriggerValue);

    return size;
}

}
}
