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

#include <Vector/BLF/MostAllocTab.h>

namespace Vector {
namespace BLF {

MostAllocTab::MostAllocTab() :
    ObjectHeader2(ObjectType::MOST_ALLOCTAB) {
}

std::vector<uint8_t>::iterator MostAllocTab::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader2::fromData(it);

    channel =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    length =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    reservedMostAllocTab =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    tableData.resize(length);
    std::copy(it, it + tableData.size(), std::begin(tableData));
    it += tableData.size();

    return it;
}

void MostAllocTab::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    length = static_cast<DWORD>(tableData.size());

    ObjectHeader2::toData(data);

    data.push_back((channel >>  0) & 0xff);
    data.push_back((channel >>  8) & 0xff);
    data.push_back((length >>  0) & 0xff);
    data.push_back((length >>  8) & 0xff);
    data.push_back((reservedMostAllocTab >>  0) & 0xff);
    data.push_back((reservedMostAllocTab >>  8) & 0xff);
    data.push_back((reservedMostAllocTab >> 16) & 0xff);
    data.push_back((reservedMostAllocTab >> 24) & 0xff);
    data.insert(std::end(data), std::begin(tableData), std::end(tableData));
}

DWORD MostAllocTab::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(length) +
        sizeof(reservedMostAllocTab) +
        length;
}

}
}
