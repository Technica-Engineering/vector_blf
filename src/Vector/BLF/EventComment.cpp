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

#include <cstring>

#include <Vector/BLF/EventComment.h>

namespace Vector {
namespace BLF {

EventComment::EventComment() :
    ObjectHeader(ObjectType::EVENT_COMMENT) {
}

void EventComment::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&commentedEventType), sizeof(commentedEventType));
    is.read(reinterpret_cast<char *>(&textLength), sizeof(textLength));
    is.read(reinterpret_cast<char *>(&reservedEventComment), sizeof(reservedEventComment));
    text.resize(textLength);
    is.read(const_cast<char *>(text.data()), textLength);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void EventComment::write(AbstractFile & os) {
    /* pre processing */
    textLength = static_cast<uint32_t>(text.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&commentedEventType), sizeof(commentedEventType));
    os.write(reinterpret_cast<char *>(&textLength), sizeof(textLength));
    os.write(reinterpret_cast<char *>(&reservedEventComment), sizeof(reservedEventComment));
    os.write(const_cast<char *>(text.data()), textLength);

    /* skip padding */
    os.skipp(objectSize % 4);
}

uint32_t EventComment::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(commentedEventType) +
        sizeof(textLength) +
        sizeof(reservedEventComment) +
        textLength;
}

}
}
