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

#include "WlanFrame.h"

#include <cstring>

namespace Vector {
namespace BLF {

WlanFrame::WlanFrame() :
    ObjectHeader(),
    channel(),
    flags(),
    dir(),
    radioChannel(),
    signalStrength(),
    signalQuality(),
    frameLength(),
    frameData(nullptr)
{
}

WlanFrame::~WlanFrame()
{
    delete[] frameData;
    frameData = nullptr;
}

char * WlanFrame::parse(char * buffer)
{
    size_t size;

    // previous data
    buffer = ObjectHeader::parse(buffer);

    // channel
    size = sizeof(channel);
    memcpy((char *) &channel, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((char *) &flags, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((char *) &dir, buffer, size);
    buffer += size;

    // radioChannel
    size = sizeof(radioChannel);
    memcpy((char *) &radioChannel, buffer, size);
    buffer += size;

    // signalStrength
    size = sizeof(signalStrength);
    memcpy((char *) &signalStrength, buffer, size);
    buffer += size;

    // signalQuality
    size = sizeof(signalQuality);
    memcpy((char *) &signalQuality, buffer, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy((char *) &frameLength, buffer, size);
    buffer += size;

    // frameData
    size = sizeof(frameLength);
    frameData = new uint8_t[frameLength];
    memcpy(frameData, buffer, size);
    buffer += size;

    return buffer;
}

size_t WlanFrame::calculateObjectSize()
{
    size_t size =
            ObjectHeader::calculateObjectSize() +
            sizeof(channel) +
            sizeof(flags) +
            sizeof(dir) +
            sizeof(radioChannel) +
            sizeof(signalStrength) +
            sizeof(signalQuality) +
            sizeof(frameLength) +
            frameLength;

    return size;
}

}
}
