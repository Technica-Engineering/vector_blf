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

#include <string>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief APP_TEXT
 *
 * Application defined text to be saved in BLF log file (currently not used in
 * CANoe/CANalyzer).
 */
class VECTOR_BLF_EXPORT AppText final : public ObjectHeader
{
public:
    AppText();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /** enumeration for source */
    enum Source : DWORD {
        /** measurement comment */
        MeasurementComment = 0x00000000,

        /** database channel info */
        DbChannelInfo = 0x00000001,

        /** meta data */
        MetaData = 0x00000002,
    };

    /**
     * @brief source of text
     *
     * Defines the source/semantic of the text. Actually two
     * different values are defined:
     *
     * 0: Measurement comment
     * - reserved is not used
     * - text contains a measurement comment
     *
     * 1: Database channel information
     * - reserved contains channel information. The following
     * - table show how the 4 bytes are used:
     *   - Bit 0-7: Version of the data
     *   - Bit 8-15: Channel number
     *   - Bit 15-23: Bus type of the channel. One of the
     *     following values:
     *     - 1: BL_BUSTYPE_CAN
     *     - 5: BL_BUSTYPE_LIN
     *     - 6: BL_BUSTYPE_MOST
     *     - 7: BL_BUSTYPE_FLEXRAY
     *     - 9: BL_BUSTYPE_J1708
     *     - 10: BL_BUSTYPE_ETHERNET
     *     - 13: BL_BUSTYPE_WLAN
     *     - 14: BL_BUSTYPE_AFDX
     *   - Bit 24: Flag, that determines, if channel is a CAN-
     *     FD channel
     *   - Bit 25-31: Unused at the moment
     * - text contains database information for the specific
     *   channel. Each database is defined by the database path and
     *   the cluster name (if available). The single databases and the
     *   cluster name are separated by a semicolon. Example:
     *   \<Path1\>;\<ClusterName1\>;\<Path2\>;\<ClusterName2\>;...
     *   If for a database there's no cluster name available, an
     *   empty string is written as cluster name.
     *
     * 2: Meta data
     */
    DWORD source {};

    /**
     * @brief reserved
     *
     * Depends on source.
     */
    DWORD reservedAppText1 {};

    /**
     * @brief text length in bytes
     *
     * Length of text without ending 0.
     */
    DWORD textLength {};

    /** reserved */
    DWORD reservedAppText2 {};

    /**
     * @brief text in MBCS
     *
     * Text to be saved to log file.
     */
    std::string text {};
};

}
}
