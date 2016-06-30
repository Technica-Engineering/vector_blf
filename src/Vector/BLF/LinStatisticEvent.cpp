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

#include "LinStatisticEvent.h"

namespace Vector {
namespace BLF {

LinStatisticEvent::LinStatisticEvent() :
    ObjectHeader(),
    channel(),
    reserved1(),
    busLoad(),
    burstsTotal(),
    burstsOverrun(),
    framesSent(),
    framesReceived(),
    framesUnanswered(),
    reserved2()
{
    objectType = ObjectType::LIN_STATISTIC;
}

void LinStatisticEvent::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(reserved1.data()), reserved1.size());
    is.read(reinterpret_cast<char *>(&busLoad), sizeof(busLoad));
    is.read(reinterpret_cast<char *>(&burstsTotal), sizeof(burstsTotal));
    is.read(reinterpret_cast<char *>(&burstsOverrun), sizeof(burstsOverrun));
    is.read(reinterpret_cast<char *>(&framesSent), sizeof(framesSent));
    is.read(reinterpret_cast<char *>(&framesReceived), sizeof(framesReceived));
    is.read(reinterpret_cast<char *>(&framesUnanswered), sizeof(framesUnanswered));
    is.read(reinterpret_cast<char *>(reserved2.data()), reserved2.size());
}

void LinStatisticEvent::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(reserved1.data()), reserved1.size());
    os.write(reinterpret_cast<char *>(&busLoad), sizeof(busLoad));
    os.write(reinterpret_cast<char *>(&burstsTotal), sizeof(burstsTotal));
    os.write(reinterpret_cast<char *>(&burstsOverrun), sizeof(burstsOverrun));
    os.write(reinterpret_cast<char *>(&framesSent), sizeof(framesSent));
    os.write(reinterpret_cast<char *>(&framesReceived), sizeof(framesReceived));
    os.write(reinterpret_cast<char *>(&framesUnanswered), sizeof(framesUnanswered));
    os.write(reinterpret_cast<char *>(reserved2.data()), reserved2.size());
}

DWORD LinStatisticEvent::calculateObjectSize()
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        reserved1.size() +
        sizeof(busLoad) +
        sizeof(burstsTotal) +
        sizeof(burstsOverrun) +
        sizeof(framesSent) +
        sizeof(framesReceived) +
        sizeof(framesUnanswered) +
        reserved2.size();
}

}
}
