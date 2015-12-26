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

char * WlanFrame::read(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::read(buffer);

    // channel
    size = sizeof(channel);
    memcpy((void *) &channel, buffer, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy((void *) &flags, buffer, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy((void *) &dir, buffer, size);
    buffer += size;

    // radioChannel
    size = sizeof(radioChannel);
    memcpy((void *) &radioChannel, buffer, size);
    buffer += size;

    // signalStrength
    size = sizeof(signalStrength);
    memcpy((void *) &signalStrength, buffer, size);
    buffer += size;

    // signalQuality
    size = sizeof(signalQuality);
    memcpy((void *) &signalQuality, buffer, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy((void *) &frameLength, buffer, size);
    buffer += size;

    // frameData
    size = frameLength;
    frameData = new char[size];
    memcpy(frameData, buffer, size);
    buffer += size;

    return buffer;
}

char * WlanFrame::write(char * buffer)
{
    size_t size;

    // preceding data
    buffer = ObjectHeader::write(buffer);

    // channel
    size = sizeof(channel);
    memcpy(buffer, (void *) &channel, size);
    buffer += size;

    // flags
    size = sizeof(flags);
    memcpy(buffer, (void *) &flags, size);
    buffer += size;

    // dir
    size = sizeof(dir);
    memcpy(buffer, (void *) &dir, size);
    buffer += size;

    // radioChannel
    size = sizeof(radioChannel);
    memcpy(buffer, (void *) &radioChannel, size);
    buffer += size;

    // signalStrength
    size = sizeof(signalStrength);
    memcpy(buffer, (void *) &signalStrength, size);
    buffer += size;

    // signalQuality
    size = sizeof(signalQuality);
    memcpy(buffer, (void *) &signalQuality, size);
    buffer += size;

    // frameLength
    size = sizeof(frameLength);
    memcpy(buffer, (void *) &frameLength, size);
    buffer += size;

    // frameData
    size = frameLength;
    frameData = new char[size];
    memcpy(buffer, frameData, size);
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
