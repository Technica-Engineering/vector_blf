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

UncompressedFile::DataBlock::DataBlock() :
    DataBlock(0)
{
}

UncompressedFile::DataBlock::DataBlock(size_t size) :
    data(nullptr),
    tellg(nullptr),
    remainingSize(0)
{
    data = new char[size];
    if (data == nullptr) {
        std::cerr << "out of memory" << std::endl;
        return;
    }

    tellg = data;
    remainingSize = size;
}

UncompressedFile::DataBlock::~DataBlock()
{
    delete[] data;
    data = nullptr;
    tellg = nullptr;
    remainingSize = 0;
}

UncompressedFile::UncompressedFile() :
    tellp(0),
    tellg(0),
    gcount(0),
    content()
{
}

UncompressedFile::~UncompressedFile()
{
    /* delete all content blocks */
    while (!content.empty()) {
        delete content.front();
        content.pop();
    }
}

void UncompressedFile::write(const char * s, std::streamsize n)
{
    /* do nothing if block is empty */
    if (s == nullptr) {
        std::cerr << "write with nullptr argument" << std::endl;
        return;
    }
    if (n <= 0) {
        std::cerr << "write with null argument" << std::endl;
        return;
    }

    /* create a new data block */
    DataBlock * db = new DataBlock(n);
    memcpy(db->data, s, n);

    /* insert it into the content buffer */
    content.push(db);

    /* advance write pointer */
    tellp += n;
}

void UncompressedFile::read(char * s, std::streamsize n)
{
    gcount = 0;

    /* safety check */
    if (s == nullptr) {
        std::cerr << "read with nullptr argument" << std::endl;
        return;
    }

    /* while more should be read */
    while (gcount < n) {
        /* check if there are content blocks available */
        if (content.empty()) {
            std::cerr << "uncompressed data exhausted II: 0x" << std::hex << gcount << " < 0x" << n << std::endl;
            return;
        }

        /* read data from container */
        std::streamsize size = std::min(content.front()->remainingSize, n - gcount);
        memcpy(s, content.front()->tellg, size);
        content.front()->tellg += size;
        content.front()->remainingSize -= size;

        /* advance pointer */
        s += size;

        /* advance read pointer */
        tellg += size;

        /* increase read count */
        gcount += size;

        /* drop empty blocks */
        if (content.front()->remainingSize <= 0) {
            delete content.front();
            content.pop();
        }
    }
}

void UncompressedFile::skipg(std::streamsize n)
{
    std::streamsize scount = 0;

    /* while more should be read */
    while (scount < n) {
        /* check if there are content blocks available */
        if (content.empty()) {
            std::cerr << "uncompressed data exhausted III: 0x" << std::hex << gcount << " < 0x" << n << std::endl;
            return;
        }

        /* skip data from container */
        std::streamsize size = std::min(content.front()->remainingSize, n - scount);
        content.front()->tellg += size;
        content.front()->remainingSize -= size;

        /* advance read pointer */
        tellg += size;

        /* increase skip count */
        scount += size;

        /* drop empty blocks */
        if (content.front()->remainingSize <= 0) {
            delete content.front();
            content.pop();
        }
    }
}

std::streamsize UncompressedFile::size()
{
    return tellp - tellg;
}

}
}
