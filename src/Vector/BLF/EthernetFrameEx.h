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

#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief ETHERNET_FRAME_EX
 */
class VECTOR_BLF_EXPORT EthernetFrameEx final : public ObjectHeader
{
public:
    EthernetFrameEx();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;
    virtual WORD calculateStructLength() const;

    /**
     * @brief Length of this structure, without sizeof(VBLObjectHeader), without mStructLength member and without mFrameData member
     */
    WORD structLength;

    /**
     * @brief flags, which indicates the valid fields:
     *   - Bit 0 - normal packet = 0, forwarded packet = 1
     *   - Bit 1 - mHardwareChannel valid
     *   - Bit 2 - mFrameDuration valid
     *   - Bit 3 - mFrameChecksum valid
     *   - Bit 4 - mFrameHandle valid
     */
    WORD flags;

    /**
     * @brief application channel, i.e. Eth 1
     */
    WORD channel;

    /**
     * @brief HW channel
     */
    WORD hardwareChannel;

    /**
     * @brief Transmission duration in [ns]
     */
    UINT64 frameDuration;

    /**
     * @brief Ethernet checksum
     */
    DWORD frameChecksum;

    /**
     * @brief Direction flag: 0=Rx, 1=Tx, 2=TxRq
     */
    WORD dir;

    /**
     * @brief Number of valid frameData bytes
     */
    WORD frameLength;

    /**
     * @brief Handle which refer the corresponding EthernetFrameForwarded event
     */
    DWORD frameHandle;

    /** reserved */
    DWORD reservedEthernetFrameEx;

    /**
     * @brief Max 1612 data bytes per frame. Contains Ethernet header + Ethernet payload
     */
    std::vector<BYTE> frameData;
};

}
}
