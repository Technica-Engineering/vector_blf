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

#include <array>
#include <vector>

#include <Vector/BLF/Types.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * File signature
 */
const DWORD FileSignature = 0x47474F4C; /* LOGG */

/**
 * Application ID
 */
enum ApplicationId : BYTE {
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
    Cancasexllog = 6,

    /** Vector Logger Configurator */
    Vlconfig = 7,

    /** Porsche Logger */
    Porschelogger = 200,

    /** CAETEC Logger */
    Caeteclogger = 201,
};

/**
 * File statistics
 */
struct VECTOR_BLF_EXPORT FileStatistics final {
    virtual ~FileStatistics() noexcept = default;

    /** @copydoc ObjectHeaderBase::fromData */
    virtual std::vector<uint8_t>::iterator fromData(std::vector<uint8_t>::iterator it);

    /** @copydoc ObjectHeaderBase::toData */
    virtual void toData(std::vector<uint8_t> & data);

    /**
     * Calculates the statisticsSize
     *
     * @return statistics size
     */
    DWORD calculateStatisticsSize() const;

    /** signature (signature) */
    DWORD signature {FileSignature};

    /** sizeof(FileStatistics) */
    DWORD statisticsSize {calculateStatisticsSize()};

    /** application ID (usually CANoe) */
    BYTE applicationId {};

    /** application major number (usually 0) */
    BYTE applicationMajor {};

    /** application minor number (usually 0) */
    BYTE applicationMinor {};

    /** application build number (usually 0) */
    BYTE applicationBuild {};

    /** BL API major number */
    BYTE apiMajor {4};

    /** BL API minor number */
    BYTE apiMinor {7};

    /** BL API build number */
    BYTE apiBuild {1};

    /** BL API patch number */
    BYTE apiPatch {0};

    /**
     * (compressed) file size in bytes
     *
     * @see File::compressedSize()
     */
    ULONGLONG fileSize {};

    /**
     * uncompressed file size in bytes
     *
     * @see File::uncompressedStatisticsSize()
     */
    ULONGLONG uncompressedFileSize {};

    /**
     * number of objects
     *
     * @see File::objectCount()
     */
    DWORD objectCount {};

    /** number of objects read */
    DWORD objectsRead {};

    /** measurement start time */
    SYSTEMTIME measurementStartTime {};

    /** last object time */
    SYSTEMTIME lastObjectTime {};

    /**
     * (compressed) file size without LogContainer+Unknown115 at end-of-file
     *
     * @see File::compressedSize()
     */
    ULONGLONG fileSizeWithoutUnknown115 {};

    /** reserved */
    std::array<DWORD, 16> reservedFileStatistics {};
};

}
}
