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

#pragma once

/** @todo till there is an efficient implementation for a mstream that forgets the past... */
#define USE_STRINGSTREAM_FOR_MSTREAM

#ifdef USE_STRINGSTREAM_FOR_MSTREAM
#include <sstream>
#else
#include <istream>
#include <ostream>
#include <streambuf>
#endif

namespace std {

#ifdef USE_STRINGSTREAM_FOR_MSTREAM

using membuf = stringbuf;
using imstream = istringstream;
using mstream = stringstream;
using omstream = ostringstream;

#else

/**
 * Memory stream buffer (similar to filebuf/stringbuf)
 */
class membuf : public streambuf
{
protected:
    int overflow(int c = EOF);

    int pbackfail(int c = EOF);

    std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way,
                           std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);

    std::streampos seekpos(std::streampos sp, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);

    std::streambuf * setbuf(char * s, std::streamsize n);

    std::streamsize showmanyc();

    int uflow();

    int underflow();
};

/**
 * Input memory stream (similar to ifstream/istringstream)
 */
class imstream : public istream
{
};

/**
 * Input/output memory stream (similar to fstream/stringstream)
 */
class mstream : public iostream
{
};

/**
 * Output memory stream (similar to ofstream/ostringstream)
 */
class omstream : public ostream
{
};

#endif

}
