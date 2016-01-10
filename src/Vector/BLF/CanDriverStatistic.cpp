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

#include "CanDriverStatistic.h"

namespace Vector {
namespace BLF {

CanDriverStatistic::CanDriverStatistic() :
    ObjectHeader(),
    channel(),
    busLoad(),
    standardDataFrames(),
    extendedDataFrames(),
    standardRemoteFrames(),
    extendedRemoteFrames(),
    errorFrames(),
    overloadFrames(),
    reserved()
{
    objectType = ObjectType::CAN_STATISTIC;
}

void CanDriverStatistic::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &busLoad, sizeof(busLoad));
    is.read((char *) &standardDataFrames, sizeof(standardDataFrames));
    is.read((char *) &extendedDataFrames, sizeof(extendedDataFrames));
    is.read((char *) &standardRemoteFrames, sizeof(standardRemoteFrames));
    is.read((char *) &extendedRemoteFrames, sizeof(extendedRemoteFrames));
    is.read((char *) &errorFrames, sizeof(errorFrames));
    is.read((char *) &overloadFrames, sizeof(overloadFrames));
    is.read((char *) reserved.data(), reserved.size());
}

void CanDriverStatistic::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &busLoad, sizeof(busLoad));
    os.write((char *) &standardDataFrames, sizeof(standardDataFrames));
    os.write((char *) &extendedDataFrames, sizeof(extendedDataFrames));
    os.write((char *) &standardRemoteFrames, sizeof(standardRemoteFrames));
    os.write((char *) &extendedRemoteFrames, sizeof(extendedRemoteFrames));
    os.write((char *) &errorFrames, sizeof(errorFrames));
    os.write((char *) &overloadFrames, sizeof(overloadFrames));
    os.write((char *) reserved.data(), reserved.size());
}

size_t CanDriverStatistic::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(busLoad) +
        sizeof(standardDataFrames) +
        sizeof(extendedDataFrames) +
        sizeof(standardRemoteFrames) +
        sizeof(extendedRemoteFrames) +
        sizeof(errorFrames) +
        sizeof(overloadFrames) +
        reserved.size();

    return size;
}

}
}
