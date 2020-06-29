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

#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief GPS_EVENT
 *
 * GPS event.
 */
struct VECTOR_BLF_EXPORT GpsEvent final : ObjectHeader {
    GpsEvent();

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /**
     * Not used, must be 0.
     */
    DWORD flags {};

    /**
     * @brief channel of event
     *
     * GPS channel the GPS event was sent.
     */
    WORD channel {};

    /**
     * Reserved, must be 0.
     */
    WORD reservedGpsEvent {};

    /**
     * Latitude, possible values reach from -180 to 180.
     *
     * Negative values are western hemisphere, positive
     * values are eastern hemisphere.
     */
    DOUBLE latitude {};

    /**
     * Longitude, possible values reach from -90 to 90.
     * Negative values are Southern hemisphere,
     * positive values are northern hemisphere.
     */
    DOUBLE longitude {};

    /**
     * Altitude in meters, measured above sea line.
     */
    DOUBLE altitude {};

    /**
     * Current vehicle speed in km/h.
     */
    DOUBLE speed {};

    /**
     * Current driving course, possible values reach
     * from -180 to 180. A value of 0 means driving
     * north, 90 means driving east, -90 means driving
     * west, -180 and 180 mean driving south.
     */
    DOUBLE course {};
};

}
}
