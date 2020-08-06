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
#include <Vector/BLF/Types.h>

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

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /**
     * @brief commented event type
     *
     * Type of the commented events
     */
    DWORD commentedEventType {};

    /**
     * Foreground color of the marker group.
     */
    COLORREF foregroundColor {};

    /**
     * Background color of the marker group.
     */
    COLORREF backgroundColor {};

    /**
     * Defines whether a marker can be relocated
     */
    BYTE isRelocatable {};

    /** reserved */
    BYTE reservedGlobalMarker1 {};

    /** reserved */
    WORD reservedGlobalMarker2 {};

    /**
     * @brief group name length in bytes
     *
     * Length of groupName without ending 0.
     */
    DWORD groupNameLength {};

    /**
     * @brief marker name length in bytes
     *
     * Length of markerName without ending 0.
     */
    DWORD markerNameLength {};

    /**
     * @brief description length in bytes
     *
     * Length of description without ending 0.
     */
    DWORD descriptionLength {};

    /** reserved */
    DWORD reservedGlobalMarker3 {};

    /** reserved */
    ULONGLONG reservedGlobalMarker4 {};

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
