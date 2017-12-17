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
 * @brief ETHERNET_STATISTIC
 */
class VECTOR_BLF_EXPORT EthernetStatistic final : public ObjectHeader
{
public:
    EthernetStatistic();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    WORD channel;
    WORD reservedEthernetStatistic1;
    DWORD reservedEthernetStatistic2;
    UINT64 rcvOk_HW;
    UINT64 xmitOk_HW;
    UINT64 rcvError_HW;
    UINT64 xmitError_HW;
    UINT64 rcvBytes_HW;
    UINT64 xmitBytes_HW;
    UINT64 rcvNoBuffer_HW;
    SHORT sqi;
    WORD hardwareChannel;
    DWORD reservedEthernetStatistic3;
};

}
}
