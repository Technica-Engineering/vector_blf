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
#include "ObjectHeader2.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_STATISTICEX
 *
 * Event transports some bus statistic information that was previously (until CANoe/
 * CANalyzerVersion 6.1) carried by the main bus statistic event but was not logged. Usually the
 * event is not visible in a Trace window.
 */
class VECTOR_BLF_EXPORT MostStatisticEx : public ObjectHeader2
{
public:
    MostStatisticEx();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief application channel
     *
     * Application channel
     */
    WORD channel;

    /** reserved */
    WORD reserved1;

    /**
     * Number of coding errors
     */
    DWORD codingErrors;

    /**
     * MOST frame counter
     */
    DWORD frameCounter;

    /** reserved */
    std::array<BYTE, 4> reserved2;
};

}
}
