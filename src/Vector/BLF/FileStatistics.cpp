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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/Exceptions.h>
#include <Vector/BLF/FileStatistics.h>

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

FileStatistics::~FileStatistics()
{
}

void FileStatistics::read(AbstractFile & is)
{
    is.read(reinterpret_cast<char *>(&signature), sizeof(signature));
    if (signature != FileSignature) {
        throw FileSignatureMismatch();
    }
    is.read(reinterpret_cast<char *>(&statisticsSize), sizeof(statisticsSize));
    if (statisticsSize != calculateStatisticsSize()) {
        return;
    }
    is.read(reinterpret_cast<char *>(&applicationId), sizeof(applicationId));
    is.read(reinterpret_cast<char *>(&applicationMajor), sizeof(applicationMajor));
    is.read(reinterpret_cast<char *>(&applicationMinor), sizeof(applicationMinor));
    is.read(reinterpret_cast<char *>(&applicationBuild), sizeof(applicationBuild));
    is.read(reinterpret_cast<char *>(&apiMajor), sizeof(apiMajor));
    is.read(reinterpret_cast<char *>(&apiMinor), sizeof(apiMinor));
    is.read(reinterpret_cast<char *>(&apiBuild), sizeof(apiBuild));
    is.read(reinterpret_cast<char *>(&apiPatch), sizeof(apiPatch));
    is.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));
    is.read(reinterpret_cast<char *>(&uncompressedFileSize), sizeof(uncompressedFileSize));
    is.read(reinterpret_cast<char *>(&objectCount), sizeof(objectCount));
    is.read(reinterpret_cast<char *>(&objectsRead), sizeof(objectsRead));
    is.read(reinterpret_cast<char *>(&measurementStartTime), sizeof(measurementStartTime));
    is.read(reinterpret_cast<char *>(&lastObjectTime), sizeof(lastObjectTime));
    is.read(reinterpret_cast<char *>(reserved.data()), static_cast<std::streamsize>(reserved.size() * sizeof(DWORD)));
}

void FileStatistics::write(AbstractFile & os)
{
    os.write(reinterpret_cast<char *>(&signature), sizeof(signature));
    os.write(reinterpret_cast<char *>(&statisticsSize), sizeof(statisticsSize));
    os.write(reinterpret_cast<char *>(&applicationId), sizeof(applicationId));
    os.write(reinterpret_cast<char *>(&applicationMajor), sizeof(applicationMajor));
    os.write(reinterpret_cast<char *>(&applicationMinor), sizeof(applicationMinor));
    os.write(reinterpret_cast<char *>(&applicationBuild), sizeof(applicationBuild));
    os.write(reinterpret_cast<char *>(&apiMajor), sizeof(apiMajor));
    os.write(reinterpret_cast<char *>(&apiMinor), sizeof(apiMinor));
    os.write(reinterpret_cast<char *>(&apiBuild), sizeof(apiBuild));
    os.write(reinterpret_cast<char *>(&apiPatch), sizeof(apiPatch));
    os.write(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));
    os.write(reinterpret_cast<char *>(&uncompressedFileSize), sizeof(uncompressedFileSize));
    os.write(reinterpret_cast<char *>(&objectCount), sizeof(objectCount));
    os.write(reinterpret_cast<char *>(&objectsRead), sizeof(objectsRead));
    os.write(reinterpret_cast<char *>(&measurementStartTime), sizeof(measurementStartTime));
    os.write(reinterpret_cast<char *>(&lastObjectTime), sizeof(lastObjectTime));
    os.write(reinterpret_cast<char *>(reserved.data()), static_cast<std::streamsize>(reserved.size() * sizeof(DWORD)));
}

DWORD FileStatistics::calculateStatisticsSize() const
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
        static_cast<DWORD>(reserved.size() * sizeof(DWORD));
}

}
}
