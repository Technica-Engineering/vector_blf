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

#include <cstddef>

#include "VectorTypes.h"
#include "ObjectHeaderBase.h"

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
    virtual ~LogContainer();

    virtual char * parse(char * buffer);

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

    /** compressed file size in bytes */
    std::streamsize compressedFileSize;

    /** compressed file content */
    char * compressedFile;
};

}
}
