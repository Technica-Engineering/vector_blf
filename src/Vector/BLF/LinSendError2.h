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

#include <array>

#include "AbstractFile.h"
#include "LinMessageDescriptor.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_SND_ERROR2
 *
 * This event occurs when no Slave responds to a frame header from Master.
 */
class VECTOR_BLF_EXPORT LinSendError2 : public ObjectHeader, public LinMessageDescriptor
{
public:
    LinSendError2();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief EndOfHeader timestamp
     *
     * End of header timestamp [in nanosecond]
     */
    ULONGLONG eoh;

    /**
     * @brief Event-triggered frame
     *
     * Flag indicating whether this frame is Event-
     * Triggered one:
     *   - 0: not ETF
     *   - 1: ETF
     */
    BYTE isEtf;

    /**
     * Slave Identifier in the Final State
     * Machine (obsolete)
     */
    BYTE fsmId;

    /**
     * State Identifier of a Slave in the Final State
     * Machine (obsolete)
     */
    BYTE fsmState;

    /** reserved */
    BYTE reserved1;

    /* the following variables are only available in Version 2 and above */

    /** reserved */
    std::array<BYTE, 4> reserved2;

    /* the following variables are only available in Version 3 and above */

    /**
     * @brief Exact baudrate of the header in bit/sec
     *
     * Event's baudrate measured in header
     * [in bits/sec]
     */
    DOUBLE exactHeaderBaudrate;

    /**
     * @brief Early stop bit offset for UART timestamps in ns
     *
     * Early stop bit offset in frame header
     * for UART timestamps [in ns]
     */
    DWORD earlyStopbitOffset;

    /** reserved */
    std::array<BYTE, 4> reserved3;
};

}
}
