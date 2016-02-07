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
#include <string>
#include <vector>

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief SYS_VARIABLE
 *
 * System variable that can be used with CANoe.
 */
class VECTOR_BLF_EXPORT SystemVariable : public ObjectHeader
{
public:
    SystemVariable();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /** enumeration for type */
    enum class Type : DWORD {
        /** DOUBLE */
        Double = 1,

        /** LONG */
        Long = 2,

        /** STRING */
        String = 3,

        /** Array of DOUBLE */
        DoubleArray = 4,

        /** Array of LONG */
        LongArray = 5,

        /** LONGLONG */
        LongLong = 6,

        /** Array of BYTE */
        ByteArray = 7
    };

    /**
     * @brief type of system variable
     */
    Type type;

    /**
     * Reserved, must be 0.
     */
    std::array<DWORD, 3> reserved1;

    /**
     * @brief length of variable name in bytes
     *
     * Length of the name of the system variable
     * (without terminating 0)
     */
    DWORD nameLength;

    /**
     * @brief length of variable data in bytes
     *
     * Length of the data of the environment variable in
     * bytes.
     */
    DWORD dataLength;

    /** reserved */
    std::array<BYTE, 8> reserved2;

    /**
     * @brief variable name in MBCS
     *
     * Name of the system variable.
     */
    std::string name;

    /**
     * @brief variable data
     *
     * Data value of the system variable.
     */
    std::vector<uint8_t> data;
};

}
}
