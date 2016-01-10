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

namespace Vector {
namespace BLF {

EthernetRxError::EthernetRxError() :
    ObjectHeader(),
    structLength(),
    channel(),
    dir(),
    reserved1(),
    fcs(),
    frameDataLength(),
    reserved2(),
    error(),
    frameData()
{
    objectType = ObjectType::ETHERNET_RX_ERROR;
}

void EthernetRxError::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &structLength, sizeof(structLength));
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) reserved1.data(), reserved1.size());
    is.read((char *) &fcs, sizeof(fcs));
    is.read((char *) &frameDataLength, sizeof(frameDataLength));
    is.read((char *) reserved2.data(), reserved2.size());
    is.read((char *) &error, sizeof(error));
    frameData.resize(frameDataLength);
    is.read((char *) frameData.data(), frameDataLength);
}

void EthernetRxError::write(AbstractFile & os)
{
    /* pre processing */
    frameDataLength = frameData.size();

    ObjectHeader::write(os);
    os.write((char *) &structLength, sizeof(structLength));
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) reserved1.data(), reserved1.size());
    os.write((char *) &fcs, sizeof(fcs));
    os.write((char *) &frameDataLength, sizeof(frameDataLength));
    os.write((char *) reserved2.data(), reserved2.size());
    os.write((char *) &error, sizeof(error));
    os.write((char *) frameData.data(), frameDataLength);
}

size_t EthernetRxError::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(structLength) +
        sizeof(channel) +
        sizeof(dir) +
        reserved1.size() +
        sizeof(fcs) +
        sizeof(frameDataLength) +
        reserved2.size() +
        sizeof(error) +
        frameDataLength;

    return size;
}

}
}
