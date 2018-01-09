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

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

UncompressedFile::UncompressedFile() :
    m_data(),
    m_dataBegin(0),
    m_tellg(0),
    m_tellgChanged(),
    m_tellp(0),
    m_tellpChanged(),
    m_gcount(0),
    m_fileSize(0x7fffffffffffffff),
    m_rdstate(std::ios_base::goodbit),
    m_mutex()
{
}

void UncompressedFile::close()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* reset data buffer */
    m_data.clear();
    m_dataBegin = 0;
    m_tellg = 0;
    m_tellp = 0;
    m_gcount = 0;
    m_fileSize = 0x7fffffffffffffff;
    m_rdstate = std::ios_base::goodbit;
}

std::streamsize UncompressedFile::gcount() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_gcount;
}

void UncompressedFile::read(char * s, std::streamsize n)
{
    /* check for eof */
    if (eof()) {
        return;
    }

    {
        std::unique_lock<std::mutex> lock(m_mutex);

        /* wait until there is sufficient data */
        std::cout << "UncompressedFile::read(): wait for sufficient data" << std::endl;
        m_tellpChanged.wait(lock, [this, n]{
            std::cout << "UncompressedFile: m_tellg=0x" << std::hex << m_tellg << std::endl;
            std::cout << "UncompressedFile: m_tellp=0x" << std::hex << m_tellp << std::endl;
            std::cout << "UncompressedFile: m_fileSize=0x" << std::hex << m_fileSize << std::endl;
            return (m_tellg + n <= m_tellp) || (m_tellg + n > m_fileSize);
        });

        /* handle read behind eof */
        if (m_tellg + n > m_fileSize) {
            std::cout << "UncompressedFile::read(): read behind eof" << std::endl;
            m_rdstate = std::ios_base::eofbit;
            n = m_fileSize - m_tellg;
        } else {
            m_rdstate = std::ios_base::goodbit;
        }

        /* copy data */
        if (n > 0) {
            std::cout << "UncompressedFile::read(): copy data" << std::endl;
            /* offset to read */
            std::streamoff offset = m_tellg - m_dataBegin;

            /* copy data */
            std::copy(m_data.begin() + offset, m_data.begin() + offset + n, s);

        }

        /* remember get count */
        m_gcount = n;

        /* new get position */
        m_tellg += n;
    }

    /* notify */
    m_tellgChanged.notify_all();
}

std::streampos UncompressedFile::tellg()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellg;
}

void UncompressedFile::seekg(std::streamoff off, const std::ios_base::seekdir /*way*/)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* new get position */
        m_tellg += off;
    }

    /* notify */
    m_tellgChanged.notify_all();
}

void UncompressedFile::write(const char * s, std::streamsize n)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* extend data block */
        std::streampos newTellp = m_tellp + n;
        m_data.resize(static_cast<size_t>(newTellp - m_dataBegin));

        /* offset to write */
        std::streamoff offset = m_tellp - m_dataBegin;

        /* copy data */
        std::copy(s, s + n, m_data.begin() + offset);

        /* new put position */
        m_tellp += n;
    }

    /* notify */
    m_tellpChanged.notify_all();
}

std::streampos UncompressedFile::tellp()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellp;
}

void UncompressedFile::seekp(std::streamoff off, const std::ios_base::seekdir /*way*/)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* new put position */
        m_tellp += off;
    }

    /* notify */
    m_tellpChanged.notify_all();
}

bool UncompressedFile::eof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_rdstate & std::ios_base::eofbit);
}

void UncompressedFile::setFileSize(std::streamsize fileSize)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* set eof at m_dataEnd */
        m_fileSize = fileSize;
    }

    /* notify */
    m_tellpChanged.notify_all();
}

std::streamsize UncompressedFile::size() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* size between put/write and get/read positions */
    return (m_tellp - m_tellg);
}

void UncompressedFile::dropOldData(std::streamsize dropSize)
{
    /* check if drop should be done now */
    if ((m_dataBegin + dropSize > m_tellg) || (m_dataBegin + dropSize > m_tellp)) {
        /* don't drop yet */
        return;
    }

    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* drop data */
        m_data.erase(m_data.begin(), m_data.begin() + dropSize);
        m_dataBegin += dropSize;
    }
}

}
}
