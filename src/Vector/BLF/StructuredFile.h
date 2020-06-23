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

#include <Vector/BLF/ObjectHeaderBase.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Generic interface to access StructuredCompressedFile and
 * StructuredUncompressedFile in the same way.
 */
struct VECTOR_BLF_EXPORT StructuredFile {
    virtual ~StructuredFile() = default;

    /* types */

    /** index offset */
    using indexoff = int32_t;

    /** index size */
    using indexsize = uint32_t;

    /** index position */
    using indexpos = uint32_t;

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
     * Read object.
     *
     * This operation blocks until the object is available.
     *
     * @param[out] objectHeaderBase object
     * @return Number of objects read (0 or 1)
     */
    virtual indexsize read(ObjectHeaderBase ** objectHeaderBase) = 0;

    /**
     * Get position in input sequence.
     *
     * @return Read position
     */
    virtual indexpos tellg() const = 0;

    /**
     * Set position in input sequence.
     *
     * @param[in] pos Position
     */
    virtual void seekg(const indexpos pos) = 0;

    /**
     * Set position in input sequence.
     *
     * @param[in] off Offset
     * @param[in] way Direction
     */
    virtual void seekg(const indexoff off, const std::ios_base::seekdir way) = 0;

    /* output methods */

    /**
     * Write object.
     *
     * @param[in] objectHeaderBase object
     * @return Number of objects written (0 or 1)
     */
    virtual indexsize write(ObjectHeaderBase * objectHeaderBase) = 0;

    /**
     * Get position in output sequence.
     *
     * @return Write position
     */
    virtual indexpos tellp() const = 0;

    /**
     * Get file size
     *
     * @return file size
     */
    virtual indexsize size() const = 0;
};

}
}
