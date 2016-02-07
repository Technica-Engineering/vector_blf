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
 * @brief FR_STARTCYCLE
 *
 * FlexRay StartCycle event transmitted by the FlexRay hardware.
 */
class VECTOR_BLF_EXPORT FlexRayVFrStartCycle : public ObjectHeader
{
public:
    FlexRayVFrStartCycle();

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
     * @brief version of data struct
     *
     * Object version, for internal use
     */
    WORD version;

    /**
     * @brief channel mask
     *
     * Channel Mask
     *   - 0 = Reserved or invalid
     *   - 1 = FlexRay Channel A
     *   - 2 = FlexRay Channel B
     *   - 3 = FlexRay Channels A and B
     */
    WORD channelMask;

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
     * @brief current cycle
     *
     * Cycle number
     */
    BYTE cycle;

    /**
     * @brief clientindex of send node
     *
     * Client index of send node
     */
    DWORD clientIndex;

    /**
     * @brief number of cluster
     *
     * Number of cluster: channel number - 1
     */
    DWORD clusterNo;

    /**
     * @brief size of NM Vector
     *
     * Length of NM-Vector in bytes
     */
    WORD nmSize;

    /**
     * @brief array of databytes (NM vector max. length)
     *
     * Array of databytes (NM vector max. length)
     */
    std::array<BYTE, 12> dataBytes;

    /** reserved */
    std::array<BYTE, 2> reserved1;

    /**
     * @brief type of cc
     *
     * Type of communication controller
     *   - 0 = Architecture independent
     *   - 1 = Invalid CC type (for internal use only)
     *   - 2 = Cyclone I
     *   - 3 = BUSDOCTOR
     *   - 4 = Cyclone II
     *   - 5 = Vector VN interface
     *   - 6 = VN-Sync-Pulse (only in Status Event, for debugging purposes only)
     */
    DWORD tag;

    /**
     * @brief register flags
     *
     * Driver flags for internal usage
     *
     * Cyclone I:
     *   - 0: Rate correction of CC, read from RCVR register
     *   - 1: Offset correction of CC, read from OCVR register
     *
     * Cyclone II:
     *   - 0: Sync correction of CC, read from RCV register
     *   - 1: Offset correction of CC, read from OCV register
     *   - 2: Cycles with no correction, read from CCEV register
     *   - 3: Cycles with correction in passive mode, read from CCEV register
     *   - 4: Sync Frame status, read from SFS register
     *
     * VN-Interface:
     *   - 0: Sync correction of CC, read from RCV register
     *   - 1: Offset correction of CC, read from OCV register
     *   - 2: Cycles with no correction, read from CCEV register
     *   - 3: Cycles with correction in passive mode, read from CCEV register
     *   - 4: Sync Frame status, read from SFS register
     */
    std::array<DWORD, 5> data;

    /**
     * Reserved
     */
    std::array<BYTE, 8> reserved2;
};

}
}
