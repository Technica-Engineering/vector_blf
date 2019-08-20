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

#include <Vector/BLF/platform.h>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief LIN_CHECKSUM_INFO
 *
 * This info event occurs when the LIN hardware successfully detected the checksum
 * model of an unknown frame. This checksum model is set as the expected one for this frame in the
 * future.
 */
class VECTOR_BLF_EXPORT LinChecksumInfo final : public ObjectHeader
{
public:
    LinChecksumInfo();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * Channel number where the event notified
     */
    WORD channel {};

    /**
     * @brief LIN ID
     *
     * Frame identifier
     */
    BYTE id {};

    /**
     * @brief LIN checksum model
     *
     * Used checksum model. Following values are
     * possible:
     *   - 0: Classic
     *   - 1: Enhanced
     *   - 0xFF: Unknown
     */
    BYTE checksumModel {};

    /** reserved */
    DWORD reservedLinChecksumInfo {};
};

}
}
