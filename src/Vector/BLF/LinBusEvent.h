/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Common header of LIN bus events
 */
struct VECTOR_BLF_EXPORT LinBusEvent {
    LinBusEvent() = default;
    virtual ~LinBusEvent() noexcept = default;
    LinBusEvent(const LinBusEvent &) = default;
    LinBusEvent & operator=(const LinBusEvent &) = default;
    LinBusEvent(LinBusEvent &&) = default;
    LinBusEvent & operator=(LinBusEvent &&) = default;

    /** @copydoc ObjectHeader::read */
    virtual void read(AbstractFile & is);

    /** @copydoc ObjectHeader::write */
    virtual void write(AbstractFile & os);

    /** @copydoc ObjectHeader::calculateObjectSize */
    virtual uint32_t calculateObjectSize() const;

    /**
     * @brief Start Of Frame timestamp
     *
     * Timestamp of frame/event start
     */
    uint64_t sof {};

    /**
     * @brief Baudrate of the event in bit/sec
     *
     * Baudrate of frame/event in bit/sec
     */
    uint32_t eventBaudrate {};

    /**
     * @brief application channel
     *
     * Channel number where the frame/event notified
     */
    uint16_t channel {};

    /** reserved */
    uint16_t reservedLinBusEvent {};
};

}
}
