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

#include <array>
#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * compact serial event
 */
struct VECTOR_BLF_EXPORT CompactSerialEvent final {
    CompactSerialEvent() = default;
    virtual ~CompactSerialEvent() noexcept = default;
    CompactSerialEvent(const CompactSerialEvent &) = default;
    CompactSerialEvent & operator=(const CompactSerialEvent &) = default;
    CompactSerialEvent(CompactSerialEvent &&) = default;
    CompactSerialEvent & operator=(CompactSerialEvent &&) = default;

    /** @copydoc ObjectHeader::read */
    virtual void read(AbstractFile & is);

    /** @copydoc ObjectHeader::write */
    virtual void write(AbstractFile & os);

    /** @copydoc ObjectHeader::calculateObjectSize */
    virtual uint32_t calculateObjectSize() const;

    /** compact length */
    uint8_t compactLength {};

    /** compact data */
    std::array<uint8_t, 15> compactData {};
};

}
}
