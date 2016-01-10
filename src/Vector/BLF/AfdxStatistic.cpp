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

#include "AfdxStatistic.h"

namespace Vector {
namespace BLF {

AfdxStatistic::AfdxStatistic() :
    ObjectHeader(),
    channel(),
    flags(),
    rxPacketCount(),
    rxByteCount(),
    txPacketCount(),
    txByteCount(),
    collisionCount(),
    errorCount(),
    statDroppedRedundantPacketCount(),
    statRedundantErrorPacketCount(),
    statIntegrityErrorPacketCount(),
    statAvrgPeriodMsec(),
    statAvrgJitterMysec(),
    vlid(),
    statDuration()
{
    objectType = ObjectType::AFDX_STATISTIC;
}

void AfdxStatistic::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &rxPacketCount, sizeof(rxPacketCount));
    is.read((char *) &rxByteCount, sizeof(rxByteCount));
    is.read((char *) &txPacketCount, sizeof(txPacketCount));
    is.read((char *) &txByteCount, sizeof(txByteCount));
    is.read((char *) &collisionCount, sizeof(collisionCount));
    is.read((char *) &errorCount, sizeof(errorCount));
    is.read((char *) &statDroppedRedundantPacketCount, sizeof(statDroppedRedundantPacketCount));
    is.read((char *) &statRedundantErrorPacketCount, sizeof(statRedundantErrorPacketCount));
    is.read((char *) &statIntegrityErrorPacketCount, sizeof(statIntegrityErrorPacketCount));
    is.read((char *) &statAvrgPeriodMsec, sizeof(statAvrgPeriodMsec));
    is.read((char *) &statAvrgJitterMysec, sizeof(statAvrgJitterMysec));
    is.read((char *) &vlid, sizeof(vlid));
    is.read((char *) &statDuration, sizeof(statDuration));
}

void AfdxStatistic::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &rxPacketCount, sizeof(rxPacketCount));
    os.write((char *) &rxByteCount, sizeof(rxByteCount));
    os.write((char *) &txPacketCount, sizeof(txPacketCount));
    os.write((char *) &txByteCount, sizeof(txByteCount));
    os.write((char *) &collisionCount, sizeof(collisionCount));
    os.write((char *) &errorCount, sizeof(errorCount));
    os.write((char *) &statDroppedRedundantPacketCount, sizeof(statDroppedRedundantPacketCount));
    os.write((char *) &statRedundantErrorPacketCount, sizeof(statRedundantErrorPacketCount));
    os.write((char *) &statIntegrityErrorPacketCount, sizeof(statIntegrityErrorPacketCount));
    os.write((char *) &statAvrgPeriodMsec, sizeof(statAvrgPeriodMsec));
    os.write((char *) &statAvrgJitterMysec, sizeof(statAvrgJitterMysec));
    os.write((char *) &vlid, sizeof(vlid));
    os.write((char *) &statDuration, sizeof(statDuration));
}

size_t AfdxStatistic::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(flags) +
        sizeof(rxPacketCount) +
        sizeof(rxByteCount) +
        sizeof(txPacketCount) +
        sizeof(txByteCount) +
        sizeof(collisionCount) +
        sizeof(errorCount) +
        sizeof(statDroppedRedundantPacketCount) +
        sizeof(statRedundantErrorPacketCount) +
        sizeof(statIntegrityErrorPacketCount) +
        sizeof(statAvrgPeriodMsec) +
        sizeof(statAvrgJitterMysec) +
        sizeof(vlid) +
        sizeof(statDuration);

    return size;
}

}
}
