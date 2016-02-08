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

#include <cstring>

#include "UncompressedFile.h"

namespace Vector {
namespace BLF {

UncompressedFile::UncompressedFile() :
    privateTellg(0),
    privateTellp(0),
    dataTell(0),
    data()
{
}

void UncompressedFile::read(char * s, std::streamsize n)
{
    /** offset to read */
    std::streamoff offset = privateTellg - dataTell;

    /** copy data */
    memcpy(s, data.data() + offset, n);

    /** new get position */
    privateTellg += n;
}

std::streampos UncompressedFile::tellg()
{
    return privateTellg;
}

void UncompressedFile::seekg(std::streampos pos)
{
    privateTellg = pos;
}

void UncompressedFile::seekg(std::streamoff off, std::ios_base::seekdir way)
{
    switch(way) {
    default:
    case std::ios_base::beg:
        privateTellg = 0 + off;
        break;
    case std::ios_base::cur:
        privateTellg = privateTellg + off;
        break;
    case std::ios_base::end:
        privateTellg = privateTellp + off;
        break;
    }
}

void UncompressedFile::write(const char * s, std::streamsize n)
{
    /** offset to write */
    std::streamoff offset = privateTellp - dataTell;

    /** extend data */
    data.resize(data.size() + n);

    /** copy data */
    memcpy(data.data() + offset, s, n);

    /** new put position */
    privateTellp += n;
}

std::streampos UncompressedFile::tellp()
{
    return privateTellp;
}

void UncompressedFile::dropOldData(std::streamsize dropSize, std::streamsize remainingSize)
{
    /* calculate sizes */
    std::streamsize oldDataSize = privateTellg - dataTell;
    oldDataSize -= remainingSize;

    /* drop data */
    if (dropSize <= oldDataSize) {
        data.erase(data.begin(), data.begin() + dropSize);
        dataTell += dropSize;
    }
}

}
}
