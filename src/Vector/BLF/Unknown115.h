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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief UNKNOWN_115
 *
 * This always comes at the end of a file.
 */
struct VECTOR_BLF_EXPORT Unknown115 final : ObjectHeader {
    Unknown115();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /** reserved */
    DWORD reservedUnknownObject1 {}; // @todo what is this? 0x001E00C4, ...

    /** reserved */
    DWORD reservedUnknownObject2 {}; // @todo what is this? 0x00000000, ...

    /** reserved */
    DWORD reservedUnknownObject3 {}; // @todo what is this? 0x000000D6, ...

    /** reserved */
    DWORD reservedUnknownObject4 {}; // @todo what is this? 0x0008F30C, ...

    /** reserved */
    DWORD reservedUnknownObject5 {}; // @todo what is this? 0x00180008, ...

    /** reserved */
    DWORD reservedUnknownObject6 {}; // @todo what is this? 0x000003E8, ...
};

}
}
