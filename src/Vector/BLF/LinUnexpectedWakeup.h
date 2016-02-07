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

#include <array>

#include "AbstractFile.h"
#include "LinBusEvent.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief LIN_UNEXPECTED_WAKEUP
 *
 * This event occurs if an unexpected byte received in bus idle phase of wake mode
 * could be a wakeup frame
 */
class VECTOR_BLF_EXPORT LinUnexpectedWakeup : public ObjectHeader, public LinBusEvent
{
public:
    LinUnexpectedWakeup();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief width of the unexpected wakeup in nanoseconds (valid for LIN 2.x)
     *
     * Width of the unexpected wakeup in nanoseconds.
     * Valid for LIN 2.x
     */
    ULONGLONG width;

    /**
     * @brief byte signal of the unexpected wakeup (valid for LIN 1.x)
     *
     * Byte signal of the unexpected wakeup. Valid for
     * LIN 1.x
     */
    BYTE signal;

    /** reserved */
    std::array<BYTE, 7> reserved;
};

}
}
