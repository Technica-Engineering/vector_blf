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

#include "EthernetStatistic.h"

namespace Vector {
namespace BLF {

EthernetStatistic::EthernetStatistic() :
    ObjectHeader(),
    channel(),
    rcvOk_HW(),
    xmitOk_HW(),
    rcvError_HW(),
    xmitError_HW(),
    rcvBytes_HW(),
    xmitBytes_HW(),
    rcvNoBuffer_HW(),
    sqi(),
    hardwareChannel()
{
    objectType = ObjectType::ETHERNET_STATISTIC;
}

void EthernetStatistic::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&rcvOk_HW), sizeof(rcvOk_HW));
    is.read(reinterpret_cast<char *>(&xmitOk_HW), sizeof(xmitOk_HW));
    is.read(reinterpret_cast<char *>(&rcvError_HW), sizeof(rcvError_HW));
    is.read(reinterpret_cast<char *>(&xmitError_HW), sizeof(xmitError_HW));
    is.read(reinterpret_cast<char *>(&rcvBytes_HW), sizeof(rcvBytes_HW));
    is.read(reinterpret_cast<char *>(&xmitBytes_HW), sizeof(xmitBytes_HW));
    is.read(reinterpret_cast<char *>(&rcvNoBuffer_HW), sizeof(rcvNoBuffer_HW));
    is.read(reinterpret_cast<char *>(&sqi), sizeof(sqi));
    is.read(reinterpret_cast<char *>(&hardwareChannel), sizeof(hardwareChannel));
}

void EthernetStatistic::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&rcvOk_HW), sizeof(rcvOk_HW));
    os.write(reinterpret_cast<char *>(&xmitOk_HW), sizeof(xmitOk_HW));
    os.write(reinterpret_cast<char *>(&rcvError_HW), sizeof(rcvError_HW));
    os.write(reinterpret_cast<char *>(&xmitError_HW), sizeof(xmitError_HW));
    os.write(reinterpret_cast<char *>(&rcvBytes_HW), sizeof(rcvBytes_HW));
    os.write(reinterpret_cast<char *>(&xmitBytes_HW), sizeof(xmitBytes_HW));
    os.write(reinterpret_cast<char *>(&rcvNoBuffer_HW), sizeof(rcvNoBuffer_HW));
    os.write(reinterpret_cast<char *>(&sqi), sizeof(sqi));
    os.write(reinterpret_cast<char *>(&hardwareChannel), sizeof(hardwareChannel));
}

DWORD EthernetStatistic::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(rcvOk_HW) +
        sizeof(xmitOk_HW) +
        sizeof(rcvError_HW) +
        sizeof(xmitError_HW) +
        sizeof(rcvBytes_HW) +
        sizeof(xmitBytes_HW) +
        sizeof(rcvNoBuffer_HW) +
        sizeof(sqi) +
        sizeof(hardwareChannel);
}

}
}
