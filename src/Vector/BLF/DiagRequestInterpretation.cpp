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

#include <Vector/BLF/DiagRequestInterpretation.h>

namespace Vector {
namespace BLF {

DiagRequestInterpretation::DiagRequestInterpretation() :
    ObjectHeader(ObjectType::DIAG_REQUEST_INTERPRETATION) {
}

std::vector<uint8_t>::iterator DiagRequestInterpretation::fromData(std::vector<uint8_t>::iterator it) {
    it = ObjectHeader::fromData(it);

    diagDescriptionHandle =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    diagVariantHandle =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    diagServiceHandle =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    ecuQualifierLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    variantQualifierLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    serviceQualifierLength =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    ecuQualifier.resize(ecuQualifierLength);
    std::copy(it, it + this->ecuQualifier.size(), std::begin(ecuQualifier));
    it += this->ecuQualifier.size();
    variantQualifier.resize(variantQualifierLength);
    std::copy(it, it + this->variantQualifier.size(), std::begin(variantQualifier));
    it += this->variantQualifier.size();
    serviceQualifier.resize(serviceQualifierLength);
    std::copy(it, it + this->serviceQualifier.size(), std::begin(serviceQualifier));
    it += this->serviceQualifier.size();

    return it;
}

void DiagRequestInterpretation::toData(std::vector<uint8_t> & data) {
    /* pre processing */
    ecuQualifierLength = static_cast<DWORD>(ecuQualifier.size());
    variantQualifierLength = static_cast<DWORD>(variantQualifier.size());
    serviceQualifierLength = static_cast<DWORD>(serviceQualifier.size());

    ObjectHeader::toData(data);

    data.push_back((diagDescriptionHandle >>  0) & 0xff);
    data.push_back((diagDescriptionHandle >>  8) & 0xff);
    data.push_back((diagDescriptionHandle >> 16) & 0xff);
    data.push_back((diagDescriptionHandle >> 24) & 0xff);
    data.push_back((diagVariantHandle >>  0) & 0xff);
    data.push_back((diagVariantHandle >>  8) & 0xff);
    data.push_back((diagVariantHandle >> 16) & 0xff);
    data.push_back((diagVariantHandle >> 24) & 0xff);
    data.push_back((diagServiceHandle >>  0) & 0xff);
    data.push_back((diagServiceHandle >>  8) & 0xff);
    data.push_back((diagServiceHandle >> 16) & 0xff);
    data.push_back((diagServiceHandle >> 24) & 0xff);
    data.push_back((ecuQualifierLength >>  0) & 0xff);
    data.push_back((ecuQualifierLength >>  8) & 0xff);
    data.push_back((ecuQualifierLength >> 16) & 0xff);
    data.push_back((ecuQualifierLength >> 24) & 0xff);
    data.push_back((variantQualifierLength >>  0) & 0xff);
    data.push_back((variantQualifierLength >>  8) & 0xff);
    data.push_back((variantQualifierLength >> 16) & 0xff);
    data.push_back((variantQualifierLength >> 24) & 0xff);
    data.push_back((serviceQualifierLength >>  0) & 0xff);
    data.push_back((serviceQualifierLength >>  8) & 0xff);
    data.push_back((serviceQualifierLength >> 16) & 0xff);
    data.push_back((serviceQualifierLength >> 24) & 0xff);
    data.insert(std::end(data), std::begin(ecuQualifier), std::end(ecuQualifier));
    data.insert(std::end(data), std::begin(variantQualifier), std::end(variantQualifier));
    data.insert(std::end(data), std::begin(serviceQualifier), std::end(serviceQualifier));
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
