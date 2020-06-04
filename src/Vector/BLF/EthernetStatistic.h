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
#include <Vector/BLF/RawFile.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief ETHERNET_STATISTIC
 *
 * Ethernet Statistics
 */
struct VECTOR_BLF_EXPORT EthernetStatistic final : ObjectHeader {
    EthernetStatistic();

    void read(RawFile & is) override;
    void write(RawFile & os) override;
    DWORD calculateObjectSize() const override;

    /** channel */
    WORD channel {};

    /** reserved */
    WORD reservedEthernetStatistic1 {};

    /** reserved */
    DWORD reservedEthernetStatistic2 {};

    /** receive ok */
    UINT64 rcvOk_HW {};

    /** transmit ok */
    UINT64 xmitOk_HW {};

    /** receive error */
    UINT64 rcvError_HW {};

    /** transmit error */
    UINT64 xmitError_HW {};

    /** receive bytes */
    UINT64 rcvBytes_HW {};

    /** transmit bytes */
    UINT64 xmitBytes_HW {};

    /** receive no buffer */
    UINT64 rcvNoBuffer_HW {};

    /** signal quality */
    SHORT sqi {};

    /** hardware channel */
    WORD hardwareChannel {};

    /** reserved */
    DWORD reservedEthernetStatistic3 {};
};

}
}
