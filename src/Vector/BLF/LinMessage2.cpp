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

#include <Vector/BLF/LinMessage2.h>

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
    is.read(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    is.read(reinterpret_cast<char *>(&crc), sizeof(crc));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&simulated), sizeof(simulated));
    is.read(reinterpret_cast<char *>(&isEtf), sizeof(isEtf));
    is.read(reinterpret_cast<char *>(&etfAssocIndex), sizeof(etfAssocIndex));
    is.read(reinterpret_cast<char *>(&etfAssocEtfId), sizeof(etfAssocEtfId));
    is.read(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    is.read(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    is.read(reinterpret_cast<char *>(reserved.data()), static_cast<std::streamsize>(reserved.size()));

    /* the following variables are only available in Version 2 and above */
    /*if (objectVersion < 0)*/ // Vector bug: Shouldn't this be < 1?
    /*    return;*/

    is.read(reinterpret_cast<char *>(&respBaudrate), sizeof(respBaudrate));

    /* the following variables are only available in Version 3 and above */
    if (objectVersion < 1) { // Vector bug: Shouldn't this be < 2?
        return;
    }

    is.read(reinterpret_cast<char *>(&exactHeaderBaudrate), sizeof(exactHeaderBaudrate));
    is.read(reinterpret_cast<char *>(&earlyStopbitOffset), sizeof(earlyStopbitOffset));
    is.read(reinterpret_cast<char *>(&earlyStopbitOffsetResponse), sizeof(earlyStopbitOffsetResponse));
}

void LinMessage2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinDatabyteTimestampEvent::write(os);
    os.write(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
    os.write(reinterpret_cast<char *>(&crc), sizeof(crc));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&simulated), sizeof(simulated));
    os.write(reinterpret_cast<char *>(&isEtf), sizeof(isEtf));
    os.write(reinterpret_cast<char *>(&etfAssocIndex), sizeof(etfAssocIndex));
    os.write(reinterpret_cast<char *>(&etfAssocEtfId), sizeof(etfAssocEtfId));
    os.write(reinterpret_cast<char *>(&fsmId), sizeof(fsmId));
    os.write(reinterpret_cast<char *>(&fsmState), sizeof(fsmState));
    os.write(reinterpret_cast<char *>(reserved.data()), static_cast<std::streamsize>(reserved.size()));

    /* the following variables are only available in Version 2 and above */
    /*if (objectVersion < 0)*/ // Vector bug: Shouldn't this be < 1?
    /*    return;*/

    os.write(reinterpret_cast<char *>(&respBaudrate), sizeof(respBaudrate));

    /* the following variables are only available in Version 3 and above */
    if (objectVersion < 1) { // Vector bug: Shouldn't this be < 2?
        return;
    }

    os.write(reinterpret_cast<char *>(&exactHeaderBaudrate), sizeof(exactHeaderBaudrate));
    os.write(reinterpret_cast<char *>(&earlyStopbitOffset), sizeof(earlyStopbitOffset));
    os.write(reinterpret_cast<char *>(&earlyStopbitOffsetResponse), sizeof(earlyStopbitOffsetResponse));
}

DWORD LinMessage2::calculateObjectSize() const
{
    DWORD size =
        ObjectHeader::calculateObjectSize() +
        LinDatabyteTimestampEvent::calculateObjectSize() +
        static_cast<DWORD>(data.size()) +
        sizeof(crc) +
        sizeof(dir) +
        sizeof(simulated) +
        sizeof(isEtf) +
        sizeof(etfAssocIndex) +
        sizeof(etfAssocEtfId) +
        sizeof(fsmId) +
        sizeof(fsmState) +
        static_cast<DWORD>(reserved.size());

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
