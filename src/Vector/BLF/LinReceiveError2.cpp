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

#include <Vector/BLF/LinReceiveError2.h>

namespace Vector {
namespace BLF {

LinReceiveError2::LinReceiveError2() :
    ObjectHeader(),
    LinDatabyteTimestampEvent(),
    data(),
    fsmId(),
    fsmState(),
    stateReason(),
    offendingByte(),
    shortError(),
    timeoutDuringDlcDetection(),
    isEtf(),
    hasDatabytes(),
    respBaudrate(),
    reserved(),
    exactHeaderBaudrate(),
    earlyStopbitOffset(),
    earlyStopbitOffsetResponse()
{
    objectType = ObjectType::LIN_RCV_ERROR2;
}

void LinReceiveError2::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinDatabyteTimestampEvent::read(is);
    is.read(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    is.read(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    is.read(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    is.read(reinterpret_cast<char *>(&stateReason), sizeof(stateReason));
    is.read(reinterpret_cast<char *>(&offendingByte), sizeof(offendingByte));
    is.read(reinterpret_cast<char *>(&shortError), sizeof(shortError));
    is.read(reinterpret_cast<char *>(&timeoutDuringDlcDetection), sizeof(timeoutDuringDlcDetection));
    is.read(reinterpret_cast<char *>(&isEtf), sizeof(isEtf));
    is.read(reinterpret_cast<char *>(&hasDatabytes), sizeof(hasDatabytes));
    is.read(reinterpret_cast<char *>(&respBaudrate), sizeof(respBaudrate));
    is.read(reinterpret_cast<char *>(reserved.data()), static_cast<std::streamsize>(reserved.size()));
    is.read(reinterpret_cast<char *>(&exactHeaderBaudrate), sizeof(exactHeaderBaudrate));
    is.read(reinterpret_cast<char *>(&earlyStopbitOffset), sizeof(earlyStopbitOffset));
    is.read(reinterpret_cast<char *>(&earlyStopbitOffsetResponse), sizeof(earlyStopbitOffsetResponse));
}

void LinReceiveError2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinDatabyteTimestampEvent::write(os);
    os.write(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    os.write(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    os.write(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    os.write(reinterpret_cast<char *>(&stateReason), sizeof(stateReason));
    os.write(reinterpret_cast<char *>(&offendingByte), sizeof(offendingByte));
    os.write(reinterpret_cast<char *>(&shortError), sizeof(shortError));
    os.write(reinterpret_cast<char *>(&timeoutDuringDlcDetection), sizeof(timeoutDuringDlcDetection));
    os.write(reinterpret_cast<char *>(&isEtf), sizeof(isEtf));
    os.write(reinterpret_cast<char *>(&hasDatabytes), sizeof(hasDatabytes));
    os.write(reinterpret_cast<char *>(&respBaudrate), sizeof(respBaudrate));
    os.write(reinterpret_cast<char *>(reserved.data()), static_cast<std::streamsize>(reserved.size()));
    os.write(reinterpret_cast<char *>(&exactHeaderBaudrate), sizeof(exactHeaderBaudrate));
    os.write(reinterpret_cast<char *>(&earlyStopbitOffset), sizeof(earlyStopbitOffset));
    os.write(reinterpret_cast<char *>(&earlyStopbitOffsetResponse), sizeof(earlyStopbitOffsetResponse));
}

DWORD LinReceiveError2::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        static_cast<DWORD>(data.size()) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(stateReason) +
        sizeof(offendingByte) +
        sizeof(shortError) +
        sizeof(timeoutDuringDlcDetection) +
        sizeof(isEtf) +
        sizeof(hasDatabytes) +
        sizeof(respBaudrate) +
        static_cast<DWORD>(reserved.size()) +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        sizeof(earlyStopbitOffsetResponse);
}

}
}
