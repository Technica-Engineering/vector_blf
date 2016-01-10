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

#include "LinSyncError2.h"

namespace Vector {
namespace BLF {

LinSyncError2::LinSyncError2() :
    ObjectHeader(),
    LinSynchFieldEvent(),
    timeDiff()
{
    objectType = ObjectType::LIN_SYN_ERROR2;
}

void LinSyncError2::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    LinSynchFieldEvent::read(is);
    is.read((char *) timeDiff.data(), timeDiff.size() * sizeof(WORD));
}

void LinSyncError2::write(AbstractFile & os)
{
    ObjectHeader::write(os);
    LinSynchFieldEvent::write(os);
    os.write((char *) timeDiff.data(), timeDiff.size() * sizeof(WORD));
}

size_t LinSyncError2::calculateObjectSize()
{
    size_t size =
        ObjectHeader::calculateObjectSize() +
        LinSynchFieldEvent::calculateObjectSize() +
        timeDiff.size() * sizeof(WORD);

    return size;
}

}
}
