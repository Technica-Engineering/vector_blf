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
#include <Vector/BLF/ObjectHeaderBase.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief UNKNOWN_115
 *
 * This always comes at the end of a file.
 */
class VECTOR_BLF_EXPORT Unknown115 final : public ObjectHeaderBase
{
public:
    Unknown115();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual WORD calculateHeaderSize() const override;
    virtual DWORD calculateObjectSize() const override;

    /** @copydoc ObjectHeader::objectFlags */
    DWORD objectFlags;

    /** @copydoc ObjectHeader::clientIndex */
    WORD clientIndex;

    /** @copydoc ObjectHeader::objectVersion */
    WORD objectVersion;

    /** @copydoc ObjectHeader::objectTimeStamp */
    ULONGLONG objectTimeStamp;

    /** reserved */
    DWORD reservedUnknownObject1;

    /** reserved */
    DWORD reservedUnknownObject2;

    /** reserved */
    DWORD reservedUnknownObject3;

    /** reserved */
    WORD reservedUnknownObject4;

    /** reserved */
    WORD reservedUnknownObject5;

    /** reserved */
    WORD reservedUnknownObject6;

    /** reserved */
    WORD reservedUnknownObject7;

    /** reserved */
    WORD reservedUnknownObject8;

    /** reserved */
    WORD reservedUnknownObject9;
};

}
}
