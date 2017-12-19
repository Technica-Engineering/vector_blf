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

#include <cassert>

namespace Vector {
namespace BLF {

CompressedFile::CompressedFile() :
    file()
{
}

std::streamsize CompressedFile::gcount() const
{
    return file.gcount();
}

void CompressedFile::read(char * s, std::streamsize n)
{
    file.read(s, n);
    if (gcount() < n) {
        throw std::runtime_error("CompressedFile::read incomplete");
    }
}

std::streampos CompressedFile::tellg()
{
    return file.tellg();
}

void CompressedFile::seekg(std::streampos pos)
{
    file.seekg(pos);
}

void CompressedFile::seekg(std::streamoff off, std::ios_base::seekdir way)
{
    file.seekg(off, way);
}

void CompressedFile::write(const char * s, std::streamsize n)
{
    file.write(s, n);
}

std::streampos CompressedFile::tellp()
{
    return file.tellp();
}

void CompressedFile::seekp(std::streampos pos)
{
    file.seekp(pos);
}

void CompressedFile::seekp(std::streamoff off, std::ios_base::seekdir way)
{
    file.seekp(off, way);
}

void CompressedFile::open(const char * filename, std::ios_base::openmode openMode)
{
    file.open(filename, openMode);
}

bool CompressedFile::is_open() const
{
    return file.is_open();
}

void CompressedFile::close()
{
    file.close();
}

bool CompressedFile::eof() const
{
    return file.eof();
}

}
}
