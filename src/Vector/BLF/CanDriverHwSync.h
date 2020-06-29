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
 * @brief CAN_DRIVER_SYNC
 *
 * Event that occurs when hardware sync is executed.
 */
struct VECTOR_BLF_EXPORT CanDriverHwSync final : ObjectHeader {
    CanDriverHwSync();

    std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it) override;
    void toData(std::vector<uint8_t> & data) override;
    DWORD calculateObjectSize() const override;

    /**
     * @brief channel where sync occured
     *
     * Application channel
     */
    WORD channel {};

    /** enumeration for flags */
    enum Flags : BYTE {
        /** sync was sent from this channel */
        Tx = 1,

        /** external sync received */
        Rx = 2,

        /** sync received but generated from this hardware */
        RxThis = 4
    };

    /** flags */
    BYTE flags {};

    /** reserved */
    BYTE reservedCanDriverHwSync1 {};

    /** reserved */
    DWORD reservedCanDriverHwSync2 {};
};

}
}
