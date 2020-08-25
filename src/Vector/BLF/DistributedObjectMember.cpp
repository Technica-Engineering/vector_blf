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

#include <Vector/BLF/DistributedObjectMember.h>

namespace Vector {
namespace BLF {

DistributedObjectMember::DistributedObjectMember() :
    ObjectHeader(ObjectType::DISTRIBUTED_OBJECT_MEMBER) {
}

void DistributedObjectMember::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&memberType), sizeof(memberType));
    is.read(reinterpret_cast<char *>(&detailType), sizeof(detailType));
    is.read(reinterpret_cast<char *>(&pathLength), sizeof(pathLength));
    is.read(reinterpret_cast<char *>(&dataLength), sizeof(dataLength));
    path.resize(pathLength);
    is.read(const_cast<char *>(path.data()), pathLength);
    data.resize(dataLength);
    is.read(reinterpret_cast<char *>(data.data()), dataLength);
}

void DistributedObjectMember::write(AbstractFile & os) {
    /* pre processing */
    pathLength = static_cast<uint32_t>(path.size());
    dataLength = static_cast<uint32_t>(data.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&memberType), sizeof(memberType));
    os.write(reinterpret_cast<char *>(&detailType), sizeof(detailType));
    os.write(reinterpret_cast<char *>(&pathLength), sizeof(pathLength));
    os.write(reinterpret_cast<char *>(&dataLength), sizeof(dataLength));
    os.write(const_cast<char *>(path.data()), pathLength);
    os.write(reinterpret_cast<char *>(data.data()), dataLength);
}

uint32_t DistributedObjectMember::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(memberType) +
        sizeof(detailType) +
        sizeof(pathLength) +
        sizeof(dataLength) +
        pathLength +
        dataLength;
}

}
}
