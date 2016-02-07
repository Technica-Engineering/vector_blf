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
#include <vector>

#include "AbstractFile.h"
#include "ObjectHeader2.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_ALLOCTAB
 *
 * Transports current state of the MOST25 Allocation Table of connected hardware
 * interface.
 */
class VECTOR_BLF_EXPORT MostAllocTab : public ObjectHeader2
{
public:
    MostAllocTab();

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
     * Length of variable data (usually 60 bytes for
     * MOST25)
     */
    WORD length;

    /** reserved */
    std::array<BYTE, 4> reserved;

    /**
     * Allocation Table
     *
     * The label of a synchronous connection can be
     * distributed over several bytes in the Allocation
     * Table.
     *
     * Each byte in mTableData contains a value that
     * specifies the identification number of the label it
     * belongs to. If the device is a timing master, the
     * MSB of the byte value is used to indicate if the
     * label is in use or not, otherwise the MSB should
     * be ignored. The label number thus can be
     * determined by byte value & 0x7F. If the resulting
     * label number is 0x70, the byte is not used for any
     * label.
     */
    std::vector<uint8_t> tableData;
};

}
}
