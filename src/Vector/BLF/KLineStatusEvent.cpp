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

#include <Vector/BLF/KLineStatusEvent.h>

namespace Vector {
namespace BLF {

KLineStatusEvent::KLineStatusEvent() :
    ObjectHeader(ObjectType::KLINE_STATUSEVENT) {
}

void KLineStatusEvent::read(RawFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&type), sizeof(type));
    is.read(reinterpret_cast<char *>(&dataLen), sizeof(dataLen));
    is.read(reinterpret_cast<char *>(&port), sizeof(port));
    is.read(reinterpret_cast<char *>(&reservedKLineStatusEvent), sizeof(reservedKLineStatusEvent));
    is.read(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size() * sizeof(UINT64)));
    // @note might be extended in future versions
}

void KLineStatusEvent::write(RawFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&type), sizeof(type));
    os.write(reinterpret_cast<char *>(&dataLen), sizeof(dataLen));
    os.write(reinterpret_cast<char *>(&port), sizeof(port));
    os.write(reinterpret_cast<char *>(&reservedKLineStatusEvent), sizeof(reservedKLineStatusEvent));
    os.write(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size() * sizeof(UINT64)));
}

DWORD KLineStatusEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(type) +
        sizeof(dataLen) +
        sizeof(port) +
        sizeof(reservedKLineStatusEvent) +
        static_cast<DWORD>(data.size() * sizeof(UINT64));
}

}
}
