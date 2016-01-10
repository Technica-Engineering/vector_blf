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

#include "CompressedFile.h"

namespace Vector {
namespace BLF {

void CompressedFile::read(char * s, std::streamsize n)
{
    std::fstream::read(s, n);
}

std::streampos CompressedFile::tellg()
{
    return std::fstream::tellg();
}

void CompressedFile::seekg(std::streampos pos)
{
    std::fstream::seekg(pos);
}

void CompressedFile::seekg(std::streamoff off, std::ios_base::seekdir way)
{
    std::fstream::seekg(off, way);
}

void CompressedFile::write(const char * s, std::streamsize n)
{
    std::fstream::write(s, n);
}

std::streampos CompressedFile::tellp()
{
    return std::fstream::tellp();
}

}
}
