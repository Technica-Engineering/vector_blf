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

#include "mstream.h"

namespace std {

#ifdef USE_STRINGSTREAM_FOR_MSTREAM
#else

int membuf::overflow(int c)
{
}

int membuf::pbackfail(int c)
{
}

std::streampos membuf::seekoff(std::streamoff off, std::ios_base::seekdir way,
                       std::ios_base::openmode which)
{
}

std::streampos membuf::seekpos(std::streampos sp, std::ios_base::openmode which)
{
}

std::streambuf * membuf::setbuf(char * s, std::streamsize n)
{
}

std::streamsize membuf::showmanyc()
{
}

int membuf::uflow()
{
}

int membuf::underflow()
{
}

#endif

}
