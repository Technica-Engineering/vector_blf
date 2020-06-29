/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief A429_STATUS
 *
 * A429 status object
 */
struct VECTOR_BLF_EXPORT A429Status final : ObjectHeader {
    A429Status();

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /** application channel */
    WORD channel {};

    /** direction flag: 0=Rx, 1=Tx */
    BYTE dir {};

    /** reserved */
    BYTE reservedA429Status1 {};

    /** parity */
    WORD parity {};

    /** reserved */
    WORD reservedA429Status2 {};

    /** minimum gap */
    ULONG minGap {};

    /** Tx bit rate */
    ULONG bitrate {};

    /** Rx min bit rate */
    ULONG minBitrate {};

    /** Rx max bit rate */
    ULONG maxBitrate {};
};

}
}
