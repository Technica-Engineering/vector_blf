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

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_RCV_ERROR
 *
 * @deprecated
 *
 * This event may have a wide variety of causes.
 *
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
class VECTOR_BLF_EXPORT LinReceiveError : public ObjectHeader
{
public:
    LinReceiveError();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Channel number where the event notified
     */
    WORD channel;

    /**
     * @brief LIN ID
     *
     * Frame identifier
     */
    BYTE id;

    /**
     * @brief LIN DLC
     *
     * Frame length
     */
    BYTE dlc;

    /**
     * Slave Identifier in the Final State
     * Machine (obsolete)
     */
    BYTE fsmId;

    /**
     * State Identifier of a Slave in the Final
     * State Machine (obsolete)
     */
    BYTE fsmState;

    /**
     * Duration of the frame header [in bit
     * times]
     */
    BYTE headerTime;

    /**
     * Duration of the entire frame [in bit times]
     */
    BYTE fullTime;

    /**
     * The lower 4 bits indicate the LIN hardware
     * state at the time the error has
     * occurred, while the upper 4 bits indicate
     * the reason of the error
     *
     * Value for the state:
     *   - 0: Bus idle
     *   - 1: Waiting for SynchBreak
     *   - 2: Waiting for SynchField
     *   - 3: Waiting for frame ID
     *   - 4-12: Waiting for data byte or checksum
     *     byte depending on the frame length. E.g.
     *     value 4 for FrameLength=0, value 12 for
     *     FrameLength=8
     *   - 15: Not expected event (i.e. not
     *     WakeupRequest) during sleep mode.
     *     Occurs for LIN hardware in Master mode
     *     only
     *
     * Values for the reason:
     *   - 0: Timeout
     *   - 1: Received an unexpected byte violating
     *     protocol. In this case, offendingByte
     *     member contains its value
     *   - 2: Received a byte with framing error
     *     (with dominant stop bit). In this case,
     *     offendingByte member contains its
     *     value
     *   - 3: Unexpected Break field
     *   - 4: Unidentified error
     */
    BYTE stateReason;

    /**
     * Byte value that resulted the protocol
     * violation. Only valid for certain values of
     * stateReason
     */
    BYTE offendingByte;

    /**
     * Specifies the detail level of the event.
     * Following values are possible:
     *   - 0: short
     *   - 1: full
     * Most members are not valid unless this
     * member is 1
     */
    BYTE shortError;

    /**
     * Flag indicating if the error is a result of
     * an attempt to resolve frame length.
     * Following values are possible:
     *   - 0: False
     *   - 1: True
     */
    BYTE timeoutDuringDlcDetection;
};

}
}
