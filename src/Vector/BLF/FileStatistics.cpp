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

#include <Vector/BLF/FileStatistics.h>

#include <algorithm>
#include <string>

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

std::vector<uint8_t>::iterator FileStatistics::fromData(std::vector<uint8_t>::iterator it) {
    signature =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    if (signature != FileSignature)
        throw Exception("FileStatistics::fromData(): File signature doesn't match.");
    statisticsSize =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    applicationId =
            (static_cast<BYTE>(*it++) <<  0);
    applicationMajor =
            (static_cast<BYTE>(*it++) <<  0);
    applicationMinor =
            (static_cast<BYTE>(*it++) <<  0);
    applicationBuild =
            (static_cast<BYTE>(*it++) <<  0);
    apiMajor =
            (static_cast<BYTE>(*it++) <<  0);
    apiMinor =
            (static_cast<BYTE>(*it++) <<  0);
    apiBuild =
            (static_cast<BYTE>(*it++) <<  0);
    apiPatch =
            (static_cast<BYTE>(*it++) <<  0);
    fileSize =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    uncompressedFileSize =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    objectCount =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    objectsRead =
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    measurementStartTime.year =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    measurementStartTime.month =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    measurementStartTime.dayOfWeek =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    measurementStartTime.day =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    measurementStartTime.hour =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    measurementStartTime.minute =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    measurementStartTime.second =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    measurementStartTime.milliseconds =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    lastObjectTime.year =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    lastObjectTime.month =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    lastObjectTime.dayOfWeek =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    lastObjectTime.day =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    lastObjectTime.hour =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    lastObjectTime.minute =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    lastObjectTime.second =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    lastObjectTime.milliseconds =
            (static_cast<WORD>(*it++) <<  0) |
            (static_cast<WORD>(*it++) <<  8);
    fileSizeWithoutUnknown115 =
            (static_cast<ULONGLONG>(*it++) <<  0) |
            (static_cast<ULONGLONG>(*it++) <<  8) |
            (static_cast<ULONGLONG>(*it++) << 16) |
            (static_cast<ULONGLONG>(*it++) << 24) |
            (static_cast<ULONGLONG>(*it++) << 32) |
            (static_cast<ULONGLONG>(*it++) << 40) |
            (static_cast<ULONGLONG>(*it++) << 48) |
            (static_cast<ULONGLONG>(*it++) << 56);
    std::generate(reservedFileStatistics.begin(), reservedFileStatistics.end(), [&it]() {
        return
            (static_cast<DWORD>(*it++) <<  0) |
            (static_cast<DWORD>(*it++) <<  8) |
            (static_cast<DWORD>(*it++) << 16) |
            (static_cast<DWORD>(*it++) << 24);
    });

    return it;
}

void FileStatistics::toData(std::vector<uint8_t> & data) {
    data.push_back((signature >>  0) & 0xff);
    data.push_back((signature >>  8) & 0xff);
    data.push_back((signature >> 16) & 0xff);
    data.push_back((signature >> 24) & 0xff);
    data.push_back((statisticsSize >>  0) & 0xff);
    data.push_back((statisticsSize >>  8) & 0xff);
    data.push_back((statisticsSize >> 16) & 0xff);
    data.push_back((statisticsSize >> 24) & 0xff);
    data.push_back((applicationId >>  0) & 0xff);
    data.push_back((applicationMajor >>  0) & 0xff);
    data.push_back((applicationMinor >>  0) & 0xff);
    data.push_back((applicationBuild >>  0) & 0xff);
    data.push_back((apiMajor >>  0) & 0xff);
    data.push_back((apiMinor >>  0) & 0xff);
    data.push_back((apiBuild >>  0) & 0xff);
    data.push_back((apiPatch >>  0) & 0xff);
    data.push_back((fileSize >>  0) & 0xff);
    data.push_back((fileSize >>  8) & 0xff);
    data.push_back((fileSize >> 16) & 0xff);
    data.push_back((fileSize >> 24) & 0xff);
    data.push_back((fileSize >> 32) & 0xff);
    data.push_back((fileSize >> 40) & 0xff);
    data.push_back((fileSize >> 48) & 0xff);
    data.push_back((fileSize >> 56) & 0xff);
    data.push_back((uncompressedFileSize >>  0) & 0xff);
    data.push_back((uncompressedFileSize >>  8) & 0xff);
    data.push_back((uncompressedFileSize >> 16) & 0xff);
    data.push_back((uncompressedFileSize >> 24) & 0xff);
    data.push_back((uncompressedFileSize >> 32) & 0xff);
    data.push_back((uncompressedFileSize >> 40) & 0xff);
    data.push_back((uncompressedFileSize >> 48) & 0xff);
    data.push_back((uncompressedFileSize >> 56) & 0xff);
    data.push_back((objectCount >>  0) & 0xff);
    data.push_back((objectCount >>  8) & 0xff);
    data.push_back((objectCount >> 16) & 0xff);
    data.push_back((objectCount >> 24) & 0xff);
    data.push_back((objectsRead >>  0) & 0xff);
    data.push_back((objectsRead >>  8) & 0xff);
    data.push_back((objectsRead >> 16) & 0xff);
    data.push_back((objectsRead >> 24) & 0xff);
    data.push_back((measurementStartTime.year >>  0) & 0xff);
    data.push_back((measurementStartTime.year >>  8) & 0xff);
    data.push_back((measurementStartTime.month >>  0) & 0xff);
    data.push_back((measurementStartTime.month >>  8) & 0xff);
    data.push_back((measurementStartTime.dayOfWeek >>  0) & 0xff);
    data.push_back((measurementStartTime.dayOfWeek >>  8) & 0xff);
    data.push_back((measurementStartTime.day >>  0) & 0xff);
    data.push_back((measurementStartTime.day >>  8) & 0xff);
    data.push_back((measurementStartTime.hour >>  0) & 0xff);
    data.push_back((measurementStartTime.hour >>  8) & 0xff);
    data.push_back((measurementStartTime.minute >>  0) & 0xff);
    data.push_back((measurementStartTime.minute >>  8) & 0xff);
    data.push_back((measurementStartTime.second >>  0) & 0xff);
    data.push_back((measurementStartTime.second >>  8) & 0xff);
    data.push_back((measurementStartTime.milliseconds >>  0) & 0xff);
    data.push_back((measurementStartTime.milliseconds >>  8) & 0xff);
    data.push_back((lastObjectTime.year >>  0) & 0xff);
    data.push_back((lastObjectTime.year >>  8) & 0xff);
    data.push_back((lastObjectTime.month >>  0) & 0xff);
    data.push_back((lastObjectTime.month >>  8) & 0xff);
    data.push_back((lastObjectTime.dayOfWeek >>  0) & 0xff);
    data.push_back((lastObjectTime.dayOfWeek >>  8) & 0xff);
    data.push_back((lastObjectTime.day >>  0) & 0xff);
    data.push_back((lastObjectTime.day >>  8) & 0xff);
    data.push_back((lastObjectTime.hour >>  0) & 0xff);
    data.push_back((lastObjectTime.hour >>  8) & 0xff);
    data.push_back((lastObjectTime.minute >>  0) & 0xff);
    data.push_back((lastObjectTime.minute >>  8) & 0xff);
    data.push_back((lastObjectTime.second >>  0) & 0xff);
    data.push_back((lastObjectTime.second >>  8) & 0xff);
    data.push_back((lastObjectTime.milliseconds >>  0) & 0xff);
    data.push_back((lastObjectTime.milliseconds >>  8) & 0xff);
    data.push_back((fileSizeWithoutUnknown115 >>  0) & 0xff);
    data.push_back((fileSizeWithoutUnknown115 >>  8) & 0xff);
    data.push_back((fileSizeWithoutUnknown115 >> 16) & 0xff);
    data.push_back((fileSizeWithoutUnknown115 >> 24) & 0xff);
    data.push_back((fileSizeWithoutUnknown115 >> 32) & 0xff);
    data.push_back((fileSizeWithoutUnknown115 >> 40) & 0xff);
    data.push_back((fileSizeWithoutUnknown115 >> 48) & 0xff);
    data.push_back((fileSizeWithoutUnknown115 >> 56) & 0xff);
    std::for_each(reservedFileStatistics.begin(), reservedFileStatistics.end(), [&data](const DWORD & d) {
        data.push_back((d >>  0) & 0xff);
        data.push_back((d >>  8) & 0xff);
        data.push_back((d >> 16) & 0xff);
        data.push_back((d >> 24) & 0xff);
    });
}

DWORD FileStatistics::calculateStatisticsSize() const {
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
        sizeof(fileSizeWithoutUnknown115) +
        static_cast<DWORD>(reservedFileStatistics.size() * sizeof(DWORD));
}

}
}
