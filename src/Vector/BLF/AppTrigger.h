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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief APP_TRIGGER
 *
 * Application defined trigger to be saved in BLF log file (currently not used in CANoe
 * / CANalyzer).
 */
struct VECTOR_BLF_EXPORT AppTrigger final : ObjectHeader {
    AppTrigger();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief pre-trigger time
     *
     * Pre trigger time.
     */
    uint64_t preTriggerTime {};

    /**
     * @brief post-trigger time
     *
     * Post trigger time.
     */
    uint64_t postTriggerTime {};

    /**
     * @brief channel of event which triggered (if any)
     *
     * Trigger that channel belongs to.
     */
    uint16_t channel {};

    /** enumeration for flags */
    enum Flags : uint16_t {
        /** single trigger type */
        SingleTrigger = 0x0000,

        /** start of logging trigger type */
        LoggingStart = 0x0001,

        /** stop of logging trigger type */
        LoggingStop = 0x0002
    };

    /**
     * @brief trigger type
     */
    uint16_t flags {};

    /**
     * @brief app specific member 2
     *
     * Reserved.
     */
    uint32_t appSpecific2 {};
};

}
}
