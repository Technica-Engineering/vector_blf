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
#include "ObjectHeader2.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_REG
 *
 * This event transports a register read or write result (e.g. reading the routing engine of
 * the OS8104). Unlike the special register event (MostGenReg) this event does not occur
 * spontaneous.
 */
class VECTOR_BLF_EXPORT MostReg : public ObjectHeader2
{
public:
    MostReg();

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
     * @brief read/write request/result
     *
     * Operation type of a register event.
     *   - Unspecified = 0: unspecified (or HW does not support sub types)
     *   - Notify = 1: notification on register change (spontaneous)
     *   - ReadRequest = 2: request of a register read operation
     *   - WriteRequest = 3: request of a register write operation
     *   - ReadResult = 4: result of a register read operation
     *   - WriteResult = 5: result of a register write operation
     *   - ReadFailed = 6: register read operation failed
     *   - WriteFailed = 7: register write operation failed
     */
    BYTE subType;

    /** reserved */
    BYTE reserved;

    /**
     * @brief operation handle
     *
     * Operation handle (obsolete; write 0)
     */
    DWORD handle;

    /**
     * @brief start address
     *
     * Register address offset
     */
    DWORD offset;

    /**
     * @brief chip id
     *
     * ID of chip
     *   - 1 – OS8104
     */
    WORD chip;

    /**
     * @brief number of bytes
     *
     * Number of valid bytes in regData
     */
    WORD regDataLen;

    /**
     * @brief data bytes
     *
     * Register data
     */
    std::array<BYTE, 16> regData;
};

}
}
