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
    frameData()
{
    objectType = ObjectType::WLAN_FRAME;
}

void WlanFrame::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &radioChannel, sizeof(radioChannel));
    is.read((char *) &signalStrength, sizeof(signalStrength));
    is.read((char *) &signalQuality, sizeof(signalQuality));
    is.read((char *) &frameLength, sizeof(frameLength));
    frameData.resize(frameLength);
    is.read((char *) frameData.data(), frameLength);
}

void WlanFrame::write(AbstractFile & os)
{
    /* pre processing */
    frameLength = frameData.size();

    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &radioChannel, sizeof(radioChannel));
    os.write((char *) &signalStrength, sizeof(signalStrength));
    os.write((char *) &signalQuality, sizeof(signalQuality));
    os.write((char *) &frameLength, sizeof(frameLength));
    os.write((char *) frameData.data(), frameLength);
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
