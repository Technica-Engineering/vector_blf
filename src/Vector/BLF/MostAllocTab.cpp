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

#include <Vector/BLF/MostAllocTab.h>

namespace Vector {
namespace BLF {

MostAllocTab::MostAllocTab() :
    ObjectHeader2(),
    channel(),
    length(),
    reservedMostAllocTab(),
    tableData()
{
    objectType = ObjectType::MOST_ALLOCTAB;
}

void MostAllocTab::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&length), sizeof(length));
    is.read(reinterpret_cast<char *>(&reservedMostAllocTab), sizeof(reservedMostAllocTab));
    tableData.resize(length);
    is.read(reinterpret_cast<char *>(tableData.data()), length);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void MostAllocTab::write(AbstractFile & os)
{
    /* pre processing */
    length = static_cast<WORD>(tableData.size());

    ObjectHeader2::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&length), sizeof(length));
    os.write(reinterpret_cast<char *>(&reservedMostAllocTab), sizeof(reservedMostAllocTab));
    os.write(reinterpret_cast<char *>(tableData.data()), length);

    /* skip padding */
    os.skipp(objectSize % 4);
}

DWORD MostAllocTab::calculateObjectSize() const
{
    return
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(length) +
        sizeof(reservedMostAllocTab) +
        length;
}

}
}
