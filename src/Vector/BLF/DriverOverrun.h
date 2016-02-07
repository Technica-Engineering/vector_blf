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

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief OVERRUN_ERROR
 */
class VECTOR_BLF_EXPORT DriverOverrun : public ObjectHeader
{
public:
    DriverOverrun();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /** enumeration for busType */
    enum class BusType : DWORD {
        /** CAN */
        Can = 1,

        /** LIN */
        Lin = 5,

        /** MOST */
        Most = 6,

        /** FlexRay */
        FlexRay = 7,

        /** J1708 */
        J1708 = 9,

        /** Ethernet */
        Ethernet = 10,

        /** WLAN */
        Wlan = 13,

        /** AFDX */
        Afdx = 14
    };

    /**
     * @brief bus type
     */
    BusType busType;

    /**
     * @brief channel where overrun occured
     */
    WORD channel;

    /** reserved */
    WORD reserved;
};

}
}
