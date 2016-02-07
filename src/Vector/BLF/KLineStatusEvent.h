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

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief KLINE_STATUSEVENT
 */
class VECTOR_BLF_EXPORT KLineStatusEvent : public ObjectHeader
{
public:
    KLineStatusEvent();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /** enumeration for type */
    enum class Type : WORD {
        /** If set in type, direction is tester -> ECU */
        toEcu = 0x8000,

        /** Use this mask to filter out the type from type */
        mask = 0x7FFF
    };

    /**
     * @brief BusSystemFacility::VKLineStatusEventType
     */
    WORD type;

    /**
     * @brief number of *bytes* used in data
     */
    WORD dataLen;

    /**
     * @brief channel of event
     */
    DWORD port;

    /** reserved */
    DWORD reserved;

    /**
     * @brief the actual data, but only dataLen BYTES are used!
     */
    std::array<UINT64, 3> data;
};

}
}
