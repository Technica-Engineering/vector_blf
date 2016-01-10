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

#include "MostStatisticEx.h"

namespace Vector {
namespace BLF {

MostStatisticEx::MostStatisticEx() :
    ObjectHeader2(),
    channel(),
    reserved1(),
    codingErrors(),
    frameCounter(),
    reserved2()
{
    objectType = ObjectType::MOST_STATISTICEX;
}

void MostStatisticEx::read(AbstractFile & is)
{
    ObjectHeader2::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &codingErrors, sizeof(codingErrors));
    is.read((char *) &frameCounter, sizeof(frameCounter));
    is.read((char *) reserved2.data(), reserved2.size());
}

void MostStatisticEx::write(AbstractFile & os)
{
    ObjectHeader2::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &codingErrors, sizeof(codingErrors));
    os.write((char *) &frameCounter, sizeof(frameCounter));
    os.write((char *) reserved2.data(), reserved2.size());
}

size_t MostStatisticEx::calculateObjectSize()
{
    size_t size =
        ObjectHeader2::calculateObjectSize() +
        sizeof(channel) +
        sizeof(reserved1) +
        sizeof(codingErrors) +
        sizeof(frameCounter) +
        reserved2.size();

    return size;
}

}
}
