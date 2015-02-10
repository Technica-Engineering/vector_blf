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
#include <string>

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
    size_t size;

    // signature
    size = sizeof(signature);
    is.read((char *) &signature, size);

    // statisticsSize
    size = sizeof(statisticsSize);
    is.read((char *) &statisticsSize, size);

    // applicationId
    size = sizeof(applicationId);
    is.read((char *) &applicationId, size);

    // applicationMajor
    size = sizeof(applicationMajor);
    is.read((char *) &applicationMajor, size);

    // applicationMinor
    size = sizeof(applicationMinor);
    is.read((char *) &applicationMinor, size);

    // applicationBuild
    size = sizeof(applicationBuild);
    is.read((char *) &applicationBuild, size);

    // apiMajor
    size = sizeof(apiMajor);
    is.read((char *) &apiMajor, size);

    // apiMinor
    size = sizeof(apiMinor);
    is.read((char *) &apiMinor, size);

    // apiBuild
    size = sizeof(apiBuild);
    is.read((char *) &apiBuild, size);

    // apiPatch
    size = sizeof(apiPatch);
    is.read((char *) &apiPatch, size);

    // fileSize
    size = sizeof(fileSize);
    is.read((char *) &fileSize, size);

    // uncompressedFileSize
    size = sizeof(uncompressedFileSize);
    is.read((char *) &uncompressedFileSize, size);

    // objectCount
    size = sizeof(objectCount);
    is.read((char *) &objectCount, size);

    // objectsRead
    size = sizeof(objectsRead);
    is.read((char *) &objectsRead, size);

    // measurementStartTime
    size = sizeof(measurementStartTime);
    is.read((char *) &measurementStartTime, size);

    // lastObjectTime
    size = sizeof(lastObjectTime);
    is.read((char *) &lastObjectTime, size);

    // reserved
    size = sizeof(reserved);
    is.read((char *) &reserved, size);

    /* checks */
    if (signature != FileSignature) {
        std::cerr << "Unexpected file signature" << std::endl;
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

std::string FileStatistics::applicationName()
{
    switch(applicationId) {
    case Vector::BLF::ApplicationId::Unknown:
        return "unknown";
    case Vector::BLF::ApplicationId::Canalyzer:
        return "CANalyzer";
    case Vector::BLF::ApplicationId::Canoe:
        return "CANoe";
    case Vector::BLF::ApplicationId::Canstress:
        return "CANstress";
    case Vector::BLF::ApplicationId::Canlog:
        return "CANlog";
    case Vector::BLF::ApplicationId::Canape:
        return "CANape";
    case Vector::BLF::ApplicationId::Cancasexllog:
        return "CANcaseXL log";
    default:
        return std::to_string((unsigned short) applicationId);
    };
}

}
}
