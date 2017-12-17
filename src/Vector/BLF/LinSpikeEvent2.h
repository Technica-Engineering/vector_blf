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

#include <Vector/BLF/platform.h>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/LinBusEvent.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_SPIKE_EVENT2
 *
 * This event occurs when a short (normally less than 1 bit time) dominant signal has
 * been detected on a LIN channel.
 */
class VECTOR_BLF_EXPORT LinSpikeEvent2 final : public ObjectHeader, public LinBusEvent
{
public:
    LinSpikeEvent2();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * @brief the spike's width in microseconds
     *
     * Spike length in microseconds
     */
    ULONG width;

    /**
     * Flag indicating whether this event is a simulated
     * one:
     *   - 0: real event
     *   - 1: simulated event
     */
    BYTE internal;

    /** reserved */
    BYTE reservedLinSpikeEvent1;

    /** reserved */
    WORD reservedLinSpikeEvent2;
};

}
}
