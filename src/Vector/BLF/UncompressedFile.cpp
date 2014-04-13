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

#include "UncompressedFile.h"

#include <cstring>

namespace Vector {
namespace BLF {

UncompressedFile::UncompressedFile() :
    tellp(0),
    tellg(0),
    gcount(0),
    content()
{
}

UncompressedFile::~UncompressedFile()
{
    while (!content.empty()) {
        delete content.front().data;
        content.pop();
    }
}

void UncompressedFile::write(const char * s, std::streamsize n)
{
    /* create a new data block */
    DataBlock db;
    db.data = new char[n];
    db.tellg = db.data;
    db.size = n;
    db.remainingSize = n;
    memcpy(db.data, s, n);

    /* insert it into the content buffer */
    content.push(db);

    /* advance write pointer */
    tellp += n;
}

void UncompressedFile::read(char * s, std::streamsize n)
{
    gcount = 0;

    /* nothing to read */
    while (n > 0) {
        /* no content left to read */
        if (content.empty()) {
            return;
        }

        /* consume container */
        std::streamsize size = std::min(content.front().remainingSize, n);
        memcpy(s, content.front().tellg, size);
        content.front().tellg += size;
        content.front().remainingSize -= size;

        /* increase read count */
        gcount += size;

        /* reduce size to read */
        n -= size;

        /* advance read pointer */
        tellg += size;

        /* drop block if empty */
        if (content.front().remainingSize == 0) {
            delete content.front().data;
            content.pop();
        }
    }
}

void UncompressedFile::skipg(std::streamsize n)
{
    /* nothing to read */
    while (n > 0) {
        /* no content left to read */
        if (content.empty()) {
            return;
        }

        /* consume container */
        std::streamsize size = std::min(content.front().remainingSize, n);
        content.front().tellg += size;
        content.front().remainingSize -= size;

        /* reduce size to read */
        n -= size;

        /* advance read pointer */
        tellg += size;

        /* drop block if empty */
        if (content.front().remainingSize == 0) {
            delete content.front().data;
            content.pop();
        }
    }
}

std::streamsize UncompressedFile::size()
{
    return tellp-tellg;
}

}
}
