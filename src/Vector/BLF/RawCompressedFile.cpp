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

#include <Vector/BLF/RawUncompressedFile.h>

#include <algorithm>
#undef NDEBUG
#include <cassert>
#include <vector>

namespace Vector {
namespace BLF {

RawCompressedFile::~RawCompressedFile() {
    close();
}

void RawCompressedFile::open(const char * filename, std::ios_base::openmode mode) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* correct file mode */
    mode |= std::ios_base::binary;

    /* open file */
    m_file.open(filename, mode);
    if (!m_file.is_open()) {
        return;
    }
    m_openMode = mode;

    /* set file size */
    m_file.seekg(0, std::ios_base::end);
    m_size = m_file.tellg();
    m_file.seekg(0);

    /* file statistics */
    if (m_openMode & std::ios_base::in) {
        m_statistics.read(m_file);
    }
    if (m_openMode & std::ios_base::out) {
        if (m_size == 0) {
            m_statistics.write(m_file);
        }
    }
}

bool RawCompressedFile::is_open() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.is_open();
}

void RawCompressedFile::close() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_file.is_open()) {
        return;
    }

    /* write file statistics */
    if (m_openMode & std::ios_base::out) {
        /* write Unknown115 */
        // @todo write Unknown115
        // m_statistics.fileSizeWithoutUnknown115 = m_size;
        // create Unknown115
        // create LogContainer logContainer;
        // write Unknown115 into LogContainer
        // write LogContainer
        // update m_size

        /* update file statistics */
        m_statistics.fileSize = m_size;

        /* write it */
        m_file.seekg(0);
        m_statistics.write(m_file);
    }

    /* close file */
    m_file.close();
}

RawCompressedFile::streamsize RawCompressedFile::read(char * s, RawCompressedFile::streamsize n) {
    assert(s || !n); // if n>0, then s!=nullptr

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.read(s, n);
    return m_file.gcount();
}

RawCompressedFile::streampos RawCompressedFile::tellg() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.tellg();
}

void RawCompressedFile::seekg(const RawCompressedFile::streampos pos) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.seekg(pos);
}

void RawCompressedFile::seekg(const RawCompressedFile::streamoff off, const std::ios_base::seekdir way) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.seekg(off, way);
}

RawCompressedFile::streamsize RawCompressedFile::write(const char * s, RawCompressedFile::streamsize n) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* write */
    std::streampos preWritePos = m_file.tellp();
    m_file.write(s, n);

    /* update file size */
    m_size = std::max(m_size, std::streamsize(m_file.tellp()));

    /* calc pcount */
    return m_file.tellp() - preWritePos;
}

RawCompressedFile::streampos RawCompressedFile::tellp() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.tellp();
}

void RawCompressedFile::seekp(const RawCompressedFile::streampos pos) {
    assert(pos == 0); // only to be used to write fileStatistics on close

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.seekp(pos);
}

void RawCompressedFile::seekp(const RawCompressedFile::streamoff off, const std::ios_base::seekdir way) {
    assert((off >= 0) && (way == std::ios_base::cur)); // only to be used to skip padding bytes

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* ensure zeros are written */
    std::vector<char> zero(off);
    m_file.write(zero.data(), zero.size());

    /* update file size */
    m_size = std::max(m_size, std::streamsize(m_file.tellp()));
}

bool RawCompressedFile::good() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.good();
}

bool RawCompressedFile::eof() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.eof();
}

bool RawCompressedFile::fail() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.fail();
}

bool RawCompressedFile::bad() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.bad();
}

std::ios_base::iostate RawCompressedFile::rdstate() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.rdstate();
}

void RawCompressedFile::setstate(std::ios_base::iostate state) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.setstate(state);
}

void RawCompressedFile::clear(std::ios_base::iostate state) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.clear(state);
}

RawCompressedFile::streamsize RawCompressedFile::size() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_size;
}

FileStatistics RawCompressedFile::statistics() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_statistics;
}

void RawCompressedFile::setApplication(const BYTE id, const BYTE major, const BYTE minor, const BYTE build) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_statistics.applicationId = id;
    m_statistics.applicationMajor = major;
    m_statistics.applicationMinor = minor;
    m_statistics.applicationBuild = build;
}

void RawCompressedFile::setApi(const BYTE major, const BYTE minor, const BYTE build, const BYTE patch) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_statistics.apiMajor = major;
    m_statistics.apiMinor = minor;
    m_statistics.apiBuild = build;
    m_statistics.apiPatch = patch;
}

void RawCompressedFile::setFileSize(const ULONGLONG fileSize) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_statistics.fileSize = fileSize;
}

void RawCompressedFile::setUncompressedFileSize(const ULONGLONG uncompressedFileSize) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_statistics.uncompressedFileSize = m_statistics.statisticsSize + uncompressedFileSize;
}

void RawCompressedFile::setObjectCount(const DWORD objectCount) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_statistics.objectCount = objectCount;
}

void RawCompressedFile::setObjectsRead(const DWORD objectsRead) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_statistics.objectsRead = objectsRead;
}

void RawCompressedFile::setMeasurementStartTime(const SYSTEMTIME measurementStartTime) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_statistics.measurementStartTime = measurementStartTime;
}

void RawCompressedFile::setLastObjectTime(const SYSTEMTIME lastObjectTime) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_statistics.lastObjectTime = lastObjectTime;
}

}
}
