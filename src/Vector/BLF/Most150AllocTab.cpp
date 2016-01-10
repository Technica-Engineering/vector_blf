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

#include "Most150AllocTab.h"

namespace Vector {
namespace BLF {

Most150AllocTab::Most150AllocTab() :
    ObjectHeader2(),
    channel(),
    eventModeFlags(),
    freeBytes(),
    length(),
    tableData()
{
    objectType = ObjectType::MOST_150_ALLOCTAB;
}

void Most150AllocTab::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &eventModeFlags, sizeof(eventModeFlags));
    is.read((char *) &freeBytes, sizeof(freeBytes));
    is.read((char *) &length, sizeof(length));
    tableData.resize(length);
    is.read((char *) tableData.data(), length * sizeof(WORD));
}

void Most150AllocTab::write(AbstractFile & os)
{
    /* pre processing */
    length = tableData.size();

    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &eventModeFlags, sizeof(eventModeFlags));
    os.write((char *) &freeBytes, sizeof(freeBytes));
    os.write((char *) &length, sizeof(length));
    os.write((char *) tableData.data(), length * sizeof(WORD));
}

size_t Most150AllocTab::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(eventModeFlags) +
        sizeof(freeBytes) +
        sizeof(length) +
        length * sizeof(WORD);

    return size;
}

}
}
