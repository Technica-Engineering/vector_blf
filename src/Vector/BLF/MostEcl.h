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
#include "ObjectHeader2.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_ECL
 *
 * State change of the MOST Electrical Control Line.
 */
class VECTOR_BLF_EXPORT MostEcl : public ObjectHeader2
{
public:
    MostEcl();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Application channel
     */
    WORD channel;

    /**
     * - 0 – discrete
     * - 1 – sequence
     */
    WORD mode;

    /**
     * @brief Electrical Control Line level
     *
     * mMode = 0:
     *   - 0 – line low
     *   - 1 – line high
     * mMode = 1:
     *   - 0 – sequence stopped
     *   - 1 – sequence started
     */
    WORD eclState;

    /** reserved */
    WORD reserved;
};

}
}
