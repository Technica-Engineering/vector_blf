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

#include <Vector/BLF/UncompressedFile.h>

#include <cassert>
#include <cstring>

namespace Vector {
namespace BLF {

UncompressedFile::UncompressedFile() :
    m_gcount(0),
    m_tellg(0),
    m_tellp(0),
    m_dataBegin(0),
    m_data()
{
}

std::streamsize UncompressedFile::gcount() const
{
    return m_gcount;
}

void UncompressedFile::read(char * s, std::streamsize n)
{
    /* offset to read */
    std::streamoff offset = m_tellg - m_dataBegin;

    /* check if sufficient data is available */
    if (m_tellg + n >= dataEnd()) {
        n = dataEnd() - m_tellg;
    }

    /* copy data */
    std::copy(m_data.begin() + offset, m_data.begin() + offset + n, s);

    /* new get position */
    m_tellg += n;

    /* remember get count */
    m_gcount = n;
}

std::streampos UncompressedFile::tellg()
{
    return m_tellg;
}

void UncompressedFile::seekg(std::streampos pos)
{
    m_tellg = pos;
}

void UncompressedFile::seekg(std::streamoff off, std::ios_base::seekdir way)
{
    assert(way == std::ios_base::cur);

    m_tellg = m_tellg + off;
}

void UncompressedFile::write(const char * s, std::streamsize n)
{
    /* extend data block, if new data exceeds end of m_data */
    if (m_tellp + n >= dataEnd()) {
        m_data.resize(static_cast<size_t>(m_tellp + n - m_dataBegin));
    }

    /* offset to write */
    std::streamoff offset = m_tellp - m_dataBegin;

    /* copy data */
    std::copy(s, s + n, m_data.begin() + offset);

    /* new put position */
    m_tellp += n;
}

std::streampos UncompressedFile::tellp()
{
    return m_tellp;
}

void UncompressedFile::seekp(std::streampos pos)
{
    assert(false);
}

void UncompressedFile::seekp(std::streamoff off, std::ios_base::seekdir way)
{
    assert(way == std::ios_base::cur);

    m_tellp += off;
}

void UncompressedFile::dropOldData(std::streamsize dropSize, std::streamsize remainingSize)
{
    /* check if drop should be done now */
    if (m_dataBegin + dropSize + remainingSize >= m_tellg) {
        /* don't drop yet */
        return;
    }

    /* drop data */
    m_data.erase(m_data.begin(), m_data.begin() + dropSize);
    m_dataBegin += dropSize;
}

std::streampos UncompressedFile::dataEnd() const
{
    return m_dataBegin + static_cast<std::streampos>(m_data.size());
}

}
}
