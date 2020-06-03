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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectType.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/** object signature */
const DWORD ObjectSignature = 0x4A424F4C; /* LOBJ */

/**
 * @brief Base object header type definition
 *
 * Object header base structure.
 */
struct VECTOR_BLF_EXPORT ObjectHeaderBase {
    ObjectHeaderBase(const WORD headerVersion, const ObjectType objectType);
    virtual ~ObjectHeaderBase() noexcept = default;
    ObjectHeaderBase(const ObjectHeaderBase &) = default;
    ObjectHeaderBase & operator=(const ObjectHeaderBase &) = default;
    ObjectHeaderBase(ObjectHeaderBase &&) = default;
    ObjectHeaderBase & operator=(ObjectHeaderBase &&) = default;

    /**
     * Read the data of this object
     *
     * @param[in] is input stream
     */
    virtual void read(AbstractFile & is);

    /**
     * Write the data of this object
     *
     * @param[in] os output stream
     */
    virtual void write(AbstractFile & os);

    /**
     * Calculates the headerSize
     *
     * @return header size
     */
    virtual WORD calculateHeaderSize() const;

    /**
     * Calculates the objectSize
     *
     * @return object size
     */
    virtual DWORD calculateObjectSize() const;

    /**
     * @brief signature (ObjectSignature)
     *
     * Object signature, must be ObjectSignature.
     */
    DWORD signature {ObjectSignature};

    /**
     * @brief sizeof object header
     *
     * Size of header in bytes, set this member to
     * sizeof(ObjectHeader) or
     * sizeof(ObjectHeader2) depending on
     * the object header type used for the object.
     */
    WORD headerSize {};

    /**
     * @brief header version (1)
     *
     * Version number of object header.
     *
     * Set this member to 1 if the object has a member
     * of type ObjectHeader.
     *
     * Set this member to 2 if the object has a member
     * of type ObjectHeader2.
     *
     * @note is set in ObjectHeader/ObjectHeader2
     */
    WORD headerVersion {};

    /**
     * @brief object size
     *
     * Object size in bytes.
     */
    DWORD objectSize {};

    /**
     * @brief object type
     *
     * Object type.
     *
     * @note is set in each event class constructor
     */
    ObjectType objectType {};
};

}
}
