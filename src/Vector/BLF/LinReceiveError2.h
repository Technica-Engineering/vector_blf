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

#include "VectorTypes.h"
#include "ObjectHeader.h"
#include "LinDatabyteTimestampEvent.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_RCV_ERROR2
 */
class LinReceiveError2 : public ObjectHeader, public LinDatabyteTimestampEvent
{
public:
    LinReceiveError2();

    BYTE data[8]; /**< data bytes. */
    BYTE fsmId;
    BYTE fsmState;
    BYTE stateReason;
    BYTE offendingByte;
    BYTE shortError;
    BYTE timeoutDuringDlcDetection;
    BYTE isETF; /**< ETF collision flag */
    BYTE hasDatabytes;
    DWORD respBaudrate; /**< Response baudrate of the event in bit/sec */
    BYTE reserved[4]; /**< 4-byte alignment, reserved since BLF 3.9.3.0, BLF files from older versions may have junk data here */
    DOUBLE exactHeaderBaudrate; /**< Exact baudrate of the header in bit/sec */
    DWORD earlyStopbitOffset; /**< Early stop bit offset for UART timestamps in ns */
    DWORD earlyStopbitOffsetResponse; /**< Early stop bit offset in frame response for UART timestamps in ns */
};

}
}
