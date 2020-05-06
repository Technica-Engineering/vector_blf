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
#include <Vector/BLF/ObjectHeader2.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief MOST_TRIGGER
 *
 * Transports changes of HW IO pins. The event is used for debugging purposes only.
 */
struct VECTOR_BLF_EXPORT MostTrigger final : ObjectHeader2 {
    MostTrigger();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    DWORD calculateObjectSize() const override;

    /**
     * @brief application channel
     *
     * Application channel
     */
    WORD channel {};

    /** reserved */
    WORD reservedMostTrigger {};

    /**
     * @brief trigger mode
     *
     * Trigger mode:
     *   - 0 – unknown
     *   - 1 – synchronization master
     *   - 2 – synchronization slave
     */
    WORD mode {};

    /**
     * @brief HW info
     *
     * HW that generated the trigger event
     *   - 0 – unknown
     *   - 1 – Optolyzer
     *   - 2 – reserved
     *   - 3 – reserved
     *   - 4 – VN2600/VN2610
     *   - 5 – OptoLyzer OL3150o
     *   - 6 – VN2640
     *   - 7 – OptoLyzer OL3050e
     *   - 8 – SMSC PCI 50
     *   - 9 – MOCCAcompact50e
     */
    WORD hw {};

    /**
     * value of IO register
     */
    DWORD previousTriggerValue {};

    /**
     * value of IO register
     */
    DWORD currentTriggerValue {};
};

}
}
