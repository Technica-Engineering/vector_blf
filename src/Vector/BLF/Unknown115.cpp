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

#include <Vector/BLF/Unknown115.h>

namespace Vector {
namespace BLF {

Unknown115::Unknown115() :
    ObjectHeader(ObjectType::Unknown115) {
}

void Unknown115::read(AbstractFile & is) {
    ObjectHeader::read(is);
    unknownData.resize(objectSize - ObjectHeader::calculateObjectSize());
    is.read(reinterpret_cast<char *>(unknownData.data()), unknownData.size());
}

void Unknown115::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(unknownData.data()), unknownData.size());
}

DWORD Unknown115::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        unknownData.size();
}

}
}
