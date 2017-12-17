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

#include <Vector/BLF/platform.h>

#include <array>
#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief SERIAL_EVENT
 *
 * serial event
 */
class VECTOR_BLF_EXPORT SerialEvent final : public ObjectHeader
{
public:
    SerialEvent();
    virtual ~SerialEvent();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /** enumeration for flags */
    enum Flags : DWORD
    {
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
    DWORD reservedSerialEvent;

    /** general serial event */
    struct GeneralSerialEvent {
        GeneralSerialEvent();
        virtual ~GeneralSerialEvent();

        /**
         * Calculates the objectSize
         *
         * @return object size
         */
        virtual DWORD calculateObjectSize() const;

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

        /** reserved */
        ULONGLONG reservedGeneralSerialEvent;

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
    struct SingleByteSerialEvent {
        SingleByteSerialEvent();
        virtual ~SingleByteSerialEvent();

        /**
         * Calculates the objectSize
         *
         * @return object size
         */
        virtual DWORD calculateObjectSize() const;

        /** single byte */
        BYTE byte;
    };

    /** single byte serial event */
    SingleByteSerialEvent singleByte;

    /** compact serial event */
    struct CompactSerialEvent {
        CompactSerialEvent();
        virtual ~CompactSerialEvent();

        /**
         * Calculates the objectSize
         *
         * @return object size
         */
        virtual DWORD calculateObjectSize() const;

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
