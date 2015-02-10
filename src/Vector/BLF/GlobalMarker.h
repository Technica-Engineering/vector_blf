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

#include "VectorTypes.h"
#include "ObjectHeader.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief GLOBAL_MARKER
 *
 * Global Marker assigned to another event or to a time stamp.
 */
class VECTOR_BLF_EXPORT GlobalMarker : public ObjectHeader
{
public:
    GlobalMarker();
    virtual ~GlobalMarker();

    virtual char * parse(char * buffer);
    virtual size_t calculateObjectSize();

    /**
     * @brief commented event type
     *
     * Type of the commented events
     */
    DWORD commentedEventType;

    /**
     * Foreground color of the marker group.
     */
    COLORREF foregroundColor;

    /**
     * Background color of the marker group.
     */
    COLORREF backgroundColor;

#if 0
    /**
     * Defines whether a marker can be relocated
     *
     * @todo don't know how this works. reserved is read instead.
     */
    BYTE isRelocatable;
#else
    /**
     * reserved
     *
     * @todo what is this?
     */
    DWORD reserved1;
#endif

    /**
     * @brief group name length in bytes
     *
     * Length of groupName without ending 0.
     */
    DWORD groupNameLength;

    /**
     * @brief marker name length in bytes
     *
     * Length of markerName without ending 0.
     */
    DWORD markerNameLength;

    /**
     * @brief description length in bytes
     *
     * Length of description without ending 0.
     */
    DWORD descriptionLength;

    /**
     * reserved
     *
     * @todo what is this?
     */
    DWORD reserved2[3];

    /**
     * @brief group name in MBCS
     *
     * Group name.
     */
    char * groupName;

    /**
     * @brief marker name in MBCS
     *
     * Marker.
     */
    char * markerName;

    /**
     * @brief description in MBCS
     *
     * Description text.
     */
    char * description;
};

}
}
