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
#include "ObjectHeaderBase.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief Object header
 *
 * Object header. Version 1.
 */
class VECTOR_BLF_EXPORT ObjectHeader : public ObjectHeaderBase
{
public:
    ObjectHeader();

    virtual char * parse(char * buffer);

    /**
     * @brief object flags
     *
     * Unit of object timestamp.
     */
    enumclass ObjectFlags : DWORD {
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
    } objectFlags;

    /**
     * @brief reserved
     *
     * Reserved, must be 0.
     */
    WORD reserved;

    /**
     * @brief object specific version
     *
     * Object specific version, has to be set to 0 unless
     * stated otherwise in the description of a specific
     * event.
     */
    WORD objectVersion;

    /**
     * @brief object timestamp
     *
     * Time stamp of this object in the unit specified in
     * objectFlags.
     */
    ULONGLONG objectTimeStamp;
};

}
}
