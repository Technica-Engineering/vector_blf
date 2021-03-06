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

#include <array>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief CAN_DRIVER_ERROR_EXT
 *
 * Extended CAN driver error information for transceiver of a CAN channel.
 */
struct VECTOR_BLF_EXPORT CanDriverErrorExt final : ObjectHeader {
    CanDriverErrorExt();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * CAN channel the driver error information
     * belongs to.
     */
    uint16_t channel {};

    /**
     * @brief # of TX errors
     *
     * Number of transmit errors that occurred in CAN
     * controller for that channel.
     */
    uint8_t txErrors {};

    /**
     * @brief # of RX errors
     *
     * Number of receive errors that occurred in CAN
     * controller for that channel.
     */
    uint8_t rxErrors {};

    /**
     * @brief CAN driver error code
     *
     * Error code
     */
    uint32_t errorCode {};

    /**
     * @brief flags
     *
     * To be defined.
     */
    uint32_t flags {};

    /**
     * @brief state register
     *
     * To be defined.
     */
    uint8_t state {};

    /** reserved */
    uint8_t reservedCanDriverErrorExt1 {};

    /** reserved */
    uint16_t reservedCanDriverErrorExt2 {};

    /** reserved */
    std::array<uint32_t, 4> reservedCanDriverErrorExt3 {};
};

}
}
