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

#include <string>

#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief GLOBAL_MARKER
 *
 * Global Marker assigned to another event or to a time stamp.
 */
struct VECTOR_BLF_EXPORT GlobalMarker final : ObjectHeader {
    GlobalMarker();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief commented event type
     *
     * Type of the commented events
     */
    uint32_t commentedEventType {};

    /**
     * Foreground color of the marker group.
     */
    uint32_t foregroundColor {};

    /**
     * Background color of the marker group.
     */
    uint32_t backgroundColor {};

    /**
     * Defines whether a marker can be relocated
     */
    uint8_t isRelocatable {};

    /** reserved */
    uint8_t reservedGlobalMarker1 {};

    /** reserved */
    uint16_t reservedGlobalMarker2 {};

    /**
     * @brief group name length in bytes
     *
     * Length of groupName without ending 0.
     */
    uint32_t groupNameLength {};

    /**
     * @brief marker name length in bytes
     *
     * Length of markerName without ending 0.
     */
    uint32_t markerNameLength {};

    /**
     * @brief description length in bytes
     *
     * Length of description without ending 0.
     */
    uint32_t descriptionLength {};

    /** reserved */
    uint32_t reservedGlobalMarker3 {};

    /** reserved */
    uint64_t reservedGlobalMarker4 {};

    /**
     * @brief group name
     *
     * Group name.
     */
    std::string groupName {};

    /**
     * @brief marker name
     *
     * Marker.
     */
    std::string markerName {};

    /**
     * @brief description
     *
     * Description text.
     */
    std::string description {};
};

}
}
