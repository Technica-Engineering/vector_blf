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

#include "platform.h"

#include "AbstractFile.h"
#include "ObjectHeader.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief DIAG_REQUEST_INTERPRETATION
 */
class VECTOR_BLF_EXPORT DiagRequestInterpretation final : public ObjectHeader
{
public:
    DiagRequestInterpretation();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * unique ID identifying the used diagnostic description
     */
    DWORD diagDescriptionHandle;

    /**
     * unique ID identifying the used diagnostic variant
     */
    DWORD diagVariantHandle;

    /**
     * unique ID identifying the used diagnostic service
     */
    DWORD diagServiceHandle;

    /**
     * string length for ecuQualifier
     */
    DWORD ecuQualifierLength;

    /**
     * string length for variantQualifier
     */
    DWORD variantQualifierLength;

    /**
     * string length for serviceQualifier
     */
    DWORD serviceQualifierLength;

    /**
     * qualifier of the ECU the request was sent to
     */
    std::string ecuQualifier;

    /**
     * qualifier of the active diagnostic variant
     */
    std::string variantQualifier;

    /**
     * qualifier of the diagnostic service
     */
    std::string serviceQualifier;
};

}
}
