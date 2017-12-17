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

#include <array>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief A429_BUS_STATISTIC
 *
 * A429 bus statistic object
 */
class VECTOR_BLF_EXPORT A429BusStatistic final : public ObjectHeader
{
public:
    A429BusStatistic();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /** application channel */
    WORD channel;

    /** direction flag: 0=Rx, 1=Tx */
    BYTE dir;

    /** reserved */
    BYTE reservedA429BusStatistic;

    /** busload */
    ULONG busload;

    /** data total */
    ULONG dataTotal;

    /** error total */
    ULONG errorTotal;

    /** bitrate */
    ULONG bitrate;

    /** parity errors */
    USHORT parityErrors;

    /** bitrate errors */
    USHORT bitrateErrors;

    /** gap errors */
    USHORT gapErrors;

    /** line errors */
    USHORT lineErrors;

    /** format errors */
    USHORT formatErrors;

    /** duty factor errors */
    USHORT dutyFactorErrors;

    /** word length errors */
    USHORT wordLenErrors;

    /** coding errors */
    USHORT codingErrors;

    /** idle errors */
    USHORT idleErrors;

    /** level errors */
    USHORT levelErrors;

    /** label count */
    std::array<USHORT, 256> labelCount;
};

}
}
