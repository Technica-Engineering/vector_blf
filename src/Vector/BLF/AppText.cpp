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

#include <Vector/BLF/AppText.h>

namespace Vector {
namespace BLF {

AppText::AppText() :
    ObjectHeader(ObjectType::APP_TEXT) {
}

std::vector<uint8_t>::iterator AppText::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    source =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    reservedAppText1 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    textLength =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    reservedAppText2 =
        (static_cast<DWORD>(*it++) <<  0) |
        (static_cast<DWORD>(*it++) <<  8) |
        (static_cast<DWORD>(*it++) << 16) |
        (static_cast<DWORD>(*it++) << 24);
    text.assign(it, it + textLength);
    it += textLength;

    return it;
}

void AppText::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    textLength = static_cast<DWORD>(text.size());

    ObjectHeader::toData(data);

    data.push_back((source >>  0) & 0xff);
    data.push_back((source >>  8) & 0xff);
    data.push_back((source >> 16) & 0xff);
    data.push_back((source >> 24) & 0xff);
    data.push_back((reservedAppText1 >>  0) & 0xff);
    data.push_back((reservedAppText1 >>  8) & 0xff);
    data.push_back((reservedAppText1 >> 16) & 0xff);
    data.push_back((reservedAppText1 >> 24) & 0xff);
    data.push_back((textLength >>  0) & 0xff);
    data.push_back((textLength >>  8) & 0xff);
    data.push_back((textLength >> 16) & 0xff);
    data.push_back((textLength >> 24) & 0xff);
    data.push_back((reservedAppText2 >>  0) & 0xff);
    data.push_back((reservedAppText2 >>  8) & 0xff);
    data.push_back((reservedAppText2 >> 16) & 0xff);
    data.push_back((reservedAppText2 >> 24) & 0xff);
    data.insert(std::end(data), std::begin(text), std::end(text));
}

DWORD AppText::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(source) +
        sizeof(reservedAppText1) +
        sizeof(textLength) +
        sizeof(reservedAppText2) +
        textLength;
}

}
}
