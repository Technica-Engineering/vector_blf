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
 * @brief J1708_MESSAGE, J1708_VIRTUAL_MSG
 *
 * J1708 message object
 */
class VECTOR_BLF_EXPORT J1708Message : public ObjectHeader
{
public:
    J1708Message();

    virtual char * read(char * buffer);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     */
    WORD channel;

    /**
     * @brief direction
     */
    BYTE dir;

    /** reserved */
    BYTE reserved1;

    /**
     * @brief error code
     */
    WORD error;

    /**
     * @brief data size
     */
    BYTE size;

    /**
     * @brief data
     */
    BYTE data[255];

    /** reserved */
    BYTE reserved2[2];
};

}
}
