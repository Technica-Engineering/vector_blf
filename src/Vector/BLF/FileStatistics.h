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

#include <fstream>

#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/** File signature */
const DWORD FileSignature = 0x47474F4C; /* LOGG */

enumclass ApplicationId : BYTE {
    UNKNOWN = 0,
    CANALYZER = 1,
    CANOE = 2,
    CANSTRESS = 3,
    CANLOG = 4,
    CANAPE = 5,
    CANCASEXLLOG = 6
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

    virtual void read(std::istream & is);
    virtual void write(std::ostream & os);

    DWORD signature; /**< signature (signature) */
    DWORD statisticsSize; /**< sizeof(FileStatistics) */
    ApplicationId applicationId; /**< application ID (usually CANoe) */
    BYTE applicationMajor; /**< application major number (usually 0) */
    BYTE applicationMinor; /**< application minor number (usually 0) */
    BYTE applicationBuild; /**< application build number (usually 0) */
    BYTE apiMajor; /**< BL API major number (e.g. 3) */
    BYTE apiMinor; /**< BL API minor number (e.g. 9) */
    BYTE apiBuild; /**< BL API build number (e.g. 6) */
    BYTE apiPatch; /**< BL API patch number (e.g. 0) */
    ULONGLONG fileSize; /**< file size in bytes */
    ULONGLONG uncompressedFileSize; /**< uncompressed file size in bytes */
    DWORD objectCount; /**< number of objects */
    DWORD objectsRead; /**< number of objects read */
    SYSTEMTIME measurementStartTime; /**< measurement start time */
    SYSTEMTIME lastObjectTime; /**< last object time */
    DWORD reserved[18]; /**< reserved */
};

}
}
