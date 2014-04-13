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
 * @brief FR_STARTCYCLE
 *
 * FlexRay StartCycle event transmitted by the FlexRay hardware.
 */
class VECTOR_BLF_EXPORT FlexRayVFrStartCycle : public ObjectHeader
{
public:
    FlexRayVFrStartCycle();

    WORD channel; /**< application channel */
    WORD version; /**< version of data struct */
    WORD channelMask; /**< channel mask */
    BYTE dir; /**< dir flag (tx, rx) */
    BYTE cycle; /**< current cycle,   byte  */
    DWORD clientIndex; /**< clientindex of send node */
    DWORD clusterNo; /**< number of cluster */
    WORD nmSize; /**< size of NM Vector */
    BYTE dataBytes[12]; /**< array of databytes (NM vector max. length)*/
    DWORD tag; /**< type of cc */
    DWORD data[5]; /**< register flags */
    WORD reserved;
};

}
}
