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

#include <array>

#include "AbstractFile.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/** File signature */
const DWORD FileSignature = 0x47474F4C; /* LOGG */

/** Application ID */
enum class ApplicationId : BYTE {
    /** Unknown */
    Unknown = 0,

    /** CANalyzer */
    Canalyzer = 1,

    /** CANoe */
    Canoe = 2,

    /** CANstress */
    Canstress = 3,

    /** CANlog */
    Canlog = 4,

    /** CANape */
    Canape = 5,

    /** CANcaseXL log */
    Cancasexllog = 6
};

/**
 * @brief File statistics
 *
 * File statistics
 */
class VECTOR_BLF_EXPORT FileStatistics
{
public:
    FileStatistics();

    /**
     * read file statistics
     *
     * @param is input stream
     */
    virtual void read(AbstractFile & is);

    /**
     * write file statistics
     *
     * @param os output stream
     */
    virtual void write(AbstractFile & os);

    /**
     * Calculates the statisticsSize
     *
     * @return statistics size
     */
    size_t calculateStatisticsSize();

    /** signature (signature) */
    DWORD signature;

    /** sizeof(FileStatistics) */
    DWORD statisticsSize;

    /** application ID (usually CANoe) */
    ApplicationId applicationId;

    /** application major number (usually 0) */
    BYTE applicationMajor;

    /** application minor number (usually 0) */
    BYTE applicationMinor;

    /** application build number (usually 0) */
    BYTE applicationBuild;

    /** BL API major number (e.g. 3) */
    BYTE apiMajor;

    /** BL API minor number (e.g. 9) */
    BYTE apiMinor;

    /** BL API build number (e.g. 6) */
    BYTE apiBuild;

    /** BL API patch number (e.g. 0) */
    BYTE apiPatch;

    /** file size in bytes */
    ULONGLONG fileSize;

    /** uncompressed file size in bytes */
    ULONGLONG uncompressedFileSize;

    /** number of objects */
    DWORD objectCount;

    /** number of objects read */
    DWORD objectsRead;

    /** measurement start time */
    SYSTEMTIME measurementStartTime;

    /** last object time */
    SYSTEMTIME lastObjectTime;

    /** reserved */
    std::array<DWORD, 18> reserved;
};

}
}
