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

#include "EventComment.h"

#include <cstring>

namespace Vector {
namespace BLF {

EventComment::EventComment() :
    ObjectHeader(),
    commentedEventType(),
    textLength(),
    reserved(),
    text(nullptr)
{
}

EventComment::~EventComment()
{
    delete[] text;
    text = nullptr;
}

char * EventComment::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // commentedEventType
    size = sizeof(commentedEventType);
    memcpy((char *) &commentedEventType, buffer, size);
    buffer += size;

    // textLength
    size = sizeof(textLength);
    memcpy((char *) &textLength, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((char *) &reserved, buffer, size);
    buffer += size;

    // text
    size = textLength;
    text = new char[textLength + 1];
    text[textLength] = 0;
    memcpy(text, buffer, size);
    buffer += size;

    return buffer;
}

size_t EventComment::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(commentedEventType) +
            sizeof(textLength) +
            sizeof(reserved) +
            textLength;

    return size;
}

}
}
