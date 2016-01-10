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

#include "MostAllocTab.h"

namespace Vector {
namespace BLF {

MostAllocTab::MostAllocTab() :
    ObjectHeader2(),
    channel(),
    length(),
    reserved(),
    tableData()
{
    objectType = ObjectType::MOST_ALLOCTAB;
}

void MostAllocTab::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &length, sizeof(length));
    is.read((char *) reserved.data(), reserved.size());
    tableData.resize(length);
    is.read((char *) tableData.data(), length);
}

void MostAllocTab::write(AbstractFile & os)
{
    /* pre processing */
    length = tableData.size();

    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &length, sizeof(length));
    os.write((char *) reserved.data(), reserved.size());
    os.write((char *) tableData.data(), length);
}

size_t MostAllocTab::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(length) +
        reserved.size() +
        length;

    return size;
}

}
}
