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

#include "platform.h"

#include <vector>

#include "AbstractFile.h"
#include "ObjectHeaderBase.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LOG_CONTAINER
 */
class VECTOR_BLF_EXPORT LogContainer : public ObjectHeaderBase
{
public:
    LogContainer();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief object flags (usually BL_OBJ_FLAG_TIME_ONE_NANS)
     */
    DWORD objectFlags;

    /**
     * @brief reserved
     */
    WORD reserved;

    /**
     * @brief object specific version (usually 0)
     */
    WORD objectVersion;

    /**
     * @brief uncompressed file size in bytes
     */
    ULONGLONG uncompressedFileSize;

    /** compressed file content */
    std::vector<uint8_t> compressedFile;

    /** compressed file size in bytes */
    std::streamsize compressedFileSize;

    /**
     * internalHeaderSize returns the size of all headers.
     * @note Not to be mixed with headerSize, which is only takes ObjectHeaderBase headers into account.
     * @return Size of all headers.
     */
    size_t internalHeaderSize();
};

}
}
