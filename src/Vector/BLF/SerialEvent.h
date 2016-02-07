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
#include <vector>

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief SERIAL_EVENT
 *
 * serial event
 */
class VECTOR_BLF_EXPORT SerialEvent : public ObjectHeader
{
public:
    SerialEvent();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /** enumeration for flags */
    enum class Flags : DWORD {
        /** K-Line event */
        KLineEvent = 0x00000001,

        /**
         * diagnostic request
         *
         * only valid if KLineEvent is set
         */
        DiagRequest = 0x00000002,

        /**
         * single byte
         *
         * optimization for logging single bytes
         */
        SingleByte = 0x00000004,

        /**
         * compact byte
         *
         * optimization for logging a few bytes without additional timestamps
         */
        CompactByte = 0x00000008
    };

    /** flags */
    DWORD flags;

    /**
     * @brief channel of event
     *
     * channel of event
     */
    DWORD port;

    /**
     * @brief baudrate at which this event was transmitted (optional)
     *
     * baudrate at which this event was transmitted (optional)
     */
    DWORD baudrate;

    /** reserved */
    DWORD reserved;

    /** general serial event */
    struct GeneralSerialEvent
    {
        GeneralSerialEvent();

        /**
         * @brief length of variable data in bytes
         *
         * length of variable data in bytes
         */
        DWORD dataLength;

        /**
         * @brief length of variable timestamps in bytes
         *
         * length of variable timestamps in bytes
         */
        DWORD timeStampsLength;

        /**
         * @brief variable data
         *
         * variable data
         */
        std::vector<BYTE> data;

        /**
         * @brief variable timestamps (optional)
         *
         * variable timestamps (optional)
         */
        std::vector<LONGLONG> timeStamps;
    };

    /** general serial event */
    GeneralSerialEvent general;

    /** single byte serial event */
    struct SingleByteSerialEvent
    {
        SingleByteSerialEvent();

        /** single byte */
        BYTE byte;
    };

    /** single byte serial event */
    SingleByteSerialEvent singleByte;

    /** compact serial event */
    struct CompactSerialEvent
    {
        CompactSerialEvent();

        /** compact length */
        BYTE compactLength;

        /** compact data */
        std::array<BYTE, 15> compactData;
    };

    /** compact serial event */
    CompactSerialEvent compact;
};

}
}
