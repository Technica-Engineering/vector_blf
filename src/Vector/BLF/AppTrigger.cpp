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

#include "AppTrigger.h"

namespace Vector {
namespace BLF {

AppTrigger::AppTrigger() :
    ObjectHeader(),
    preTriggerTime(),
    postTriggerTime(),
    channel(),
    flags(),
    appSpecific2()
{
    objectType = ObjectType::APP_TRIGGER;
}

void AppTrigger::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&preTriggerTime), sizeof(preTriggerTime));
    is.read(reinterpret_cast<char *>(&postTriggerTime), sizeof(postTriggerTime));
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&appSpecific2), sizeof(appSpecific2));
}

void AppTrigger::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&preTriggerTime), sizeof(preTriggerTime));
    os.write(reinterpret_cast<char *>(&postTriggerTime), sizeof(postTriggerTime));
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&appSpecific2), sizeof(appSpecific2));
}

DWORD AppTrigger::calculateObjectSize()
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(preTriggerTime) +
        sizeof(postTriggerTime) +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(appSpecific2);
}

}
}
