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

#include <cstring>

namespace Vector {
namespace BLF {

Most150AllocTab::Most150AllocTab() :
    ObjectHeader2(),
    channel(),
    eventModeFlags(),
    freeBytes(),
    length(),
    tableData(nullptr)
{
}

Most150AllocTab::~Most150AllocTab()
{
    delete[] tableData;
    tableData = nullptr;
}

char * Most150AllocTab::read(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader2::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // eventModeFlags
    size = sizeof(eventModeFlags);
    memcpy((void *) &eventModeFlags, buffer, size);
    buffer += size;

    // freeBytes
    size = sizeof(freeBytes);
    memcpy((void *) &freeBytes, buffer, size);
    buffer += size;

    // length
    size = sizeof(length);
    memcpy((void *) &length, buffer, size);
    buffer += size;

    // tableData
    size = length;
    tableData = new char[size];
    memcpy((void *) tableData, buffer, size);
    buffer += size;

    return buffer;
}

char * Most150AllocTab::write(char * buffer)
{
    // @todo
}

size_t Most150AllocTab::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(eventModeFlags) +
        sizeof(freeBytes) +
        sizeof(length) +
        length;

    return size;
}

}
}
