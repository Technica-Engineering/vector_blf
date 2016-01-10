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

#include "EthernetStatus.h"

namespace Vector {
namespace BLF {

EthernetStatus::EthernetStatus() :
    ObjectHeader(),
    channel(),
    flags(),
    linkStatus(),
    ethernetPhy(),
    duplex(),
    mdi(),
    connector(),
    clockMode(),
    pairs(),
    reserved(),
    bitrate()
{
    objectType = ObjectType::ETHERNET_STATUS;
}

void EthernetStatus::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &linkStatus, sizeof(linkStatus));
    is.read((char *) &ethernetPhy, sizeof(ethernetPhy));
    is.read((char *) &duplex, sizeof(duplex));
    is.read((char *) &mdi, sizeof(mdi));
    is.read((char *) &connector, sizeof(connector));
    is.read((char *) &clockMode, sizeof(clockMode));
    is.read((char *) &pairs, sizeof(pairs));
    is.read((char *) &reserved, sizeof(reserved));
    is.read((char *) &bitrate, sizeof(bitrate));
}

void EthernetStatus::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &linkStatus, sizeof(linkStatus));
    os.write((char *) &ethernetPhy, sizeof(ethernetPhy));
    os.write((char *) &duplex, sizeof(duplex));
    os.write((char *) &mdi, sizeof(mdi));
    os.write((char *) &connector, sizeof(connector));
    os.write((char *) &clockMode, sizeof(clockMode));
    os.write((char *) &pairs, sizeof(pairs));
    os.write((char *) &reserved, sizeof(reserved));
    os.write((char *) &bitrate, sizeof(bitrate));
}

size_t EthernetStatus::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(linkStatus) +
        sizeof(ethernetPhy) +
        sizeof(duplex) +
        sizeof(mdi) +
        sizeof(connector) +
        sizeof(clockMode) +
        sizeof(pairs) +
        sizeof(reserved) +
        sizeof(bitrate);

    return size;
}

}
}
