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

#include "EthernetFrame.h"

namespace Vector {
namespace BLF {

EthernetFrame::EthernetFrame() :
    ObjectHeader(),
    sourceAddress(),
    channel(),
    destinationAddress(),
    dir(),
    type(),
    tpid(),
    tci(),
    payLoadLength(),
    reserved(),
    payLoad()
{
    objectType = ObjectType::ETHERNET_FRAME;
}

void EthernetFrame::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(sourceAddress.data()), sourceAddress.size());
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(destinationAddress.data()), destinationAddress.size());
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&type), sizeof(type));
    is.read(reinterpret_cast<char *>(&tpid), sizeof(tpid));
    is.read(reinterpret_cast<char *>(&tci), sizeof(tci));
    is.read(reinterpret_cast<char *>(&payLoadLength), sizeof(payLoadLength));
    is.read(reinterpret_cast<char *>(reserved.data()), reserved.size());
    payLoad.resize(payLoadLength);
    is.read(reinterpret_cast<char *>(payLoad.data()), payLoadLength);
}

void EthernetFrame::write(AbstractFile & os)
{
    /* pre processing */
    payLoadLength = payLoad.size();

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(sourceAddress.data()), sourceAddress.size());
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(destinationAddress.data()), destinationAddress.size());
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&type), sizeof(type));
    os.write(reinterpret_cast<char *>(&tpid), sizeof(tpid));
    os.write(reinterpret_cast<char *>(&tci), sizeof(tci));
    os.write(reinterpret_cast<char *>(&payLoadLength), sizeof(payLoadLength));
    os.write(reinterpret_cast<char *>(reserved.data()), reserved.size());
    os.write(reinterpret_cast<char *>(payLoad.data()), payLoadLength);
}

DWORD EthernetFrame::calculateObjectSize()
{
    return
        ObjectHeader::calculateObjectSize() +
        sourceAddress.size() +
        sizeof(channel) +
        destinationAddress.size() +
        sizeof(dir) +
        sizeof(type) +
        sizeof(tpid) +
        sizeof(tci) +
        sizeof(payLoadLength) +
        reserved.size() +
        payLoadLength;
}

}
}
