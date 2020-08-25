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

#include <Vector/BLF/CanOverloadFrame.h>

namespace Vector {
namespace BLF {

CanOverloadFrame::CanOverloadFrame() :
    ObjectHeader(ObjectType::CAN_OVERLOAD) {
}

void CanOverloadFrame::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&reservedCanOverloadFrame1), sizeof(reservedCanOverloadFrame1));
    is.read(reinterpret_cast<char *>(&reservedCanOverloadFrame2), sizeof(reservedCanOverloadFrame2));
}

void CanOverloadFrame::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&reservedCanOverloadFrame1), sizeof(reservedCanOverloadFrame1));
    os.write(reinterpret_cast<char *>(&reservedCanOverloadFrame2), sizeof(reservedCanOverloadFrame2));
}

DWORD CanOverloadFrame::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reservedCanOverloadFrame1) +
        sizeof(reservedCanOverloadFrame2);
}

}
}
