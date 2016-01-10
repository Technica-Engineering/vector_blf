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

#include "LinSendError2.h"

namespace Vector {
namespace BLF {

LinSendError2::LinSendError2() :
    ObjectHeader(),
    LinMessageDescriptor(),
    eoh(),
    isEtf(),
    fsmId(),
    fsmState(),
    reserved1(),
    reserved2(),
    exactHeaderBaudrate(),
    earlyStopbitOffset(),
    reserved3()
{
    objectType = ObjectType::LIN_SND_ERROR2;
}

void LinSendError2::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinMessageDescriptor::read(is);
    is.read((char *) &eoh, sizeof(eoh));
    is.read((char *) &isEtf, sizeof(isEtf));
    is.read((char *) &fsmId, sizeof(fsmId));
    is.read((char *) &fsmState, sizeof(fsmState));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) reserved2.data(), reserved2.size());
    is.read((char *) &exactHeaderBaudrate, sizeof(exactHeaderBaudrate));
    is.read((char *) &earlyStopbitOffset, sizeof(earlyStopbitOffset));
    is.read((char *) reserved3.data(), reserved3.size());
}

void LinSendError2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinMessageDescriptor::write(os);
    os.write((char *) &eoh, sizeof(eoh));
    os.write((char *) &isEtf, sizeof(isEtf));
    os.write((char *) &fsmId, sizeof(fsmId));
    os.write((char *) &fsmState, sizeof(fsmState));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) reserved2.data(), reserved2.size());
    os.write((char *) &exactHeaderBaudrate, sizeof(exactHeaderBaudrate));
    os.write((char *) &earlyStopbitOffset, sizeof(earlyStopbitOffset));
    os.write((char *) reserved3.data(), reserved3.size());
}

size_t LinSendError2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinMessageDescriptor::calculateObjectSize() +
        sizeof(eoh) +
        sizeof(isEtf) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(reserved1) +
        reserved2.size() +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        reserved3.size();

    return size;
}

}
}
