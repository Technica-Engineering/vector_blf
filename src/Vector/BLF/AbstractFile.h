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

#include <Vector/BLF/platform.h>

#include <iostream>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/** Generic interface to access CompressedFile and UncompressedFile in the same way */
class VECTOR_BLF_EXPORT AbstractFile
{
public:
    virtual ~AbstractFile();

    /**
     * Get characters returned by last read operation
     *
     * @return Number of characters
     */
    virtual std::streamsize gcount() const = 0;

    /**
     * Read block of data
     *
     * @param[out] s Pointer to data
     * @param[in] n Requested size of data
     */
    virtual void read(char * s, std::streamsize n) = 0;

    /**
     * Get position in input sequence
     *
     * @return Read position
     */
    virtual std::streampos tellg() = 0;

    /**
     * Set position in input sequence
     *
     * @param[in] off Offset
     * @param[in] way Direction
     */
    virtual void seekg(std::streamoff off, std::ios_base::seekdir way) = 0;

    /**
     * Write block of data
     *
     * @param[in] s Pointer to data
     * @param[in] n Size of data
     */
    virtual void write(const char * s, std::streamsize n) = 0;

    /**
     * Get position in input sequence
     *
     * @return Write position
     */
    virtual std::streampos tellp() = 0;

    /**
     * Set position in output sequence
     *
     * @param[in] off Offset
     * @param[in] way Direction
     */
    virtual void seekp(std::streamoff off, std::ios_base::seekdir way) = 0;

    /**
     * close file
     */
    virtual void close() = 0;
};

}
}
