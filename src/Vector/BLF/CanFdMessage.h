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

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief CAN_FD_MESSAGE
 *
 * CAN Message Flags
 *
 * CAN dir, rtr, wu & nerr encoded into flags
 */
enumclass CanMessageFlags : BYTE {
    TX = (1<<0),
    NERR = (1<<5),
    WU = (1<<6),
    RTR = (1<<7)
};

enumclass CanFdMessageFlags : BYTE {
    EDL = (1<<0),
    BRS = (1<<1),
    ESI = (1<<2)
};

/**
 * @brief CAN_FD_MESSAGE
 */
class CanFdMessage : public ObjectHeader
{
public:
    CanFdMessage();

    WORD channel; /**< application channel */
    BYTE flags; /**< CAN dir & rtr */
    BYTE dlc; /**< CAN dlc */
    DWORD id; /**< CAN ID */
    DWORD frameLength; /**< message length in ns - without 3 inter frame space bits and by Rx-message also without 1 End-Of-Frame bit */
    BYTE arbBitCount; /**< bit count of arbitration phase */
    BYTE canFdFlags; /**< CAN FD flags */
    BYTE validDataBytes; /**< Valid payload length of data */
    BYTE reserved1; /**< reserved */
    DWORD reserved2; /**< reserved */
    BYTE data[64]; /**< CAN FD data */
};

}
}
