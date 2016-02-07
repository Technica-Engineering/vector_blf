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
#include "LinBusEvent.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_WAKEUP2
 *
 * LIN Wakeup-Frame received or transmitted on a LIN channel.
 */
class VECTOR_BLF_EXPORT LinWakeupEvent2 : public ObjectHeader, public LinBusEvent
{
public:
    LinWakeupEvent2();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * Wake-up length validity indicator:
     *   - 0: Wake-up length is OK
     *   - 1: Wake-up is too short
     *   - 2: Wake-up is too long
     */
    BYTE lengthInfo;

    /**
     * Byte value used by wakeup frame.
     */
    BYTE signal;

    /**
     * Flag indicating whether the wakeup frame has
     * been transmitted by an external device (selector
     * set) or by the LIN hardware itself (selector not
     * set).
     */
    BYTE external;

    /** reserved */
    std::array<BYTE, 5> reserved;
};

}
}
