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

#include <string>

#include "AbstractFile.h"
#include "FileStatistics.h"

namespace Vector {
namespace BLF {

FileStatistics::FileStatistics() :
    signature(FileSignature),
    statisticsSize(calculateStatisticsSize()),
    applicationId(),
    applicationMajor(),
    applicationMinor(),
    applicationBuild(),
    apiMajor(3),
    apiMinor(9),
    apiBuild(6),
    apiPatch(0),
    fileSize(),
    uncompressedFileSize(),
    objectCount(),
    objectsRead(),
    measurementStartTime(),
    lastObjectTime(),
    reserved()
{
}

void FileStatistics::read(AbstractFile & is)
{
    is.read((char *) &signature, sizeof(signature));
    if (signature != FileSignature) {
        return;
    }
    is.read((char *) &statisticsSize, sizeof(statisticsSize));
    if (statisticsSize != calculateStatisticsSize()) {
        return;
    }
    is.read((char *) &applicationId, sizeof(applicationId));
    is.read((char *) &applicationMajor, sizeof(applicationMajor));
    is.read((char *) &applicationMinor, sizeof(applicationMinor));
    is.read((char *) &applicationBuild, sizeof(applicationBuild));
    is.read((char *) &apiMajor, sizeof(apiMajor));
    is.read((char *) &apiMinor, sizeof(apiMinor));
    is.read((char *) &apiBuild, sizeof(apiBuild));
    is.read((char *) &apiPatch, sizeof(apiPatch));
    is.read((char *) &fileSize, sizeof(fileSize));
    is.read((char *) &uncompressedFileSize, sizeof(uncompressedFileSize));
    is.read((char *) &objectCount, sizeof(objectCount));
    is.read((char *) &objectsRead, sizeof(objectsRead));
    is.read((char *) &measurementStartTime, sizeof(measurementStartTime));
    is.read((char *) &lastObjectTime, sizeof(lastObjectTime));
    is.read((char *) reserved.data(), reserved.size() * sizeof(DWORD));
}

void FileStatistics::write(AbstractFile & os)
{
    os.write((char *) &signature, sizeof(signature));
    os.write((char *) &statisticsSize, sizeof(statisticsSize));
    os.write((char *) &applicationId, sizeof(applicationId));
    os.write((char *) &applicationMajor, sizeof(applicationMajor));
    os.write((char *) &applicationMinor, sizeof(applicationMinor));
    os.write((char *) &applicationBuild, sizeof(applicationBuild));
    os.write((char *) &apiMajor, sizeof(apiMajor));
    os.write((char *) &apiMinor, sizeof(apiMinor));
    os.write((char *) &apiBuild, sizeof(apiBuild));
    os.write((char *) &apiPatch, sizeof(apiPatch));
    os.write((char *) &fileSize, sizeof(fileSize));
    os.write((char *) &uncompressedFileSize, sizeof(uncompressedFileSize));
    os.write((char *) &objectCount, sizeof(objectCount));
    os.write((char *) &objectsRead, sizeof(objectsRead));
    os.write((char *) &measurementStartTime, sizeof(measurementStartTime));
    os.write((char *) &lastObjectTime, sizeof(lastObjectTime));
    os.write((char *) reserved.data(), reserved.size() * sizeof(DWORD));
}

size_t FileStatistics::calculateStatisticsSize()
{
    return
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
        reserved.size() * sizeof(DWORD);
}

}
}
