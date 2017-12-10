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
class VECTOR_BLF_EXPORT LogContainer final : public ObjectHeaderBase
{
public:
    LogContainer();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * @brief reserved
     */
    ULONGLONG reserved1; // @todo often 0x02

    /**
     * @brief uncompressed file size in bytes
     */
    DWORD uncompressedFileSize;

    /** reserved */
    DWORD reserved2; // @todo often 0x0215, 0x9a, 0, 0x0c

    /** compressed file content */
    std::vector<uint8_t> compressedFile;

    /** compressed file size in bytes */
    DWORD compressedFileSize;

    /**
     * internalHeaderSize returns the size of all headers.
     * @note Not to be mixed with headerSize, which only takes ObjectHeaderBase headers into account.
     * @return Size of all headers.
     */
    WORD internalHeaderSize() const;
};

}
}
