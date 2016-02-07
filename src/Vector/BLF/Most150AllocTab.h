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

#include <vector>

#include "AbstractFile.h"
#include "ObjectHeader2.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_150_ALLOCTAB
 *
 * Transports current state and changes of the MOST50/150 Allocation Table.
 */
class VECTOR_BLF_EXPORT Most150AllocTab : public ObjectHeader2 /* applied for MOST50 and MOST150 */
{
public:
    Most150AllocTab();

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
     * @brief determines the data layout
     *
     * Determines the data layout (see below)
     */
    WORD eventModeFlags;

    /**
     * @brief number of free bytes after the operation
     *
     * Number of free bytes after the operation
     *   - Max. 116 with SBC=29 for MOST50
     *   - Max. 372 with SBC=93 for MOST150
     */
    WORD freeBytes;

    /**
     * @brief number of bytes in tableData
     *
     * Length of variable data in bytes. The value must
     * be a multiple of 4.
     */
    WORD length;

    /**
     * Allocation Table data
     *
     * The data layout tableData depends on bit 0 of eventModeFlags.
     *
     * If bit 0 of eventModeFlags is clear tableData contains length/4 records with the following
     * fields. (Other data layouts are not specified yet.)
     * - Bit 0..12 (LabelIdent): Synchronous Connection Label
     * - Bit 12..15 (LabelStatus):
     *   - 0: label unchanged
     *   - 4: label has been added (allocated)
     *   - 8: label has been removed (de-allocated)
     *     List removed labels at the end of the table!
     *     Listing of removed labels is optional.
     * - Bit 16..31 (LabelWidth): Width of the label in bytes
     *
     * Data layout:
     * if((eventModeFlags & 0x0001) == 0)
     *   layout A: SLLLWWWWSLLLWWWWSLLLWWWW...
     * if((eventModeFlags & 0x0001) == 0x0001)
     *   layout B: SLLLWWWW< channels >SLLLWWWW< channels >SLLLWWWW< channels >...
     * - S: status flags
     *   - 0x4: 1: new label (alloc)
     *   - 0x8: 1: this label has been removed (dealloc)
     * - LLL:  label number
     * - WWWW: label width
     * - < channels >: list of 16-bit channel numbers (size = label width)
     */
    std::vector<WORD> tableData;
};

}
}
