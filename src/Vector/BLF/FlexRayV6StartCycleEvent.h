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
 * @brief FLEXRAY_CYCLE
 *
 * Start of cycle event transmitted by the hardware interface on a FlexRay channel.
 */
class VECTOR_BLF_EXPORT FlexRayV6StartCycleEvent : public ObjectHeader
{
public:
    FlexRayV6StartCycleEvent();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Application channel
     */
    WORD channel;

    /**
     * @brief dir flag (tx, rx)
     *
     * Direction Flags
     *   - 0 = Rx
     *   - 1 = Tx
     *   - 2 = Tx Request
     *   - 3 and 4 are for internal use only.
     */
    BYTE dir;

    /**
     * @brief additional time field in simulation
     *
     * Additional time field in simulation
     */
    BYTE lowTime;

    /**
     * @brief timestamp generated from xModule
     *
     * Timestamp generated from xModule
     */
    DWORD fpgaTick;

    /**
     * @brief overflow counter of the timestamp
     *
     * Overflow counter of the timestamp
     */
    DWORD fpgaTickOverflow;

    /**
     * @brief clientindex of send node
     *
     * Client index of send node. Must be set to 0 if file
     * is written from other applications
     */
    DWORD clientIndex;

    /**
     * @brief relative clustertime, from 0 to cyclelength
     *
     * Relative cluster time, from 0 to cycle length
     */
    DWORD clusterTime;

    /**
     * @brief array of databytes
     *
     * Array of data bytes
     */
    std::array<BYTE, 2> dataBytes;

    /** reserved */
    std::array<BYTE, 2> reserved;
};

}
}
