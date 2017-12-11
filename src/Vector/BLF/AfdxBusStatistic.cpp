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

#include <Vector/BLF/AfdxBusStatistic.h>

namespace Vector {
namespace BLF {

AfdxBusStatistic::AfdxBusStatistic() :
    ObjectHeader(),
    channel(),
    flags(),
    statDuration(),
    statRxPacketCountHW(),
    statTxPacketCountHW(),
    statRxErrorCountHW(),
    statTxErrorCountHW(),
    statRxBytesHW(),
    statTxBytesHW(),
    statRxPacketCount(),
    statTxPacketCount(),
    statDroppedPacketCount(),
    statInvalidPacketCount(),
    statLostPacketCount(),
    line(),
    linkStatus(),
    linkSpeed(),
    linkLost()
{
    objectType = ObjectType::A429_BUS_STATISTIC;
}

void AfdxBusStatistic::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    is.read(reinterpret_cast<char *>(&statDuration), sizeof(statDuration));
    is.read(reinterpret_cast<char *>(&statRxPacketCountHW), sizeof(statRxPacketCountHW));
    is.read(reinterpret_cast<char *>(&statTxPacketCountHW), sizeof(statTxPacketCountHW));
    is.read(reinterpret_cast<char *>(&statRxErrorCountHW), sizeof(statRxErrorCountHW));
    is.read(reinterpret_cast<char *>(&statTxErrorCountHW), sizeof(statTxErrorCountHW));
    is.read(reinterpret_cast<char *>(&statRxBytesHW), sizeof(statRxBytesHW));
    is.read(reinterpret_cast<char *>(&statTxBytesHW), sizeof(statTxBytesHW));
    is.read(reinterpret_cast<char *>(&statRxPacketCount), sizeof(statRxPacketCount));
    is.read(reinterpret_cast<char *>(&statTxPacketCount), sizeof(statTxPacketCount));
    is.read(reinterpret_cast<char *>(&statDroppedPacketCount), sizeof(statDroppedPacketCount));
    is.read(reinterpret_cast<char *>(&statInvalidPacketCount), sizeof(statInvalidPacketCount));
    is.read(reinterpret_cast<char *>(&statLostPacketCount), sizeof(statLostPacketCount));
    is.read(reinterpret_cast<char *>(&line), sizeof(line));
    is.read(reinterpret_cast<char *>(&linkStatus), sizeof(linkStatus));
    is.read(reinterpret_cast<char *>(&linkSpeed), sizeof(linkSpeed));
    is.read(reinterpret_cast<char *>(&linkLost), sizeof(linkLost));
}

void AfdxBusStatistic::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&flags), sizeof(flags));
    os.write(reinterpret_cast<char *>(&statDuration), sizeof(statDuration));
    os.write(reinterpret_cast<char *>(&statRxPacketCountHW), sizeof(statRxPacketCountHW));
    os.write(reinterpret_cast<char *>(&statTxPacketCountHW), sizeof(statTxPacketCountHW));
    os.write(reinterpret_cast<char *>(&statRxErrorCountHW), sizeof(statRxErrorCountHW));
    os.write(reinterpret_cast<char *>(&statTxErrorCountHW), sizeof(statTxErrorCountHW));
    os.write(reinterpret_cast<char *>(&statRxBytesHW), sizeof(statRxBytesHW));
    os.write(reinterpret_cast<char *>(&statTxBytesHW), sizeof(statTxBytesHW));
    os.write(reinterpret_cast<char *>(&statRxPacketCount), sizeof(statRxPacketCount));
    os.write(reinterpret_cast<char *>(&statTxPacketCount), sizeof(statTxPacketCount));
    os.write(reinterpret_cast<char *>(&statDroppedPacketCount), sizeof(statDroppedPacketCount));
    os.write(reinterpret_cast<char *>(&statInvalidPacketCount), sizeof(statInvalidPacketCount));
    os.write(reinterpret_cast<char *>(&statLostPacketCount), sizeof(statLostPacketCount));
    os.write(reinterpret_cast<char *>(&line), sizeof(line));
    os.write(reinterpret_cast<char *>(&linkStatus), sizeof(linkStatus));
    os.write(reinterpret_cast<char *>(&linkSpeed), sizeof(linkSpeed));
    os.write(reinterpret_cast<char *>(&linkLost), sizeof(linkLost));
}

DWORD AfdxBusStatistic::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(statDuration) +
        sizeof(statRxPacketCountHW) +
        sizeof(statTxPacketCountHW) +
        sizeof(statRxErrorCountHW) +
        sizeof(statTxErrorCountHW) +
        sizeof(statRxBytesHW) +
        sizeof(statTxBytesHW) +
        sizeof(statRxPacketCount) +
        sizeof(statTxPacketCount) +
        sizeof(statDroppedPacketCount) +
        sizeof(statInvalidPacketCount) +
        sizeof(statLostPacketCount) +
        sizeof(line) +
        sizeof(linkStatus) +
        sizeof(linkSpeed) +
        sizeof(linkLost);
}

}
}
