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

#include <cstring>

namespace Vector {
namespace BLF {

MostAllocTab::MostAllocTab() :
    ObjectHeader2(),
    channel(),
    length(),
    reserved(),
    tableData(nullptr)
{
    objectType = ObjectType::MOST_ALLOCTAB;
}

MostAllocTab::~MostAllocTab()
{
    delete[] tableData;
    tableData = nullptr;
}

char * MostAllocTab::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // length
    size = sizeof(length);
    memcpy((void *) &length, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // tableData
    size = length;
    tableData = new char[size];
    memcpy(tableData, buffer, size);
    buffer += size;

    return buffer;
}

char * MostAllocTab::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader2::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // length
    size = sizeof(length);
    memcpy(buffer, (void *) &length, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    // tableData
    size = length;
    memcpy(buffer, tableData, size);
    buffer += size;

    return buffer;
}

size_t MostAllocTab::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(length) +
        sizeof(reserved) +
        length;

    return size;
}

}
}
