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
#include "LinMessageDescriptor.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * Common header of LIN bus events containing response data bytes
 */
class VECTOR_BLF_EXPORT LinDatabyteTimestampEvent : public LinMessageDescriptor
{
public:
    LinDatabyteTimestampEvent();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief Databyte timestamps, where d[0] = EndOfHeader, d[1]=EndOfDataByte1, ..., d[8]=EndOfDataByte8
     *
     * Data byte timestamps [in nanoseconds]
     *
     * Index 0 corresponds to last header byte
     *
     * Indexes 1-9 correspond to response data
     * bytes D1-D8
     */
    std::array<ULONGLONG, 9> databyteTimestamps;
};

}
}
