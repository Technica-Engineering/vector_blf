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

struct GeneralSerialEvent
{
    /**
     * @brief length of variable data in bytes
     */
    DWORD dataLength;

    /**
     * @brief length of variable timestamps in bytes
     */
    DWORD timeStampsLength;

    /**
     * @brief variable data
     */
    BYTE * data;

    /**
     * @brief variable timestamps (optional)
     */
    LONGLONG * timeStamps;
};

struct SingleByteSerialEvent
{
    BYTE byte;
};

struct CompactSerialEvent
{
    BYTE compactLength;
    BYTE compactData[15];
};

/**
 * @brief SERIAL_EVENT
 */
class VECTOR_BLF_EXPORT SerialEvent : public ObjectHeader
{
public:
    SerialEvent();

    virtual char * parse(char * buffer);

    enumclass Flags : DWORD {
        KLineEvent = 0x000000001,

        /** only valid if BL_SERIAL_TYPE_KLINE_EVENT is set */
        DiagRequest = 0x000000002,

        /** optimization for logging single bytes */
        SingleByte = 0x000000004,

        /** optimization for logging a few bytes without additional timestamps */
        CompactByte = 0x000000008
    };

    DWORD flags;

    /**
     * @brief channel of event
     */
    DWORD port;

    /**
     * @brief baudrate at which this event was transmitted (optional)
     */
    DWORD baudrate;

    DWORD reserved;

    union
    {
        GeneralSerialEvent general;
        SingleByteSerialEvent singleByte;
        CompactSerialEvent compact;
    };
};

}
}
