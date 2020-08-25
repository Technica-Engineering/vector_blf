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

#include <Vector/BLF/Most150AllocTab.h>

namespace Vector {
namespace BLF {

Most150AllocTab::Most150AllocTab() :
    ObjectHeader2(ObjectType::MOST_150_ALLOCTAB) {
}

void Most150AllocTab::read(AbstractFile & is) {
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&eventModeFlags), sizeof(eventModeFlags));
    is.read(reinterpret_cast<char *>(&freeBytes), sizeof(freeBytes));
    is.read(reinterpret_cast<char *>(&length), sizeof(length));
    is.read(reinterpret_cast<char *>(&reservedMost150AllocTab), sizeof(reservedMost150AllocTab));
    tableData.resize(length);
    is.read(reinterpret_cast<char *>(tableData.data()), length);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void Most150AllocTab::write(AbstractFile & os) {
    /* pre processing */
    length = static_cast<uint16_t>(tableData.size());

    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&eventModeFlags), sizeof(eventModeFlags));
    os.write(reinterpret_cast<char *>(&freeBytes), sizeof(freeBytes));
    os.write(reinterpret_cast<char *>(&length), sizeof(length));
    os.write(reinterpret_cast<char *>(&reservedMost150AllocTab), sizeof(reservedMost150AllocTab));
    os.write(reinterpret_cast<char *>(tableData.data()), length);

    /* skip padding */
    os.skipp(objectSize % 4);
}

uint32_t Most150AllocTab::calculateObjectSize() const {
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(eventModeFlags) +
        sizeof(freeBytes) +
        sizeof(length) +
        sizeof(reservedMost150AllocTab) +
        length;
}

}
}
