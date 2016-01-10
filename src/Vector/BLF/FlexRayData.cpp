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

#include "FlexRayData.h"

namespace Vector {
namespace BLF {

FlexRayData::FlexRayData() :
    ObjectHeader(),
    channel(),
    mux(),
    len(),
    messageId(),
    crc(),
    dir(),
    reserved1(),
    reserved2(),
    dataBytes()
{
    objectType = ObjectType::FLEXRAY_DATA;
}

void FlexRayData::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &mux, sizeof(mux));
    is.read((char *) &len, sizeof(len));
    is.read((char *) &messageId, sizeof(messageId));
    is.read((char *) &crc, sizeof(crc));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) dataBytes.data(), dataBytes.size());
}

void FlexRayData::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &mux, sizeof(mux));
    os.write((char *) &len, sizeof(len));
    os.write((char *) &messageId, sizeof(messageId));
    os.write((char *) &crc, sizeof(crc));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) dataBytes.data(), dataBytes.size());
}

size_t FlexRayData::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(mux) +
        sizeof(len) +
        sizeof(messageId) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(reserved1) +
        sizeof(reserved2) +
        dataBytes.size();

    return size;
}

}
}
