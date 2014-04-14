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

#include <iostream>

#include "FileStatistics.h"

namespace Vector {
namespace BLF {

FileStatistics::FileStatistics() :
    signature(),
    statisticsSize(),
    applicationId(),
    applicationMajor(),
    applicationMinor(),
    applicationBuild(),
    apiMajor(),
    apiMinor(),
    apiBuild(),
    apiPatch(),
    fileSize(),
    uncompressedFileSize(),
    objectCount(),
    objectsRead(),
    measurementStartTime(),
    lastObjectTime(),
    reserved()
{
}

void FileStatistics::read(std::istream & is)
{
    /* read header */
    const std::streamsize size =
            sizeof(signature) +
            sizeof(statisticsSize) +
            sizeof(applicationId) +
            sizeof(applicationMajor) +
            sizeof(applicationMinor) +
            sizeof(applicationBuild) +
            sizeof(apiMajor) +
            sizeof(apiMinor) +
            sizeof(apiBuild) +
            sizeof(apiPatch) +
            sizeof(fileSize) +
            sizeof(uncompressedFileSize) +
            sizeof(objectCount) +
            sizeof(objectsRead) +
            sizeof(measurementStartTime) +
            sizeof(lastObjectTime) +
            sizeof(reserved);
    is.read((char *) &signature, size);

    /* checks */
    if (signature != FileSignature) {
        std::cerr << "Unexpected file signature" << std::endl;
        return;
    }
    if (statisticsSize != size) {
        std::cerr << "Unexpected statistics size" << std::endl;
        return;
    }
}

void FileStatistics::write(std::ostream & os)
{
    /* read header */
    const std::streamsize size =
            sizeof(signature) +
            sizeof(statisticsSize) +
            sizeof(applicationId) +
            sizeof(applicationMajor) +
            sizeof(applicationMinor) +
            sizeof(applicationBuild) +
            sizeof(apiMajor) +
            sizeof(apiMinor) +
            sizeof(apiBuild) +
            sizeof(apiPatch) +
            sizeof(fileSize) +
            sizeof(uncompressedFileSize) +
            sizeof(objectCount) +
            sizeof(objectsRead) +
            sizeof(measurementStartTime) +
            sizeof(lastObjectTime) +
            sizeof(reserved);
    os.write((char *) &signature, size);
}

}
}
