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
    DWORD dataLength; /**< length of variable data in bytes */
    DWORD timeStampsLength; /**< length of variable timestamps in bytes */
    BYTE * data; /**< variable data */
    LONGLONG * timeStamps; /**< variable timestamps (optional) */
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
class SerialEvent : public ObjectHeader
{
public:
    SerialEvent();
    enumclass Flags : DWORD {
        KLineEvent = 0x000000001,
        DiagRequest = 0x000000002, /**< only valid if BL_SERIAL_TYPE_KLINE_EVENT is set */
        SingleByte = 0x000000004, /**< optimization for logging single bytes */
        CompactByte = 0x000000008 /**< optimization for logging a few bytes without additional timestamps */
    };
    DWORD flags;
    DWORD port; /**< channel of event */
    DWORD baudrate; /**< baudrate at which this event was transmitted (optional) */
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
