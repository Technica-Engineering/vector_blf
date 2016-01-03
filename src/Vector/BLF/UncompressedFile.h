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

#include <iostream>
#include <queue>

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * This class is actually a memory buffer.
 *
 * The write procedure puts the data and and the read procedure gets the data out.
 * tellp and tellg are the write and read pointers.
 *
 * Read data automatically gets freed again. Therefore there is no seek
 * operation to rewind.
 */
class VECTOR_BLF_EXPORT UncompressedFile {
public:
    UncompressedFile();
    virtual ~UncompressedFile();

    /**
     * Write block of data
     *
     * @param s pointer to buffer
     * @param n bytes to write
     */
    void write(const char * s, std::streamsize n);

    /** Write position */
    std::streampos tellp;

    /**
     * Read block of data
     *
     * @param s pointer to buffer
     * @param n bytes to read
     */
    void read(char * s, std::streamsize n);

    /** Read position */
    std::streampos tellg;

    /**
     * skip block of data
     *
     * @param n number of bytes to skip
     */
    void skipg(std::streamsize n);

    /** Get character count */
    std::streamsize gcount;

    /**
     * Get the remaining size
     *
     * @return size
     */
    std::streamsize size();

private:
    /** a data block */
    struct DataBlock {
        DataBlock();
        DataBlock(size_t size);
        virtual ~DataBlock();

        /** data */
        char * data;

        /** read pointer */
        char * tellg;

        /** remaining size */
        std::streamsize remainingSize;
    };

    /** contains the file content in blocks */
    std::queue<DataBlock *> content;
};

}
}
