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

#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief FUNCTION_BUS
 */
struct VECTOR_BLF_EXPORT FunctionBus final : ObjectHeader {
    FunctionBus();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    DWORD calculateObjectSize() const override;

    /** enumeration for functionBusObjectType */
    enum FunctionBusObjectType : DWORD {
        Undefined = 0,
        Signal = 1,
        ServiceFunction = 2,
        State = 3
    };

    /** type of system variable */
    DWORD functionBusObjectType {};

    DWORD veType {};

    /** length of variable name in bytes */
    DWORD nameLength {};

    /** length of variable data in bytes */
    DWORD dataLength {};

    /** path name in the port server */
    std::string name {};

    /** variable data */
    std::vector<BYTE> data {};
};

}
}
