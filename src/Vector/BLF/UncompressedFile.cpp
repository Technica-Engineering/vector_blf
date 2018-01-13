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

void UncompressedFile::open()
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

void UncompressedFile::close()
{
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait till the queue is empty */
    m_tellgChanged.wait(lock, [this]{
       return m_tellg >= m_tellp;
    });
}

std::streamsize UncompressedFile::gcount() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_gcount;
}

void UncompressedFile::read(char * s, std::streamsize n)
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        /* wait until there is sufficient data */
        m_tellpChanged.wait(lock, [this, n]{
            return
                (m_tellg + n <= m_tellp) ||
                (m_tellg + n > m_fileSize);
        });

        /* handle read behind eof */
        if (m_tellg + n > m_fileSize) {
            n = m_fileSize - m_tellg;
            m_rdstate = std::ios_base::eofbit;
        } else {
            m_rdstate = std::ios_base::goodbit;
        }

        /* copy data */
        if (n > 0) {
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
        m_data.resize(static_cast<size_t>(newTellp - m_dataBegin), 0);

        /* offset to write */
        std::streamoff offset = m_tellp - m_dataBegin;

        /* copy data */
        std::copy(s, s + n, m_data.begin() + offset);

        /* new put position */
        m_tellp += n;

        /* if new position is behind eof, shift it */
        if (m_tellp >= m_fileSize) {
            m_fileSize = m_tellp;
        }
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

bool UncompressedFile::atEof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* next is eof */
    return (m_tellp >= m_fileSize);
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
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* check if drop should be done now */
    if ((m_dataBegin + dropSize > m_tellg) || (m_dataBegin + dropSize > m_tellp) || (m_dataBegin + dropSize > m_fileSize)) {
        /* don't drop yet */
        return;
    }

    /* drop data */
    m_data.erase(m_data.begin(), m_data.begin() + dropSize);
    m_dataBegin += dropSize;
}

}
}
