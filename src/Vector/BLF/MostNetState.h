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
 * @brief MOST_NETSTATE
 *
 * Network state derived by MOST Supervisor Layer I+II
 */
class VECTOR_BLF_EXPORT MostNetState : public ObjectHeader2
{
public:
    MostNetState();

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
     * @brief MOST NetState
     *
     * Current network state
     *   - 0 (undefined): Before the first event (shortly after
     *     measurement start) the network status is
     *     unknown.
     *   - 1 (reserved for Ring Break Diagnostics mode)
     *   - 2 (PowerOff): The network interface to the
     *     MOST ring is deactivated. The Tx FOT is not
     *     emitting any light.
     *   - 3 (NetInterfaceInit): The network interface is
     *     ready to communicate in the MOST ring.
     *   - 4 (ConfigNotOk): The network interface is in
     *     normal operating mode (stable lock).
     *   - 5 (ConfigOk): From the perspective of the
     *     Network Master the system configuration is
     *     valid.
     *   - 6 (NetOn/InitReady): NetOn/InitReady reported
     *     to application
     */
    WORD stateNew;

    /**
     * Previous network state
     */
    WORD stateOld;

    /** reserved */
    WORD reserved;
};

}
}
