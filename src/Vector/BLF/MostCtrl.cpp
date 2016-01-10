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

#include "MostCtrl.h"

namespace Vector {
namespace BLF {

MostCtrl::MostCtrl() :
    ObjectHeader(),
    channel(),
    dir(),
    reserved1(),
    sourceAdr(),
    destAdr(),
    msg(),
    reserved2(),
    rTyp(),
    rTypAdr(),
    state(),
    reserved3(),
    ackNack(),
    reserved4()
{
    objectType = ObjectType::MOST_CTRL;
}

void MostCtrl::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &sourceAdr, sizeof(sourceAdr));
    is.read((char *) &destAdr, sizeof(destAdr));
    is.read((char *) msg.data(), msg.size());
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) &rTyp, sizeof(rTyp));
    is.read((char *) &rTypAdr, sizeof(rTypAdr));
    is.read((char *) &state, sizeof(state));
    is.read((char *) &reserved3, sizeof(reserved3));
    is.read((char *) &ackNack, sizeof(ackNack));
    is.read((char *) reserved4.data(), reserved4.size());
}

void MostCtrl::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &sourceAdr, sizeof(sourceAdr));
    os.write((char *) &destAdr, sizeof(destAdr));
    os.write((char *) msg.data(), msg.size());
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) &rTyp, sizeof(rTyp));
    os.write((char *) &rTypAdr, sizeof(rTypAdr));
    os.write((char *) &state, sizeof(state));
    os.write((char *) &reserved3, sizeof(reserved3));
    os.write((char *) &ackNack, sizeof(ackNack));
    os.write((char *) reserved4.data(), reserved4.size());
}

size_t MostCtrl::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reserved1) +
        sizeof(sourceAdr) +
        sizeof(destAdr) +
        msg.size() +
        sizeof(reserved2) +
        sizeof(rTyp) +
        sizeof(rTypAdr) +
        sizeof(state) +
        sizeof(reserved3) +
        sizeof(ackNack) +
        reserved4.size();

    return size;
}

}
}
