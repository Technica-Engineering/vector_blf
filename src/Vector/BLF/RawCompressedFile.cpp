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

#undef NDEBUG
#include <cassert>
#include <vector>

namespace Vector {
namespace BLF {

RawCompressedFile::RawCompressedFile() {
}

RawCompressedFile::~RawCompressedFile() {
    close();
}

void RawCompressedFile::open(const char * filename, std::ios_base::openmode mode) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* correct file mode */
    mode |= std::ios_base::binary;
    if (mode & std::ios_base::out) {
        mode |= std::ios_base::app;
    }

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

    /* read file statistics */
    if (m_openMode & std::ios_base::in) {
        m_statistics.read(m_file);
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
        m_file.seekg(0);
        m_statistics.write(m_file);
    }

    /* close file */
    m_file.close();
}

RawCompressedFile::streamsize RawCompressedFile::read(char * s, RawCompressedFile::streamsize n) {
    assert(s);

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

    std::streampos preWritePos = m_file.tellp();
    m_file.write(s, n);
    return m_file.tellp() - preWritePos;
}

RawCompressedFile::streampos RawCompressedFile::tellp() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.tellp();
}

void RawCompressedFile::seekp(const RawCompressedFile::streampos pos) {
    /* only to be used to write fileStatistics on close */
    assert(pos == 0);

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.seekp(pos);
}

void RawCompressedFile::seekp(const RawCompressedFile::streamoff off, const std::ios_base::seekdir way) {
    /* only to be used to skip padding bytes */
    assert(off >= 0);
    assert(way == std::ios_base::cur);

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* ensure zeros are written */
    std::vector<char> zero(off);
    m_file.write(zero.data(), zero.size());
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

void RawCompressedFile::setStatistics(const Vector::BLF::FileStatistics & statistics) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_statistics = statistics;
}

}
}
