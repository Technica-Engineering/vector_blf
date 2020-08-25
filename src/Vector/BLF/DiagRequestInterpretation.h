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
 * @brief DIAG_REQUEST_INTERPRETATION
 */
struct VECTOR_BLF_EXPORT DiagRequestInterpretation final : ObjectHeader {
    DiagRequestInterpretation();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /**
     * @brief unique ID identifying the used diagnostic description
     */
    uint32_t diagDescriptionHandle {};

    /**
     * @brief unique ID identifying the used diagnostic variant
     */
    uint32_t diagVariantHandle {};

    /**
     * @brief unique ID identifying the used diagnostic service
     */
    uint32_t diagServiceHandle {};

    /**
     * @brief string length for ecuQualifier
     */
    uint32_t ecuQualifierLength {};

    /**
     * @brief string length for variantQualifier
     */
    uint32_t variantQualifierLength {};

    /**
     * @brief string length for serviceQualifier
     */
    uint32_t serviceQualifierLength {};

    /**
     * @brief qualifier of the ECU the request was sent to
     */
    std::string ecuQualifier {};

    /**
     * @brief qualifier of the active diagnostic variant
     */
    std::string variantQualifier {};

    /**
     * @brief qualifier of the diagnostic service
     */
    std::string serviceQualifier {};
};

}
}
