/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/EthernetStatus.h>

namespace Vector {
namespace BLF {

EthernetStatus::EthernetStatus() :
    ObjectHeader(ObjectType::ETHERNET_STATUS) {
}

std::vector<uint8_t>::iterator EthernetStatus::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    channel =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    flags =
        (static_cast<WORD>(*it++) <<  0) |
        (static_cast<WORD>(*it++) <<  8);
    linkStatus =
        (static_cast<BYTE>(*it++) <<  0);
    ethernetPhy =
        (static_cast<BYTE>(*it++) <<  0);
    duplex =
        (static_cast<BYTE>(*it++) <<  0);
    mdi =
        (static_cast<BYTE>(*it++) <<  0);
    connector =
        (static_cast<BYTE>(*it++) <<  0);
    clockMode =
        (static_cast<BYTE>(*it++) <<  0);
    pairs =
        (static_cast<BYTE>(*it++) <<  0);
    hardwareChannel =
        (static_cast<BYTE>(*it++) <<  0);
    bitrate =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);

    return it;
}

void EthernetStatus::toData(std::vector<uint8_t> & data) {
    ObjectHeader::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((flags >>  0) & 0xff);
    data.push_back((flags >>  8) & 0xff);
    data.push_back((linkStatus >>  0) & 0xff);
    data.push_back((ethernetPhy >>  0) & 0xff);
    data.push_back((duplex >>  0) & 0xff);
    data.push_back((mdi >>  0) & 0xff);
    data.push_back((connector >>  0) & 0xff);
    data.push_back((clockMode >>  0) & 0xff);
    data.push_back((pairs >>  0) & 0xff);
    data.push_back((hardwareChannel >>  0) & 0xff);
    data.push_back((bitrate >>  0) & 0xff);
    data.push_back((bitrate >>  8) & 0xff);
    data.push_back((bitrate >> 16) & 0xff);
    data.push_back((bitrate >> 24) & 0xff);
}

DWORD EthernetStatus::calculateObjectSize() const {
    return
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
        sizeof(hardwareChannel) +
        sizeof(bitrate);
}

}
}
