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

#include <Vector/BLF/LinMessageDescriptor.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_SND_ERROR2
 *
 * This event occurs when no Slave responds to a frame header from Master.
 */
struct VECTOR_BLF_EXPORT LinSendError2 final : ObjectHeader, LinMessageDescriptor {
    LinSendError2();

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /**
     * @brief EndOfHeader timestamp
     *
     * End of header timestamp [in nanosecond]
     */
    ULONGLONG eoh {};

    /**
     * @brief Event-triggered frame
     *
     * Flag indicating whether this frame is Event-
     * Triggered one:
     *   - 0: not ETF
     *   - 1: ETF
     */
    BYTE isEtf {};

    /**
     * Slave Identifier in the Final State
     * Machine (obsolete)
     */
    BYTE fsmId {};

    /**
     * State Identifier of a Slave in the Final State
     * Machine (obsolete)
     */
    BYTE fsmState {};

    /** reserved */
    BYTE reservedLinSendError1 {};

    /* the following variables are only available in Version 2 and above */

    /** reserved */
    DWORD reservedLinSendError2 {};

    /* the following variables are only available in Version 3 and above */

    /**
     * @brief Exact baudrate of the header in bit/sec
     *
     * Event's baudrate measured in header
     * [in bits/sec]
     */
    DOUBLE exactHeaderBaudrate {};

    /**
     * @brief Early stop bit offset for UART timestamps in ns
     *
     * Early stop bit offset in frame header
     * for UART timestamps [in ns]
     */
    DWORD earlyStopbitOffset {};

    /** reserved */
    DWORD reservedLinSendError3 {};
};

}
}
