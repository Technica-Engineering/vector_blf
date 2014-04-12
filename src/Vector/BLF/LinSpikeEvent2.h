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
#include "LinBusEvent.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_SPIKE_EVENT2
 */
class LinSpikeEvent2 : public ObjectHeader, public LinBusEvent
{
public:
    LinSpikeEvent2();

    ULONG width; /**< the spike's width in microseconds */
    BYTE internal;
    BYTE reserved[3]; /**< 4-byte alignment */
};

}
}
