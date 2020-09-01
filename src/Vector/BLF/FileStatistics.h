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

#include <Vector/BLF/AbstractFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * File signature
 */
const uint32_t FileSignature = 0x47474F4C; /* LOGG */

/**
 * Application ID
 */
enum ApplicationId : uint8_t {
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

    /** Vector Network Simulator */
    Vectornetworksimulator = 202,

    /** IPETRONIK Logger */
    Ipetroniklogger=203,

    /** RT PK */
    RtPk=204,

    /** PikeTec */
    Piketec=205,

    /** Sparks */
    Sparks=206
};

/** system time */
struct SYSTEMTIME {
    /** year */
    uint16_t year;

    /** month */
    uint16_t month;

    /** day of week (0=Sunday, 6=Saturday) */
    uint16_t dayOfWeek;

    /** day */
    uint16_t day;

    /** hour */
    uint16_t hour;

    /** minute */
    uint16_t minute;

    /** second */
    uint16_t second;

    /** milliseconds */
    uint16_t milliseconds;
};

/**
 * File statistics
 */
struct VECTOR_BLF_EXPORT FileStatistics final {
    FileStatistics() = default;
    virtual ~FileStatistics() noexcept = default;
    FileStatistics(const FileStatistics &) = default;
    FileStatistics & operator=(const FileStatistics &) = default;
    FileStatistics(FileStatistics &&) = default;
    FileStatistics & operator=(FileStatistics &&) = default;

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
    uint32_t calculateStatisticsSize() const;

    /** signature (signature) */
    uint32_t signature {FileSignature};

    /** sizeof(FileStatistics) */
    uint32_t statisticsSize {calculateStatisticsSize()};

    /** @todo unknown what this is */
    uint8_t unknown1 {};

    /** @todo unknown what this is */
    uint8_t unknown2 {};

    /** @todo unknown what this is */
    uint8_t unknown3 {};

    /** @todo unknown what this is */
    uint8_t unknown4 {};

    /** application ID */
    uint8_t applicationId {};

    /** number of objects read */
    uint8_t objectsRead {};

    /** application major number */
    uint8_t applicationMajor {};

    /** application minor number */
    uint8_t applicationMinor {};

    /** (compressed) file size in bytes */
    uint64_t fileSize {};

    /** uncompressed file size in bytes */
    uint64_t uncompressedFileSize {};

    /** number of objects */
    uint32_t objectCount {};

    /** application build number */
    uint32_t applicationBuild {};

    /** measurement start time */
    SYSTEMTIME measurementStartTime {};

    /** last object time */
    SYSTEMTIME lastObjectTime {};

    /** (compressed) file size without LogContainer+Unknown115 at end-of-file */
    uint64_t fileSizeWithoutUnknown115 {};

    /** reserved */
    std::array<uint32_t, 16> reservedFileStatistics {};
};

}
}
