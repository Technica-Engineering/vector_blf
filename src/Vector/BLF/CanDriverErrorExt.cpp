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

#include "CanDriverErrorExt.h"

namespace Vector {
namespace BLF {

CanDriverErrorExt::CanDriverErrorExt() :
    ObjectHeader(),
    channel(),
    txErrors(),
    rxErrors(),
    errorCode(),
    flags(),
    state(),
    reserved1(),
    reserved2(),
    reserved3()
{
    objectType = ObjectType::CAN_DRIVER_ERROR_EXT;
}

void CanDriverErrorExt::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read((char *) &channel, sizeof(channel));
    is.read((char *) &txErrors, sizeof(txErrors));
    is.read((char *) &rxErrors, sizeof(rxErrors));
    is.read((char *) &errorCode, sizeof(errorCode));
    is.read((char *) &flags, sizeof(flags));
    is.read((char *) &state, sizeof(state));
    is.read((char *) &reserved1, sizeof(reserved1));
    is.read((char *) &reserved2, sizeof(reserved2));
    is.read((char *) reserved3.data(), reserved3.size());
}

void CanDriverErrorExt::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    os.write((char *) &channel, sizeof(channel));
    os.write((char *) &txErrors, sizeof(txErrors));
    os.write((char *) &rxErrors, sizeof(rxErrors));
    os.write((char *) &errorCode, sizeof(errorCode));
    os.write((char *) &flags, sizeof(flags));
    os.write((char *) &state, sizeof(state));
    os.write((char *) &reserved1, sizeof(reserved1));
    os.write((char *) &reserved2, sizeof(reserved2));
    os.write((char *) reserved3.data(), reserved3.size());
}

size_t CanDriverErrorExt::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(txErrors) +
        sizeof(rxErrors) +
        sizeof(errorCode) +
        sizeof(flags) +
        sizeof(state) +
        sizeof(reserved1) +
        sizeof(reserved2) +
        reserved3.size();

    return size;
}

}
}
