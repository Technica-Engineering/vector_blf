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

#include <Vector/BLF/A429Message.h>

namespace Vector {
namespace BLF {

A429Message::A429Message() :
    ObjectHeader(),
    a429Data(),
    channel(),
    dir(),
    reserved1(),
    bitrate(),
    errReason(),
    errPosition(),
    reserved2(),
    reserved3(),
    frameGap(),
    frameLength(),
    msgCtrl(),
    reserved4(),
    cycleTime(),
    error(),
    bitLenOfLastBit(),
    reserved5()
{
    objectType = ObjectType::A429_MESSAGE;
}

void A429Message::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(a429Data.data()), static_cast<std::streamsize>(a429Data.size()));
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&bitrate), sizeof(bitrate));
    is.read(reinterpret_cast<char *>(&errReason), sizeof(errReason));
    is.read(reinterpret_cast<char *>(&errPosition), sizeof(errPosition));
    is.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    is.read(reinterpret_cast<char *>(&reserved3), sizeof(reserved3));
    is.read(reinterpret_cast<char *>(&frameGap), sizeof(frameGap));
    is.read(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    is.read(reinterpret_cast<char *>(&msgCtrl), sizeof(msgCtrl));
    is.read(reinterpret_cast<char *>(&reserved4), sizeof(reserved4));
    is.read(reinterpret_cast<char *>(&cycleTime), sizeof(cycleTime));
    is.read(reinterpret_cast<char *>(&error), sizeof(error));
    is.read(reinterpret_cast<char *>(&bitLenOfLastBit), sizeof(bitLenOfLastBit));
    is.read(reinterpret_cast<char *>(&reserved5), sizeof(reserved5));
}

void A429Message::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(a429Data.data()), static_cast<std::streamsize>(a429Data.size()));
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&bitrate), sizeof(bitrate));
    os.write(reinterpret_cast<char *>(&errReason), sizeof(errReason));
    os.write(reinterpret_cast<char *>(&errPosition), sizeof(errPosition));
    os.write(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    os.write(reinterpret_cast<char *>(&reserved3), sizeof(reserved3));
    os.write(reinterpret_cast<char *>(&frameGap), sizeof(frameGap));
    os.write(reinterpret_cast<char *>(&frameLength), sizeof(frameLength));
    os.write(reinterpret_cast<char *>(&msgCtrl), sizeof(msgCtrl));
    os.write(reinterpret_cast<char *>(&reserved4), sizeof(reserved4));
    os.write(reinterpret_cast<char *>(&cycleTime), sizeof(cycleTime));
    os.write(reinterpret_cast<char *>(&error), sizeof(error));
    os.write(reinterpret_cast<char *>(&bitLenOfLastBit), sizeof(bitLenOfLastBit));
    os.write(reinterpret_cast<char *>(&reserved5), sizeof(reserved5));
}

DWORD A429Message::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        static_cast<DWORD>(a429Data.size()) +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(reserved1) +
        sizeof(bitrate) +
        sizeof(errReason) +
        sizeof(errPosition) +
        sizeof(reserved2) +
        sizeof(reserved3) +
        sizeof(frameGap) +
        sizeof(frameLength) +
        sizeof(msgCtrl) +
        sizeof(reserved4) +
        sizeof(cycleTime) +
        sizeof(error) +
        sizeof(bitLenOfLastBit) +
        sizeof(reserved5);
}

}
}
