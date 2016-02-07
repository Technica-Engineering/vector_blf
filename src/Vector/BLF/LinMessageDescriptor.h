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
#include "LinSynchFieldEvent.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * Common header of LIN bus events containing LIN header data
 */
class VECTOR_BLF_EXPORT LinMessageDescriptor : public LinSynchFieldEvent
{
public:
    LinMessageDescriptor();

    virtual void read(AbstractFile & is);
    virtual void write(AbstractFile & os);
    virtual size_t calculateObjectSize();

    /**
     * @brief LIN Sub-Identifier - Supplier ID
     *
     * Supplier identifier of the frame’s transmitter
     * as it is specified in LDF. LIN protocol 2.0
     * and higher
     */
    WORD supplierId;

    /**
     * @brief LIN Sub-Identifier - Message ID (16 bits)
     *
     * LIN protocol 2.0: Message identifier (16-bit)
     * of the frame as it is specified in LDF in the
     * list of transmitter’s configurable frames.
     *
     * LIN protocol 2.1: Position index of the frame
     * as it is specified in LDF in the list of
     * transmitter’s configurable frames.
     */
    WORD messageId;

    /**
     * @brief LIN Sub-Identifier - NAD
     *
     * Configured Node Address of the frame’s
     * transmitter as it is specified in LDF. LIN
     * protocol 2.0 and higher
     */
    BYTE nad;

    /**
     * @brief LIN ID
     *
     * Frame identifier (6-bit)
     */
    BYTE id;

    /**
     * @brief LIN DLC
     *
     * Frame length [in bytes]
     */
    BYTE dlc;

    /**
     * @brief LIN checksum model
     *
     * Expected checksum model of checksum
     * value. Only valid if objectVersion >= 1.
     */
    BYTE checksumModel;
};

}
}
