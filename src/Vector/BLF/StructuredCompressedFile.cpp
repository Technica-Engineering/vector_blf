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

#include <Vector/BLF/StructuredCompressedFile.h>

namespace Vector {
namespace BLF {

StructuredCompressedFile::StructuredCompressedFile(RawCompressedFile & rawCompressedFile) :
    m_rawCompressedFile(rawCompressedFile)
{
}

DWORD StructuredCompressedFile::defaultLogContainerSize() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_defaultLogContainerSize;
}

void StructuredCompressedFile::setDefaultLogContainerSize(DWORD defaultLogContainerSize) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set default log container size */
    m_defaultLogContainerSize = defaultLogContainerSize;
}

/* iterators */

StructuredCompressedFile::iterator StructuredCompressedFile::begin() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // return m_data.begin();
}

StructuredCompressedFile::const_iterator StructuredCompressedFile::begin() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // return m_data.begin();
}

StructuredCompressedFile::const_iterator StructuredCompressedFile::cbegin() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // return m_data.cbegin();
}

StructuredCompressedFile::iterator StructuredCompressedFile::end() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // return m_data.end();
}

StructuredCompressedFile::const_iterator StructuredCompressedFile::end() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // return m_data.end();
}

StructuredCompressedFile::const_iterator StructuredCompressedFile::cend() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    //return m_data.cend();
}

StructuredCompressedFile::reverse_iterator StructuredCompressedFile::rbegin() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    //return m_data.rbegin();
}

StructuredCompressedFile::const_reverse_iterator StructuredCompressedFile::rbegin() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    //return m_data.rbegin();
}

StructuredCompressedFile::const_reverse_iterator StructuredCompressedFile::crbegin() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    //return m_data.crbegin();
}

StructuredCompressedFile::reverse_iterator StructuredCompressedFile::rend() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    //return m_data.rend();
}

StructuredCompressedFile::const_reverse_iterator StructuredCompressedFile::rend() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    //return m_data.rend();
}

StructuredCompressedFile::const_reverse_iterator StructuredCompressedFile::crend() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    //return m_data.crend();
}

/* element access */

StructuredCompressedFile::reference StructuredCompressedFile::at(size_type n) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data.at(n);
}

StructuredCompressedFile::const_reference StructuredCompressedFile::at(size_type n) const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data.at(n);
}

StructuredCompressedFile::reference StructuredCompressedFile::operator[] (size_type n) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data[n];
}

StructuredCompressedFile::const_reference StructuredCompressedFile::operator[] (size_type n) const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data[n];
}

StructuredCompressedFile::reference StructuredCompressedFile::front() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data.front();
}

StructuredCompressedFile::const_reference StructuredCompressedFile::front() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data.front();
}

StructuredCompressedFile::reference StructuredCompressedFile::back() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data.back();
}

StructuredCompressedFile::const_reference StructuredCompressedFile::back() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data.back();
}

/* capacity */

bool StructuredCompressedFile::empty() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data.empty();
}

StructuredCompressedFile::size_type StructuredCompressedFile::size() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data.size();
}

/* modifiers */

void StructuredCompressedFile::clear() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_data.clear();
}

void StructuredCompressedFile::push_back(const StructuredCompressedFile::value_type & value) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_data.push_back(value);
}

void StructuredCompressedFile::push_back(StructuredCompressedFile::value_type && value) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_data.push_back(value);
}

StructuredCompressedFile::value_type StructuredCompressedFile::logContainerContaining(std::streampos pos) {
    /* loop over all logContainers */
    for (std::shared_ptr<LogContainer> logContainer : m_data) {
        /* when file position is contained ... */
        if ((pos >= logContainer->filePosition) &&
                (pos < logContainer->uncompressedFileSize + logContainer->filePosition)) {

            /* ... return log container */
            return logContainer;
        }
    }

    /* not found, so return nullptr */
    return nullptr;
}

void StructuredCompressedFile::init(StructuredCompressedFile::reference logContainerRef) {
//    // logContainerRef.uncompressedFilePosition = 0;
//    logContainerRef.uncompressedFileSize = m_defaultLogContainerSize;
//    logContainerRef.uncompressedFile.resize(logContainerRef.uncompressedFileSize);
}

void StructuredCompressedFile::load(StructuredCompressedFile::reference logContainerRef) {
//    m_rawCompressedFile.seekg(logContainerRef.compressedFilePosition);
//    LogContainer logContainer;
//    logContainer.read(m_rawCompressedFile);
//    logContainer.uncompress(logContainerRef.uncompressedFile);
}

void StructuredCompressedFile::save(StructuredCompressedFile::reference logContainerRef) {
//    LogContainer logContainer;
//    logContainer.compress(logContainerRef.uncompressedFile); // @todo compressionMethod, compressionLevel
//    m_rawCompressedFile.seekp(logContainerRef.compressedFilePosition);
//    logContainer.write(m_rawCompressedFile);
}

}
}
