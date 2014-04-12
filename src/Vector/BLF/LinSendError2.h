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
#include "LinMessageDescriptor.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_SND_ERROR2
 */
class LinSendError2 : public ObjectHeader, public LinMessageDescriptor
{
public:
    LinSendError2();

    ULONGLONG eoh; /**< EndOfHeader timestamp */
    BYTE isETF; /**< Event-triggered frame */
    BYTE fsmId;
    BYTE fsmState;
    BYTE reserved; /**< 4-byte alignment */
    BYTE reserved2[4]; /**< 4-byte alignment, reserved since BLF 3.9.3.0, BLF files from older versions may have junk data here */
    DOUBLE exactHeaderBaudrate; /**< Exact baudrate of the header in bit/sec */
    DWORD earlyStopbitOffset; /**< Early stop bit offset for UART timestamps in ns */
};

}
}
