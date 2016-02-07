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
 * @brief MOST_DATALOST
 *
 * Indicates loss of data. (Number of lost messages and start and end time stamp of data
 * loss.)
 */
class VECTOR_BLF_EXPORT MostDataLost : public ObjectHeader2
{
public:
    MostDataLost();

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
     * @brief info about data loss
     *
     * Data loss information
     *   - Bit0: 1: data loss on control channel (spy)
     *   - Bit1: 1: data loss on control channel (node)
     *   - Bit2: 1: data loss on asynchronous channel
     *     (spy)
     *   - Bit3: 1: data loss on asynchronous channel
     *     (node)
     *   - Bit4: 1: data loss on synchronous channel
     *   - Bit5: 1: data loss since driver queue full
     */
    DWORD info;

    /**
     * Number of lost messages on Control channel
     */
    DWORD lostMsgsCtrl;

    /**
     * Number of lost messages on Packet Data
     * Channel channel
     */
    DWORD lostMsgsAsync;

    /**
     * Absolute time in nano-seconds
     */
    ULONGLONG lastGoodTimeStampNs;

    /**
     * Absolute time in nano-seconds
     */
    ULONGLONG nextGoodTimeStampNs;
};

}
}
