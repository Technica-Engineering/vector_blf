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

#include "VectorTypes.h"
#include "ObjectHeader.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief FR_STATUS
 *
 * The content of the FlexRay status event depends on the type of hardware interface.
 * The event is generated in one of the following situations:
 * - A symbol is received
 * - The POC state or wakeup state of the CC has changed
 * - The status of the symbol window has changed
 */
class VECTOR_BLF_EXPORT FlexRayVFrStatus : public ObjectHeader
{
public:
    FlexRayVFrStatus();

    WORD channel; /**< application channel */
    WORD version; /**< object version */
    WORD channelMask; /**< channel mask */
    BYTE cycle; /**< current cycle,   byte */
    DWORD clientIndex; /**< clientindex of send node */
    DWORD clusterNo; /**< number of cluster */
    DWORD wus; /**< wakeup status */
    DWORD ccSyncState; /**< sync state of cc */
    DWORD tag; /**< type of cc */
    DWORD data[2]; /**< register flags */
    WORD reserved[16];
};

}
}
