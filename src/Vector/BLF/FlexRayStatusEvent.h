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

#include <array>

#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/RawFile.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief FLEXRAY_STATUS
 *
 * @deprecated
 */
struct VECTOR_BLF_EXPORT FlexRayStatusEvent final : ObjectHeader {
    FlexRayStatusEvent();

    void read(RawFile & is) override;
    void write(RawFile & os) override;
    DWORD calculateObjectSize() const override;

    /**
     * @brief application channel
     */
    WORD channel {};

    /**
     * @brief object version
     */
    WORD version {};

    /**
     * @brief type of status event
     */
    WORD statusType {};

    /**
     * @brief additional info 1
     */
    WORD infoMask1 {};

    /**
     * @brief additional info 2
     */
    WORD infoMask2 {};

    /**
     * @brief additional info 3
     */
    WORD infoMask3 {};

    /** reserved */
    std::array<WORD, 18> reservedFlexRayStatusEvent {};
};

}
}
