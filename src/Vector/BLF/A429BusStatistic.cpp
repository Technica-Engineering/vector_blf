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

#include <Vector/BLF/A429BusStatistic.h>

namespace Vector {
namespace BLF {

A429BusStatistic::A429BusStatistic() :
    ObjectHeader(),
    channel(),
    dir(),
    busload(),
    dataTotal(),
    errorTotal(),
    bitrate(),
    parityErrors(),
    bitrateErrors(),
    gapErrors(),
    lineErrors(),
    formatErrors(),
    dutyFactorErrors(),
    wordLenErrors(),
    codingErrors(),
    idleErrors(),
    levelErrors(),
    labelCount()
{
    objectType = ObjectType::A429_BUS_STATISTIC;
}

void A429BusStatistic::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&busload), sizeof(busload));
    is.read(reinterpret_cast<char *>(&dataTotal), sizeof(dataTotal));
    is.read(reinterpret_cast<char *>(&errorTotal), sizeof(errorTotal));
    is.read(reinterpret_cast<char *>(&bitrate), sizeof(bitrate));
    is.read(reinterpret_cast<char *>(&parityErrors), sizeof(parityErrors));
    is.read(reinterpret_cast<char *>(&bitrateErrors), sizeof(bitrateErrors));
    is.read(reinterpret_cast<char *>(&gapErrors), sizeof(gapErrors));
    is.read(reinterpret_cast<char *>(&lineErrors), sizeof(lineErrors));
    is.read(reinterpret_cast<char *>(&formatErrors), sizeof(formatErrors));
    is.read(reinterpret_cast<char *>(&dutyFactorErrors), sizeof(dutyFactorErrors));
    is.read(reinterpret_cast<char *>(&wordLenErrors), sizeof(wordLenErrors));
    is.read(reinterpret_cast<char *>(&codingErrors), sizeof(codingErrors));
    is.read(reinterpret_cast<char *>(&idleErrors), sizeof(idleErrors));
    is.read(reinterpret_cast<char *>(&levelErrors), sizeof(levelErrors));
    is.read(reinterpret_cast<char *>(labelCount.data()), static_cast<std::streamsize>(labelCount.size()));
}

void A429BusStatistic::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&busload), sizeof(busload));
    os.write(reinterpret_cast<char *>(&dataTotal), sizeof(dataTotal));
    os.write(reinterpret_cast<char *>(&errorTotal), sizeof(errorTotal));
    os.write(reinterpret_cast<char *>(&bitrate), sizeof(bitrate));
    os.write(reinterpret_cast<char *>(&parityErrors), sizeof(parityErrors));
    os.write(reinterpret_cast<char *>(&bitrateErrors), sizeof(bitrateErrors));
    os.write(reinterpret_cast<char *>(&gapErrors), sizeof(gapErrors));
    os.write(reinterpret_cast<char *>(&lineErrors), sizeof(lineErrors));
    os.write(reinterpret_cast<char *>(&formatErrors), sizeof(formatErrors));
    os.write(reinterpret_cast<char *>(&dutyFactorErrors), sizeof(dutyFactorErrors));
    os.write(reinterpret_cast<char *>(&wordLenErrors), sizeof(wordLenErrors));
    os.write(reinterpret_cast<char *>(&codingErrors), sizeof(codingErrors));
    os.write(reinterpret_cast<char *>(&idleErrors), sizeof(idleErrors));
    os.write(reinterpret_cast<char *>(&levelErrors), sizeof(levelErrors));
    os.write(reinterpret_cast<char *>(labelCount.data()), static_cast<std::streamsize>(labelCount.size()));
}

DWORD A429BusStatistic::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(busload) +
        sizeof(dataTotal) +
        sizeof(errorTotal) +
        sizeof(bitrate) +
        sizeof(parityErrors) +
        sizeof(bitrateErrors) +
        sizeof(gapErrors) +
        sizeof(lineErrors) +
        sizeof(formatErrors) +
        sizeof(dutyFactorErrors) +
        sizeof(wordLenErrors) +
        sizeof(codingErrors) +
        sizeof(idleErrors) +
        sizeof(levelErrors) +
        sizeof(labelCount);
}

}
}
