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

#include "MostDataLost.h"

namespace Vector {
namespace BLF {

MostDataLost::MostDataLost() :
    ObjectHeader2(),
    channel(),
    reserved(),
    info(),
    lostMsgsCtrl(),
    lostMsgsAsync(),
    lastGoodTimeStampNs(),
    nextGoodTimeStampNs()
{
    objectType = ObjectType::MOST_DATALOST;
}

void MostDataLost::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &reserved, sizeof(reserved));
    is.read((char *) &info, sizeof(info));
    is.read((char *) &lostMsgsCtrl, sizeof(lostMsgsCtrl));
    is.read((char *) &lostMsgsAsync, sizeof(lostMsgsAsync));
    is.read((char *) &lastGoodTimeStampNs, sizeof(lastGoodTimeStampNs));
    is.read((char *) &nextGoodTimeStampNs, sizeof(nextGoodTimeStampNs));
}

void MostDataLost::write(AbstractFile & os)
{
    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &reserved, sizeof(reserved));
    os.write((char *) &info, sizeof(info));
    os.write((char *) &lostMsgsCtrl, sizeof(lostMsgsCtrl));
    os.write((char *) &lostMsgsAsync, sizeof(lostMsgsAsync));
    os.write((char *) &lastGoodTimeStampNs, sizeof(lastGoodTimeStampNs));
    os.write((char *) &nextGoodTimeStampNs, sizeof(nextGoodTimeStampNs));
}

size_t MostDataLost::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reserved) +
        sizeof(info) +
        sizeof(lostMsgsCtrl) +
        sizeof(lostMsgsAsync) +
        sizeof(lastGoodTimeStampNs) +
        sizeof(nextGoodTimeStampNs);

    return size;
}

}
}
