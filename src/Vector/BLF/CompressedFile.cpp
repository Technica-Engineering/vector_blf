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

#include <Vector/BLF/CompressedFile.h>

namespace Vector {
namespace BLF {

CompressedFile::CompressedFile() :
    m_file(),
    m_mutex()
{
}

CompressedFile::~CompressedFile()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    close();
}

std::streamsize CompressedFile::gcount() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.gcount();
}

void CompressedFile::read(char * s, std::streamsize n)
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.read(s, n);
}

std::streampos CompressedFile::tellg()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.tellg();
}

void CompressedFile::seekg(std::streamoff off, const std::ios_base::seekdir way)
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.seekg(off, way);
}

void CompressedFile::write(const char * s, std::streamsize n)
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.write(s, n);
}

std::streampos CompressedFile::tellp()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.tellp();
}

bool CompressedFile::good() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.good();
}

bool CompressedFile::eof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.eof();
}

void CompressedFile::open(const char * filename, std::ios_base::openmode openMode)
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.open(filename, openMode);
}

bool CompressedFile::is_open() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.is_open();
}

void CompressedFile::close()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.close();
}

void CompressedFile::seekp(std::streampos pos)
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.seekp(pos);
}

}
}
