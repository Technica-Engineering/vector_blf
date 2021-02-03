/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/RestorePoint.h>

namespace Vector {
namespace BLF {

void RestorePoint::read(AbstractFile & is) {
    is.read(reinterpret_cast<char *>(&timeStamp), sizeof(timeStamp));
    is.read(reinterpret_cast<char *>(&compressedFilePosition), sizeof(compressedFilePosition));
    is.read(reinterpret_cast<char *>(&uncompressedFileOffset), sizeof(uncompressedFileOffset));
    is.read(reinterpret_cast<char *>(&unknownRestorePoint), sizeof(unknownRestorePoint));
}

void RestorePoint::write(AbstractFile & os) {
    os.write(reinterpret_cast<char *>(&timeStamp), sizeof(timeStamp));
    os.write(reinterpret_cast<char *>(&compressedFilePosition), sizeof(compressedFilePosition));
    os.write(reinterpret_cast<char *>(&uncompressedFileOffset), sizeof(uncompressedFileOffset));
    os.write(reinterpret_cast<char *>(&unknownRestorePoint), sizeof(unknownRestorePoint));
}

uint32_t RestorePoint::calculateObjectSize() {
    return
        sizeof(timeStamp) +
        sizeof(compressedFilePosition) +
        sizeof(uncompressedFileOffset) +
        sizeof(unknownRestorePoint);
}

}
}
