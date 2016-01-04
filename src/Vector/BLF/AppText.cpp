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

#include "AppText.h"

#include <cstring>

namespace Vector {
namespace BLF {

AppText::AppText() :
    ObjectHeader(),
    source(),
    reserved(),
    textLength(),
    text()
{
    objectType = ObjectType::APP_TEXT;
}

AppText::~AppText()
{
}

char * AppText::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // source
    size = sizeof(source);
    memcpy((void *) &source, buffer, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy((void *) &reserved, buffer, size);
    buffer += size;

    // textLength
    size = sizeof(textLength);
    memcpy((void *) &textLength, buffer, size);
    buffer += size;

    // text
    size = textLength;
    text.assign(buffer, size);
    buffer += size;

    return buffer;
}

char * AppText::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // source
    size = sizeof(source);
    memcpy(buffer, (void *) &source, size);
    buffer += size;

    // reserved
    size = sizeof(reserved);
    memcpy(buffer, (void *) &reserved, size);
    buffer += size;

    // textLength
    size = sizeof(textLength);
    memcpy(buffer, (void *) &textLength, size);
    buffer += size;

    // text
    size = textLength;
    memcpy(buffer, text.data(), size);
    buffer += size;

    return buffer;
}

size_t AppText::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(source) +
        sizeof(reserved) +
        sizeof(textLength) +
        textLength;

    return size;
}

}
}
