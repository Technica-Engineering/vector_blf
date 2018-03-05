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
    m_file()
{
}

CompressedFile::~CompressedFile()
{
    close();
}

std::streamsize CompressedFile::gcount() const
{
    return m_file.gcount();
}

void CompressedFile::read(char * s, std::streamsize n)
{
    m_file.read(s, n);
}

std::streampos CompressedFile::tellg()
{
    return m_file.tellg();
}

void CompressedFile::seekg(std::streamoff off, const std::ios_base::seekdir way)
{
    m_file.seekg(off, way);
}

void CompressedFile::write(const char * s, std::streamsize n)
{
    m_file.write(s, n);
}

std::streampos CompressedFile::tellp()
{
    return m_file.tellp();
}

bool CompressedFile::good() const
{
    return m_file.good();
}

bool CompressedFile::eof() const
{
    return m_file.eof();
}

void CompressedFile::open(const char * filename, std::ios_base::openmode openMode)
{
    m_file.open(filename, openMode);
}

bool CompressedFile::is_open() const
{
    return m_file.is_open();
}

void CompressedFile::close()
{
    m_file.close();
}

void CompressedFile::seekp(std::streampos pos)
{
    m_file.seekp(pos);
}

}
}
