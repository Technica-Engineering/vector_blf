/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <ios>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Generic interface to access RawCompressedFile and RawUncompressedFile in the
 * same way.
 */
struct VECTOR_BLF_EXPORT RawFile {
    virtual ~RawFile() = default;

    /* types */

    /** stream offset */
    using streamoff = std::streamoff;

    /** stream size */
    using streamsize = std::streamsize;

    /** stream position */
    using streampos = std::streampos;

    /* general methods */

    /**
     * open file
     *
     * @param[in] filename file name
     * @param[in] mode open in read or write mode
     */
    virtual void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in) = 0;

    /**
     * is file open?
     *
     * @return true if file is open
     */
    virtual bool is_open() const = 0;

    /** Close file. */
    virtual void close() = 0;

    /* input methods */

    /**
     * Read block of data.
     *
     * This operation blocks until the data is available.
     *
     * @param[out] s Pointer to data
     * @param[in] n Requested size of data
     * @return Size of data read
     */
    virtual streamsize read(char * s, streamsize n) = 0;

    /**
     * Get position in input sequence.
     *
     * @return Read position
     */
    virtual streampos tellg() = 0;

    /**
     * Set position in input sequence.
     *
     * @param[in] pos Position
     */
    virtual void seekg(const streampos pos) = 0;

    /**
     * Set position in input sequence.
     *
     * @param[in] off Offset
     * @param[in] way Direction
     */
    virtual void seekg(const streamoff off, const std::ios_base::seekdir way) = 0;

    /* output methods */

    /**
     * Write block of data.
     *
     * @param[in] s Pointer to data
     * @param[in] n Size of data
     * @return Size of data written
     */
    virtual streamsize write(const char * s, streamsize n) = 0;

    /**
     * Get position in output sequence.
     *
     * @return Write position
     */
    virtual streampos tellp() = 0;

    /**
     * Set position in output sequence.
     *
     * @note seekp writes zeros if it goes beyond eof.
     *
     * @param[in] pos Position
     */
    virtual void seekp(const streampos pos) = 0;

    /**
     * Set position in output sequence.
     *
     * @note seekp writes zeros if it goes beyond eof.
     *
     * @param[in] off Offset
     * @param[in] way Direction
     */
    virtual void seekp(const streamoff off, const std::ios_base::seekdir way) = 0;

    /**
     * Get file size
     *
     * @return file size
     */
    virtual streamsize size() const = 0;
};

}
}
