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

#include <vector>

#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief UNKNOWN_115
 *
 * This always comes at the end of a file.
 *
 * @note It's not clear yet what this is. RestorePoint? Metadata?
 */
struct VECTOR_BLF_EXPORT Unknown115 final : public ObjectHeader {
    Unknown115();

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /** Unknown 64-bit value */
    uint64_t unknown0{};

    /** Unknown 64-bit value */
    uint64_t unknown1{};

    /** Unknown 64-bit value */
    uint64_t unknown2{};

    /** Data Block */
    struct UnknownDataBlock {
        /** time stamp (in ns) */
        uint64_t timeStamp;

        /** uncompressed file size (in bytes) */
        uint64_t uncompressedFileSize;

        /** @todo unknown value */
        uint32_t value;

        /** @todo looks like some kind of flags field */
        uint32_t flags;

        /** @copydoc ObjectHeaderBase::calculateObjectSize() */
        static DWORD calculateObjectSize();
    };

    /** @copydoc UnknownDataBlock */
    std::vector<UnknownDataBlock> unknownData {};

    /** reserved */
    std::vector<uint8_t> reservedUnknown115 {};
};

}
}
