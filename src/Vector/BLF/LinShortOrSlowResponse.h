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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/LinDatabyteTimestampEvent.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_SHORT_OR_SLOW_RESPONSE
 *
 * This event occurs if a set of receive errors could be a valid header followed by a short
 * or slow response.
 */
struct VECTOR_BLF_EXPORT LinShortOrSlowResponse final : ObjectHeader, LinDatabyteTimestampEvent {
    LinShortOrSlowResponse();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief number of valid response bytes
     *
     * The number of response bytes.
     */
    uint32_t numberOfRespBytes {};

    /**
     * @brief the response bytes (can include the checksum)
     *
     * The response bytes (can include the
     * checksum).
     */
    std::array<uint8_t, 9> respBytes {};

    /**
     * @brief non-zero, if the response was too slow
     *
     * Non-zero, if the response was too
     * slow; otherwise zero.
     */
    uint8_t slowResponse {};

    /**
     * @brief non-zero, if the response was interrupted by a sync break
     *
     * Non-zero, if the response was
     * interrupted by a sync break;
     * otherwise zero.
     */
    uint8_t interruptedByBreak {};

    /** reserved */
    uint8_t reservedLinShortOrSlowResponse {};
};

}
}
