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

#include "LinReceiveError2.h"

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
    is.read((char *) data.data(), data.size());
    is.read((char *) &fsmId, sizeof(fsmId));
    is.read((char *) &fsmState, sizeof(fsmState));
    is.read((char *) &stateReason, sizeof(stateReason));
    is.read((char *) &offendingByte, sizeof(offendingByte));
    is.read((char *) &shortError, sizeof(shortError));
    is.read((char *) &timeoutDuringDlcDetection, sizeof(timeoutDuringDlcDetection));
    is.read((char *) &isEtf, sizeof(isEtf));
    is.read((char *) &hasDatabytes, sizeof(hasDatabytes));
    is.read((char *) &respBaudrate, sizeof(respBaudrate));
    is.read((char *) reserved.data(), reserved.size());
    is.read((char *) &exactHeaderBaudrate, sizeof(exactHeaderBaudrate));
    is.read((char *) &earlyStopbitOffset, sizeof(earlyStopbitOffset));
    is.read((char *) &earlyStopbitOffsetResponse, sizeof(earlyStopbitOffsetResponse));
}

void LinReceiveError2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinDatabyteTimestampEvent::write(os);
    os.write((char *) data.data(), data.size());
    os.write((char *) &fsmId, sizeof(fsmId));
    os.write((char *) &fsmState, sizeof(fsmState));
    os.write((char *) &stateReason, sizeof(stateReason));
    os.write((char *) &offendingByte, sizeof(offendingByte));
    os.write((char *) &shortError, sizeof(shortError));
    os.write((char *) &timeoutDuringDlcDetection, sizeof(timeoutDuringDlcDetection));
    os.write((char *) &isEtf, sizeof(isEtf));
    os.write((char *) &hasDatabytes, sizeof(hasDatabytes));
    os.write((char *) &respBaudrate, sizeof(respBaudrate));
    os.write((char *) reserved.data(), reserved.size());
    os.write((char *) &exactHeaderBaudrate, sizeof(exactHeaderBaudrate));
    os.write((char *) &earlyStopbitOffset, sizeof(earlyStopbitOffset));
    os.write((char *) &earlyStopbitOffsetResponse, sizeof(earlyStopbitOffsetResponse));
}

size_t LinReceiveError2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        data.size() +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(stateReason) +
        sizeof(offendingByte) +
        sizeof(shortError) +
        sizeof(timeoutDuringDlcDetection) +
        sizeof(isEtf) +
        sizeof(hasDatabytes) +
        sizeof(respBaudrate) +
        reserved.size() +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        sizeof(earlyStopbitOffsetResponse);

    return size;
}

}
}
