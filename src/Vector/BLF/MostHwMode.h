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
#include "ObjectHeader2.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_HWMODE
 *
 * This event is fired when one or more HW state changes. HW states are the AllBypass
 * bit (e.g. ABY of OS8104), the Master/Slave selection (e.g. MTR of OS8104), the Control spy and
 * the Asynchronous spy. The event transports all states even if only a single state has changed.
 * hwModeMask denotes which state differs regarding to the previous HW mode event.
 */
class VECTOR_BLF_EXPORT MostHwMode : public ObjectHeader2
{
public:
    MostHwMode();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Application channel
     */
    WORD channel;

    /** reserved */
    WORD reserved;

    /**
     * @brief bypass/master/slave/spy
     *
     * - Bit 0x01: Bypass: 0: open; 1: active
     * - Bit 0x02: Timing mode: 0: slave; 1: master
     * - Bit 0x04: Master mode: 0: static master; 1: nonstatic
     *   master
     * - Bit 0x08: 0: Ethernet Spy active: 1: blocks
     *   "Ethernet Spy over MOST" channel
     * - Bit 0x10: Control channel spy: 1: active
     * - Bit 0x20: Async. channel spy: 1: active
     * - Bit 0x40: 1: no "Ethernet over MOST" events
     *   (MOST150)
     * - Bit 0x80: 1: no events from async. channel
     */
    WORD hwMode;

    /**
     * @brief marks the altered bits
     *
     * Bitmask of changed bits
     */
    WORD hwModeMask;
};

}
}
