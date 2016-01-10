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
    is.read((char *) sourceAddress.data(), sourceAddress.size());
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) destinationAddress.data(), destinationAddress.size());
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &type, sizeof(type));
    is.read((char *) &tpid, sizeof(tpid));
    is.read((char *) &tci, sizeof(tci));
    is.read((char *) &payLoadLength, sizeof(payLoadLength));
    is.read((char *) reserved.data(), reserved.size());
    payLoad.resize(payLoadLength);
    is.read((char *) payLoad.data(), payLoadLength);
}

void EthernetFrame::write(AbstractFile & os)
{
    /* pre processing */
    payLoadLength = payLoad.size();

    ObjectHeader::write(os);
    os.write((char *) sourceAddress.data(), sourceAddress.size());
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) destinationAddress.data(), destinationAddress.size());
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &type, sizeof(type));
    os.write((char *) &tpid, sizeof(tpid));
    os.write((char *) &tci, sizeof(tci));
    os.write((char *) &payLoadLength, sizeof(payLoadLength));
    os.write((char *) reserved.data(), reserved.size());
    os.write((char *) payLoad.data(), payLoadLength);
}

size_t EthernetFrame::calculateObjectSize()
{
    size_t size =
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

    return size;
}

}
}
