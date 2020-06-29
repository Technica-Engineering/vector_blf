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

#include <Vector/BLF/LinMessageDescriptor.h>

namespace Vector {
namespace BLF {

std::vector<uint8_t>::iterator LinMessageDescriptor::fromData(std::vector<uint8_t>::iterator it) {
    it = LinSynchFieldEvent::fromData(it);

    supplierId =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    messageId =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    nad =
            (static_cast<BYTE>(*it++) <<  0);
    id =
            (static_cast<BYTE>(*it++) <<  0);
    dlc =
            (static_cast<BYTE>(*it++) <<  0);
    checksumModel =
            (static_cast<BYTE>(*it++) <<  0);

    return it;
}

void LinMessageDescriptor::toData(std::vector<uint8_t> & data) {
    LinSynchFieldEvent::toData(data);

    data.push_back((supplierId >>  0) & 0xff);
    data.push_back((supplierId >>  8) & 0xff);
    data.push_back((messageId >>  0) & 0xff);
    data.push_back((messageId >>  8) & 0xff);
    data.push_back((nad >>  0) & 0xff);
    data.push_back((id >>  0) & 0xff);
    data.push_back((dlc >>  0) & 0xff);
    data.push_back((checksumModel >>  0) & 0xff);
}

DWORD LinMessageDescriptor::calculateObjectSize() const {
    return
        LinSynchFieldEvent::calculateObjectSize() +
        sizeof(supplierId) +
        sizeof(messageId) +
        sizeof(nad) +
        sizeof(id) +
        sizeof(dlc) +
        sizeof(checksumModel);
}

}
}
