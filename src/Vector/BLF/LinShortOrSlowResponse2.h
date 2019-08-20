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

#include <Vector/BLF/platform.h>

#include <array>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/LinDatabyteTimestampEvent.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_SHORT_OR_SLOW_RESPONSE2
 */
class VECTOR_BLF_EXPORT LinShortOrSlowResponse2 final : public ObjectHeader, public LinDatabyteTimestampEvent
{
public:
    LinShortOrSlowResponse2();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * @brief number of valid response bytes
     *
     * The number of response bytes.
     */
    ULONG numberOfRespBytes {};

    /**
     * @brief the response bytes (can include the checksum)
     *
     * The response bytes (can include the
     * checksum).
     */
    std::array<BYTE, 9> respBytes {};

    /**
     * @brief non-zero, if the response was too slow
     *
     * Non-zero, if the response was too
     * slow; otherwise zero.
     */
    BYTE slowResponse {};

    /**
     * @brief non-zero, if the response was interrupted by a sync break
     *
     * Non-zero, if the response was
     * interrupted by a sync break;
     * otherwise zero.
     */
    BYTE interruptedByBreak {};

    /** reserved */
    BYTE reservedLinShortOrSlowResponse1 {};

    /**
     * @brief Exact baudrate of the header in bit/sec
     *
     * Event's baudrate measured in
     * header [in bits/sec]
     */
    DOUBLE exactHeaderBaudrate {};

    /**
     * @brief Early stop bit offset for UART timestamps in ns
     *
     * Early stop bit offset in frame
     * header for UART timestamps
     * [in ns]
     */
    DWORD earlyStopbitOffset {};

    /** reserved */
    DWORD reservedLinShortOrSlowResponse2 {};
};

}
}
