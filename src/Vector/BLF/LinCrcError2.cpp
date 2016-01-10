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

#include "LinCrcError2.h"

namespace Vector {
namespace BLF {

LinCrcError2::LinCrcError2() :
    ObjectHeader(),
    LinDatabyteTimestampEvent(),
    data(),
    crc(),
    dir(),
    fsmId(),
    fsmState(),
    simulated(),
    reserved1(),
    respBaudrate(),
    reserved2(),
    exactHeaderBaudrate(),
    earlyStopbitOffset(),
    earlyStopbitOffsetResponse()
{
    objectType = ObjectType::LIN_CRC_ERROR2;
}

void LinCrcError2::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinDatabyteTimestampEvent::read(is);
    is.read((char *) data.data(), data.size());
    is.read((char *) &crc, sizeof(crc));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &fsmId, sizeof(fsmId));
    is.read((char *) &fsmState, sizeof(fsmState));
    is.read((char *) &simulated, sizeof(simulated));
    is.read((char *) reserved1.data(), reserved1.size());
    is.read((char *) &respBaudrate, sizeof(respBaudrate));
    is.read((char *) reserved2.data(), reserved2.size());
    is.read((char *) &exactHeaderBaudrate, sizeof(exactHeaderBaudrate));
    is.read((char *) &earlyStopbitOffset, sizeof(earlyStopbitOffset));
    is.read((char *) &earlyStopbitOffsetResponse, sizeof(earlyStopbitOffsetResponse));
}

void LinCrcError2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinDatabyteTimestampEvent::write(os);
    os.write((char *) data.data(), data.size());
    os.write((char *) &crc, sizeof(crc));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &fsmId, sizeof(fsmId));
    os.write((char *) &fsmState, sizeof(fsmState));
    os.write((char *) &simulated, sizeof(simulated));
    os.write((char *) reserved1.data(), reserved1.size());
    os.write((char *) &respBaudrate, sizeof(respBaudrate));
    os.write((char *) reserved2.data(), reserved2.size());
    os.write((char *) &exactHeaderBaudrate, sizeof(exactHeaderBaudrate));
    os.write((char *) &earlyStopbitOffset, sizeof(earlyStopbitOffset));
    os.write((char *) &earlyStopbitOffsetResponse, sizeof(earlyStopbitOffsetResponse));
}

size_t LinCrcError2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        data.size() +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        sizeof(simulated) +
        reserved1.size() +
        sizeof(respBaudrate) +
        reserved2.size() +
        sizeof(exactHeaderBaudrate) +
        sizeof(earlyStopbitOffset) +
        sizeof(earlyStopbitOffsetResponse);

    return size;
}

}
}
