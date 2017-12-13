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

#include <cstring>

#include <Vector/BLF/AppText.h>

namespace Vector {
namespace BLF {

AppText::AppText() :
    ObjectHeader(),
    source(),
    reserved1(),
    textLength(),
    text()
{
    objectType = ObjectType::APP_TEXT;
}

void AppText::read(AbstractFile & is)
{
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&source), sizeof(source));
    is.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    is.read(reinterpret_cast<char *>(&textLength), sizeof(textLength));
    is.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    text.resize(textLength);
    is.read(const_cast<char *>(text.data()), textLength);

    /* skip padding */
    is.seekg(objectSize % 4, std::ios_base::cur);
}

void AppText::write(AbstractFile & os)
{
    /* pre processing */
    textLength = static_cast<DWORD>(text.size());

    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&source), sizeof(source));
    os.write(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
    os.write(reinterpret_cast<char *>(&textLength), sizeof(textLength));
    os.write(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
    os.write(const_cast<char *>(text.data()), textLength);

    /* skip padding */
    os.seekp(objectSize % 4, std::ios_base::cur);
}

DWORD AppText::calculateObjectSize() const
{
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(source) +
        sizeof(reserved1) +
        sizeof(textLength) +
        sizeof(reserved2) +
        textLength;
}

}
}
