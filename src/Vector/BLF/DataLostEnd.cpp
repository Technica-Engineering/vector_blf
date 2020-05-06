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

#include <Vector/BLF/DataLostEnd.h>

namespace Vector {
namespace BLF {

DataLostEnd::DataLostEnd() :
    ObjectHeader(ObjectType::DATA_LOST_END) {
}

void DataLostEnd::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&queueIdentifier), sizeof(queueIdentifier));
    is.read(reinterpret_cast<char *>(&firstObjectLostTimeStamp), sizeof(firstObjectLostTimeStamp));
    is.read(reinterpret_cast<char *>(&numberOfLostEvents), sizeof(numberOfLostEvents));
}

void DataLostEnd::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&queueIdentifier), sizeof(queueIdentifier));
    os.write(reinterpret_cast<char *>(&firstObjectLostTimeStamp), sizeof(firstObjectLostTimeStamp));
    os.write(reinterpret_cast<char *>(&numberOfLostEvents), sizeof(numberOfLostEvents));
}

DWORD DataLostEnd::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(queueIdentifier) +
        sizeof(firstObjectLostTimeStamp) +
        sizeof(numberOfLostEvents);
}

}
}
