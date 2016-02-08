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

#include "LinMessage2.h"

namespace Vector {
namespace BLF {

LinMessage2::LinMessage2() :
    ObjectHeader(),
    LinDatabyteTimestampEvent(),
    data(),
    crc(),
    dir(),
    simulated(),
    isEtf(),
    etfAssocIndex(),
    etfAssocEtfId(),
    fsmId(),
    fsmState(),
    reserved(),
    respBaudrate(),
    exactHeaderBaudrate(),
    earlyStopbitOffset(),
    earlyStopbitOffsetResponse()
{
    objectType = ObjectType::LIN_MESSAGE2;
    objectVersion = 1;
}

void LinMessage2::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinDatabyteTimestampEvent::read(is);
    is.read((char *) data.data(), data.size());
    is.read((char *) &crc, sizeof(crc));
    is.read((char *) &dir, sizeof(dir));
    is.read((char *) &simulated, sizeof(simulated));
    is.read((char *) &isEtf, sizeof(isEtf));
    is.read((char *) &etfAssocIndex, sizeof(etfAssocIndex));
    is.read((char *) &etfAssocEtfId, sizeof(etfAssocEtfId));
    is.read((char *) &fsmId, sizeof(fsmId));
    is.read((char *) &fsmState, sizeof(fsmState));
    is.read((char *) reserved.data(), reserved.size());

    /* the following variables are only available in Version 2 and above */
    /*if (objectVersion < 0)*/ // Vector bug: Shouldn't this be < 1?
    /*    return;*/

    is.read((char *) &respBaudrate, sizeof(respBaudrate));

    /* the following variables are only available in Version 3 and above */
    if (objectVersion < 1) // Vector bug: Shouldn't this be < 2?
        return;

    is.read((char *) &exactHeaderBaudrate, sizeof(exactHeaderBaudrate));
    is.read((char *) &earlyStopbitOffset, sizeof(earlyStopbitOffset));
    is.read((char *) &earlyStopbitOffsetResponse, sizeof(earlyStopbitOffsetResponse));
}

void LinMessage2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinDatabyteTimestampEvent::write(os);
    os.write((char *) data.data(), data.size());
    os.write((char *) &crc, sizeof(crc));
    os.write((char *) &dir, sizeof(dir));
    os.write((char *) &simulated, sizeof(simulated));
    os.write((char *) &isEtf, sizeof(isEtf));
    os.write((char *) &etfAssocIndex, sizeof(etfAssocIndex));
    os.write((char *) &etfAssocEtfId, sizeof(etfAssocEtfId));
    os.write((char *) &fsmId, sizeof(fsmId));
    os.write((char *) &fsmState, sizeof(fsmState));
    os.write((char *) reserved.data(), reserved.size());

    /* the following variables are only available in Version 2 and above */
    /*if (objectVersion < 0)*/ // Vector bug: Shouldn't this be < 1?
    /*    return;*/

    os.write((char *) &respBaudrate, sizeof(respBaudrate));

    /* the following variables are only available in Version 3 and above */
    if (objectVersion < 1) // Vector bug: Shouldn't this be < 2?
        return;

    os.write((char *) &exactHeaderBaudrate, sizeof(exactHeaderBaudrate));
    os.write((char *) &earlyStopbitOffset, sizeof(earlyStopbitOffset));
    os.write((char *) &earlyStopbitOffsetResponse, sizeof(earlyStopbitOffsetResponse));
}

size_t LinMessage2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        data.size() +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(simulated) +
        sizeof(isEtf) +
        sizeof(etfAssocIndex) +
        sizeof(etfAssocEtfId) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        reserved.size();

    /*if (objectVersion >= 0)*/ // Vector bug: Shouldn't this be >= 1?
        size += sizeof(respBaudrate);

    if (objectVersion >= 1) // Vector bug: Shouldn't this be >= 2?
        size += sizeof(exactHeaderBaudrate) +
                sizeof(earlyStopbitOffset) +
                sizeof(earlyStopbitOffsetResponse);

    return size;
}

}
}
