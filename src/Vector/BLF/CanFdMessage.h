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
 */
class VECTOR_BLF_EXPORT CanFdMessage : public ObjectHeader
{
public:
    CanFdMessage();

    virtual char * parse(char * buffer);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     */
    WORD channel;

    /**
     * CAN Message Flags
     *
     * CAN dir, rtr, wu & nerr encoded into flags
     *
     * @todo does this make sense here?
     */
    enumclass CanMessageFlags : BYTE {
        TX = (1<<0),
        NERR = (1<<5),
        WU = (1<<6),
        RTR = (1<<7)
    };

    /**
     * @brief CAN dir & rtr
     */
    BYTE flags;

    /**
     * @brief CAN dlc
     */
    BYTE dlc;

    /**
     * @brief CAN ID
     */
    DWORD id;

    /**
     * @brief message length in ns - without 3 inter frame space bits and by Rx-message also without 1 End-Of-Frame bit
     */
    DWORD frameLength;

    /**
     * @brief bit count of arbitration phase
     */
    BYTE arbBitCount;

    /**
     * @todo does this make sense here?
     */
    enumclass CanFdMessageFlags : BYTE {
        EDL = (1<<0),
        BRS = (1<<1),
        ESI = (1<<2)
    };

    /**
     * @brief CAN FD flags
     */
    BYTE canFdFlags;

    /**
     * @brief Valid payload length of data
     */
    BYTE validDataBytes;

    /** reserved */
    BYTE reserved[5];

    /**
     * @brief CAN FD data
     */
    BYTE data[64];
};

}
}
