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

#include <string>
#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief ENV_INTEGER, ENV_DOUBLE, ENV_STRING, ENV_DATA
 *
 * Environment variable that can be used with CANoe.
 */
class VECTOR_BLF_EXPORT EnvironmentVariable final : public ObjectHeader
{
public:
    EnvironmentVariable();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * @brief length of variable name in bytes
     *
     * Length of the name of the environment variable
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
    ULONGLONG reservedEnvironmentVariable;

    /**
     * @brief variable name in MBCS
     *
     * Name of the environment variable.
     */
    std::string name;

    /**
     * @brief variable data
     *
     * Data value of the environment variable.
     */
    std::vector<uint8_t> data;
};

}
}
