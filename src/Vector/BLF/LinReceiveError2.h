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
#include "LinDatabyteTimestampEvent.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_RCV_ERROR2
 *
 * This event may have a wide variety of causes.
 * An external Master can cause a receive error event:
 *   - by transmitting sync break that is too short,
 *   - by not returning the correct value 0x55 in the sync field,
 *   - by assigning an incorrect parity to the frame identifier.
 * Other reasons:
 *   - Slave transmitting an illegal character during a Bus Idle phase (e.g. because it did not
 *     finish transmission quickly enough and the checksum byte of the response was sent during
 *     the Bus Idle phase),
 *   - Faulty (dominant) stop bit (i.e. framing error),
 *   - LIN hardware receives a character that is different from the character sent during
 *     transmission
 *   - LIN hardware only receives part of a frame, at the start of a measurement (in a correctly
 *     functioning system).
 */
class VECTOR_BLF_EXPORT LinReceiveError2 : public ObjectHeader, public LinDatabyteTimestampEvent
{
public:
    LinReceiveError2();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief data bytes.
     */
    std::array<BYTE, 8> data;

    /**
     * Slave Identifier in the
     * Final State Machine
     * (obsolete)
     */
    BYTE fsmId;

    /**
     * State Identifier of a Slave in
     * the Final State Machine
     * (obsolete)
     */
    BYTE fsmState;

    /**
     * The lower 4 bits indicate the
     * LIN hard-ware state at the
     * time the error has occurred,
     * while the upper 4 bits
     * indicate the reason of the
     * error
     *
     * Value for the state:
     *   - 0: Bus idle
     *   - 1: Waiting for SynchBreak
     *   - 2: Waiting for SynchField
     *   - 3: Waiting for frame ID
     *   - 4-12: Waiting for data byte
     *     or checksum byte depending
     *     on the frame length. E.g.
     *     value 4 for FrameLength=0,
     *     value 12 for FrameLength=8
     *   - 14: Consecutive event (i.e.
     *     event resulting from further
     *     data interpretation, after
     *     already notified error for
     *     first offending byte)
     *   - 15: Not expected event (i.e.
     *     not WakeupRequest) during
     *     sleep mode. Occurs for LIN
     *     hardware in Master mode
     *     only
     *
     * Values for the reason:
     *   - 0: Timeout
     *   - 1: Received an unexpected
     *     byte violating protocol. In
     *     this case, mOffendingByte
     *     member contains its value
     *   - 2: Received a byte with
     *     framing error (with
     *     dominant stop bit). In this
     *     case, mOffendingByte
     *     member contains its value
     *   - 3: Unexpected Break field
     *   - 4: Unidentified error
     */
    BYTE stateReason;

    /**
     * Byte value that resulted the
     * protocol violation. Only
     * valid for certain values of
     * mStateReason
     */
    BYTE offendingByte;

    /**
     * Specifies the detail level of
     * the event. Following values
     * are possible:
     *   - 0: short
     *   - 1: full
     * Most members are not valid
     * unless this member is 1
     */
    BYTE shortError;

    /**
     * Flag indicating if the error is
     * a result of an attempt to
     * resolve frame length.
     * Following values are
     * possible:
     *   - 0: False
     *   - 1: True
     */
    BYTE timeoutDuringDlcDetection;

    /**
     * @brief ETF collision flag
     *
     * Flag indicating whether this
     * frame is Event-Triggered
     * one:
     *   - 0: not ETF
     *   - 1: ETF
     */
    BYTE isEtf;

    /**
     * Flag indicating whether at
     * least one data byte value is
     * valid
     */
    BYTE hasDatabytes;

    /* the following variables are only available in Version 2 and above */

    /**
     * @brief Response baudrate of the event in bit/sec
     *
     * Event's baudrate
     * measured in response [in
     * bits/sec]
     */
    DWORD respBaudrate;

    /** reserved */
    std::array<BYTE, 4> reserved;

    /* the following variables are only available in Version 3 and above */

    /**
     * @brief Exact baudrate of the header in bit/sec
     *
     * Event's baudrate
     * measured in header [in
     * bits/sec]
     */
    DOUBLE exactHeaderBaudrate;

    /**
     * @brief Early stop bit offset for UART timestamps in ns
     *
     * Early stop bit offset in
     * frame header for UART
     * timestamps [in ns]
     */
    DWORD earlyStopbitOffset;

    /**
     * @brief Early stop bit offset in frame response for UART timestamps in ns
     *
     * Early stop bit offset in
     * frame response for
     * UART timestamps [in ns]
     */
    DWORD earlyStopbitOffsetResponse;
};

}
}
