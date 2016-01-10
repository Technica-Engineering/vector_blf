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

#include <cstring>

#include "EventComment.h"

namespace Vector {
namespace BLF {

EventComment::EventComment() :
    ObjectHeader(),
    commentedEventType(),
    textLength(),
    reserved(),
    text()
{
    objectType = ObjectType::EVENT_COMMENT;
}

void EventComment::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &commentedEventType, sizeof(commentedEventType));
    is.read((char *) &textLength, sizeof(textLength));
    is.read((char *) reserved.data(), reserved.size());
    text.resize(textLength);
    is.read((char *) text.data(), textLength);

    /* post processing */
    text.resize(strnlen(text.c_str(), textLength)); // Vector bug: the actual string can be shorter than size!
    objectSize = calculateObjectSize();
}

void EventComment::write(AbstractFile & os)
{
    /* pre processing */
    textLength = text.size();

    ObjectHeader::write(os);
    os.write((char *) &commentedEventType, sizeof(commentedEventType));
    os.write((char *) &textLength, sizeof(textLength));
    os.write((char *) reserved.data(), reserved.size());
    os.write((char *) text.data(), textLength);
}

size_t EventComment::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(commentedEventType) +
        sizeof(textLength) +
        reserved.size() +
        textLength;

    return size;
}

}
}
