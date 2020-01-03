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

#include <Vector/BLF/DiagRequestInterpretation.h>

namespace Vector {
namespace BLF {

DiagRequestInterpretation::DiagRequestInterpretation() :
    ObjectHeader() {
    objectType = ObjectType::DIAG_REQUEST_INTERPRETATION;
}

void DiagRequestInterpretation::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&diagDescriptionHandle), sizeof(diagDescriptionHandle));
    is.read(reinterpret_cast<char *>(&diagVariantHandle), sizeof(diagVariantHandle));
    is.read(reinterpret_cast<char *>(&diagServiceHandle), sizeof(diagServiceHandle));
    is.read(reinterpret_cast<char *>(&ecuQualifierLength), sizeof(ecuQualifierLength));
    is.read(reinterpret_cast<char *>(&variantQualifierLength), sizeof(variantQualifierLength));
    is.read(reinterpret_cast<char *>(&serviceQualifierLength), sizeof(serviceQualifierLength));
    ecuQualifier.resize(ecuQualifierLength);
    is.read(const_cast<char *>(ecuQualifier.data()), ecuQualifierLength);
    variantQualifier.resize(variantQualifierLength);
    is.read(const_cast<char *>(variantQualifier.data()), variantQualifierLength);
    serviceQualifier.resize(serviceQualifierLength);
    is.read(const_cast<char *>(serviceQualifier.data()), serviceQualifierLength);
}

void DiagRequestInterpretation::write(AbstractFile & os) {
    /* pre processing */
    ecuQualifierLength = static_cast<DWORD>(ecuQualifier.size());
    variantQualifierLength = static_cast<DWORD>(variantQualifier.size());
    serviceQualifierLength = static_cast<DWORD>(serviceQualifier.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&diagDescriptionHandle), sizeof(diagDescriptionHandle));
    os.write(reinterpret_cast<char *>(&diagVariantHandle), sizeof(diagVariantHandle));
    os.write(reinterpret_cast<char *>(&diagServiceHandle), sizeof(diagServiceHandle));
    os.write(reinterpret_cast<char *>(&ecuQualifierLength), sizeof(ecuQualifierLength));
    os.write(reinterpret_cast<char *>(&variantQualifierLength), sizeof(variantQualifierLength));
    os.write(reinterpret_cast<char *>(&serviceQualifierLength), sizeof(serviceQualifierLength));
    os.write(const_cast<char *>(ecuQualifier.data()), ecuQualifierLength);
    os.write(const_cast<char *>(variantQualifier.data()), variantQualifierLength);
    os.write(const_cast<char *>(serviceQualifier.data()), serviceQualifierLength);
}

DWORD DiagRequestInterpretation::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(diagDescriptionHandle) +
        sizeof(diagVariantHandle) +
        sizeof(diagServiceHandle) +
        sizeof(ecuQualifierLength) +
        sizeof(variantQualifierLength) +
        sizeof(serviceQualifierLength) +
        ecuQualifierLength +
        variantQualifierLength +
        serviceQualifierLength;
}

}
}
