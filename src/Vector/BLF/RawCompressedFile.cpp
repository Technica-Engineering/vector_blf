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

#include <cassert>
#include <vector>

namespace Vector {
namespace BLF {

RawCompressedFile::RawCompressedFile() :
    m_file()
{
}

void RawCompressedFile::open(const char * filename, std::ios_base::openmode mode) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.open(filename, mode);
}

bool RawCompressedFile::is_open() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.is_open();
}

void RawCompressedFile::close() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.close();
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

std::streamsize RawCompressedFile::gcount() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.gcount();
}

void RawCompressedFile::read(char * s, std::streamsize n) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.read(s, n);
}

std::streampos RawCompressedFile::tellg() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.tellg();
}

void RawCompressedFile::seekg(const std::streampos pos) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.seekg(pos);
}

void RawCompressedFile::seekg(const std::streamoff off, const std::ios_base::seekdir way) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.seekg(off, way);
}

void RawCompressedFile::write(const char * s, std::streamsize n) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.write(s, n);
}

std::streampos RawCompressedFile::tellp() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.tellp();
}

void RawCompressedFile::seekp(const std::streampos pos) {
    /* only to be used to write fileStatistics on close */
    assert(pos == 0);

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_file.seekp(pos);
}

void RawCompressedFile::seekp(const std::streamoff off, const std::ios_base::seekdir way) {
    /* only to be used to skip padding bytes */
    assert(off >= 0);
    assert(way == std::ios_base::cur);

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* ensure zeros are written */
    std::vector<char> zero(off);
    m_file.write(zero.data(), zero.size());
}

}
}
