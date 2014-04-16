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

#include "EthernetRxError.h"

#include <cstring>

namespace Vector {
namespace BLF {

EthernetRxError::EthernetRxError() :
    ObjectHeader(),
    structLength(),
    channel(),
    dir(),
    fcs(),
    frameDataLength(),
    error(),
    frameData(nullptr)
{
}

EthernetRxError::~EthernetRxError()
{
    delete[] frameData;
    frameData = nullptr;
}

char * EthernetRxError::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // structLength
    size = sizeof(structLength);
    memcpy((char *) &structLength, buffer, size);
    buffer += size;

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // fcs
    size = sizeof(fcs);
    memcpy((char *) &fcs, buffer, size);
    buffer += size;

    // frameDataLength
    size = sizeof(frameDataLength);
    memcpy((char *) &frameDataLength, buffer, size);
    buffer += size;

    // error
    size = sizeof(error);
    memcpy((char *) &error, buffer, size);
    buffer += size;

    // frameData
    size = frameDataLength;
    frameData = new char[frameDataLength];
    memcpy(frameData, buffer, size);
    buffer += size;

    return buffer;
}

size_t EthernetRxError::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(structLength) +
            sizeof(channel) +
            sizeof(dir) +
            sizeof(fcs) +
            sizeof(frameDataLength) +
            sizeof(error) +
            frameDataLength;

    return size;
}

}
}
