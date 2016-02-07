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
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_BAUDRATE
 *
 * This info event is sent by the LIN hardware at the start of a measurement and
 * whenever the baud rate changes by more than 0.5 % during a measurement. If this info event
 * occurs, then the LIN hardware is synchronized with the baud rate of the external Master.
 */
class VECTOR_BLF_EXPORT LinBaudrateEvent : public ObjectHeader
{
public:
    LinBaudrateEvent();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Channel number where the frame sent/received.
     */
    WORD channel;

    /** reserved */
    WORD reserved;

    /**
     * Measured baud rate [in bits/sec]
     */
    LONG baudrate;
};

}
}
