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

bool StructuredCompressedFile::empty() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_data.empty();
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

void StructuredCompressedFile::pop_front() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_data.pop_front();
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

}
}
