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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief UNKNOWN_115
 *
 * This always comes at the end of a file.
 */
struct VECTOR_BLF_EXPORT Unknown115 final : public ObjectHeader {
    Unknown115();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    DWORD calculateObjectSize() const override;

    /* @todo unclear what the following values mean */
    uint64_t unknown0{};
    uint64_t unknown1{};
    uint64_t unknown2{};

    struct UnknownDataBlock {
        uint64_t timeStamp; // unit: ns
        uint64_t uncompressedFileSize; // unit: bytes
        uint32_t value; // @todo unknown value
        uint32_t flags; // @todo looks like some kind of flags field

        static DWORD calculateObjectSize();
    };
    std::vector<UnknownDataBlock> unknownData {};

    std::vector<uint8_t> reservedUnknown115 {};
};

}
}
