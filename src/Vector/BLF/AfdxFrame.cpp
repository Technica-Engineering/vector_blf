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

#include <Vector/BLF/AfdxFrame.h>

namespace Vector {
namespace BLF {

AfdxFrame::AfdxFrame() :
    ObjectHeader(),
    sourceAddress(),
    channel(),
    destinationAddress(),
    dir(),
    type(),
    tpid(),
    tci(),
    ethChannel(),
    reserved1(),
    afdxFlags(),
    reserved2(),
    bagUsec(),
    payLoadLength(),
    reserved3(),
    payLoad()
{
    objectType = ObjectType::AFDX_FRAME;
}

void AfdxFrame::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(sourceAddress.data()), static_cast<std::streamsize>(sourceAddress.size()));
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(destinationAddress.data()), static_cast<std::streamsize>(destinationAddress.size()));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&type), sizeof(type));
    is.read(reinterpret_cast<char *>(&tpid), sizeof(tpid));
    is.read(reinterpret_cast<char *>(&tci), sizeof(tci));
    is.read(reinterpret_cast<char *>(&ethChannel), sizeof(ethChannel));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&afdxFlags), sizeof(afdxFlags));
    is.read(reinterpret_cast<char *>(reserved2.data()), static_cast<std::streamsize>(reserved2.size()));
    is.read(reinterpret_cast<char *>(&bagUsec), sizeof(bagUsec));
    is.read(reinterpret_cast<char *>(&payLoadLength), sizeof(payLoadLength));
    is.read(reinterpret_cast<char *>(reserved3.data()), static_cast<std::streamsize>(reserved3.size()));
    payLoad.resize(payLoadLength);
    is.read(reinterpret_cast<char *>(payLoad.data()), payLoadLength);
}

void AfdxFrame::write(AbstractFile & os)
{
    /* pre processing */
    payLoadLength = static_cast<WORD>(payLoad.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(sourceAddress.data()), static_cast<std::streamsize>(sourceAddress.size()));
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(destinationAddress.data()), static_cast<std::streamsize>(destinationAddress.size()));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&type), sizeof(type));
    os.write(reinterpret_cast<char *>(&tpid), sizeof(tpid));
    os.write(reinterpret_cast<char *>(&tci), sizeof(tci));
    os.write(reinterpret_cast<char *>(&ethChannel), sizeof(ethChannel));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&afdxFlags), sizeof(afdxFlags));
    os.write(reinterpret_cast<char *>(reserved2.data()), static_cast<std::streamsize>(reserved2.size()));
    os.write(reinterpret_cast<char *>(&bagUsec), sizeof(bagUsec));
    os.write(reinterpret_cast<char *>(&payLoadLength), sizeof(payLoadLength));
    os.write(reinterpret_cast<char *>(reserved3.data()), static_cast<std::streamsize>(reserved3.size()));
    os.write(reinterpret_cast<char *>(payLoad.data()), payLoadLength);
}

DWORD AfdxFrame::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        static_cast<DWORD>(sourceAddress.size()) +
        sizeof(channel) +
        static_cast<DWORD>(destinationAddress.size()) +
        sizeof(dir) +
        sizeof(type) +
        sizeof(tpid) +
        sizeof(tci) +
        sizeof(ethChannel) +
        sizeof(reserved1) +
        sizeof(afdxFlags) +
        static_cast<DWORD>(reserved2.size()) +
        sizeof(bagUsec) +
        sizeof(payLoadLength) +
        static_cast<DWORD>(reserved3.size()) +
        payLoadLength;
}

}
}
