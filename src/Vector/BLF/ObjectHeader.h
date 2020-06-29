/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/ObjectHeaderBase.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief Object header
 *
 * Object header. Version 1.
 */
struct VECTOR_BLF_EXPORT ObjectHeader : ObjectHeaderBase {
    /**
     * Constructor
     *
     * @param[in] objectType object type
     * @param[in] objectVersion object version
     */
    ObjectHeader(const ObjectType objectType, const WORD objectVersion = 0);

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    WORD calculateHeaderSize() const override;
    DWORD calculateObjectSize() const override;

    /** enumeration for objectFlags */
    enum ObjectFlags : DWORD {
        /**
         * @brief 10 micro second timestamp
         *
         * Object time stamp is saved as multiple of ten
         * microseconds.
         * (BL_OBJ_FLAG_TIME_TEN_MICS)
         */
        TimeTenMics = 0x00000001,

        /**
         * @brief 1 nano second timestamp
         *
         * Object time stamp is saved in nanoseconds.
         * (BL_OBJ_FLAG_TIME_ONE_NANS)
         */
        TimeOneNans = 0x00000002
    };

    /**
     * @brief object flags
     *
     * Unit of object timestamp.
     */
    DWORD objectFlags {ObjectFlags::TimeOneNans};

    /**
     * @brief client index of send node
     */
    WORD clientIndex {};

    /**
     * @brief object specific version
     *
     * Object specific version, has to be set to 0 unless
     * stated otherwise in the description of a specific
     * event.
     *
     * @note can be set in event class constructor
     */
    WORD objectVersion {0};

    /**
     * @brief object timestamp
     *
     * Time stamp of this object in the unit specified in
     * objectFlags.
     */
    ULONGLONG objectTimeStamp {};
};

}
}
