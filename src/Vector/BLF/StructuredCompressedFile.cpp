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

#undef NDEBUG
#include <cassert>
#include <iostream>

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

StructuredCompressedFile::StructuredCompressedFile(RawCompressedFile & rawCompressedFile) :
    m_rawCompressedFile(rawCompressedFile)
{
}

StructuredCompressedFile::~StructuredCompressedFile() {
    close();
}

void StructuredCompressedFile::open(const char *filename, std::ios_base::openmode mode) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* open file */
    m_rawCompressedFile.open(filename, mode);
    if (!m_rawCompressedFile.is_open()) {
        return;
    }
    m_openMode = mode;

    /* start index/read thread */
    if (m_openMode & std::ios_base::in) {
        indexThread(); // @todo make this a thread
        // @todo start normal read thread
    }

    /* start write thread */
    if (m_openMode & std::ios_base::out) {
        // @todo start write thread
    }
}

bool StructuredCompressedFile::is_open() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_rawCompressedFile.is_open();
}

void StructuredCompressedFile::close() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo abort read thread
    // @todo wait till read/write threads finished

    m_rawCompressedFile.close();
}

StructuredCompressedFile::streamsize StructuredCompressedFile::read(LogContainer ** logContainer) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* check if read position is valid */
    if (m_posg >= m_logContainerRefs.size()) {
        *logContainer = nullptr;
        return 0;
    }

    /* seek to log container */
    assert(m_posg < m_logContainerRefs.size());
    m_rawCompressedFile.seekg(m_logContainerRefs[m_posg].filePosition);

    /* read log container */
    *logContainer = new LogContainer;
    assert(*logContainer);
    (*logContainer)->read(m_rawCompressedFile);
    assert(m_rawCompressedFile.good());

    /* update status variables */
    m_posg++;

    return 1;
}

StructuredCompressedFile::streampos StructuredCompressedFile::tellg() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_posg;
}

void StructuredCompressedFile::seekg(const StructuredCompressedFile::streampos pos) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* get raw file position and seek there */
    assert(pos < m_logContainerRefs.size());
    RawCompressedFile::streampos rawFilePosition = m_logContainerRefs[pos].filePosition;
    m_rawCompressedFile.seekg(rawFilePosition);

    /* set get pointer */
    m_posg = pos;
}

void StructuredCompressedFile::seekg(const StructuredCompressedFile::streamoff off, const std::ios_base::seekdir way) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* calculate new position */
    StructuredCompressedFile::streampos pos;
    switch(way) {
    case std::ios_base::beg:
        pos = 0;
        break;
    case std::ios_base::cur:
        pos = m_posg;
        break;
    case std::ios_base::end:
        pos = m_logContainerRefs.size();
        break;
    default:
        assert(false);
    }
    m_posg = pos + off;

    /* get raw file position and seek there */
    assert(m_posg < m_logContainerRefs.size());
    RawCompressedFile::streampos rawFilePosition = m_logContainerRefs[m_posg].filePosition;
    m_rawCompressedFile.seekg(rawFilePosition);
}

bool StructuredCompressedFile::write(LogContainer * logContainer) {
    assert(logContainer);

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* prepare LogContainerRef */
    LogContainerRef logContainerRef;
    logContainerRef.filePosition = m_rawCompressedFile.tellp();
    // @todo logContainerRef.logContainer = std::make_shared<LogContainer>(logContainer);
    m_logContainerRefs.push_back(logContainerRef);

    /* write log container */
    logContainer->write(m_rawCompressedFile); // @todo do this in thread

    return true;
}

StructuredCompressedFile::streampos StructuredCompressedFile::tellp() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_logContainerRefs.size();
}

StructuredCompressedFile::streamsize StructuredCompressedFile::size() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_logContainerRefs.size();
}

FileStatistics StructuredCompressedFile::statistics() const {
    // no lock needed as just pass-thru
    return m_rawCompressedFile.statistics();
}

void StructuredCompressedFile::setStatistics(const Vector::BLF::FileStatistics & statistics) {
    // no lock needed as just pass-thru
    m_rawCompressedFile.setStatistics(statistics);
}

void StructuredCompressedFile::indexThread() {
    // already locked by calling method open

    /* create index of all log containers */
    while(!m_rawCompressedFile.eof()) {
        /* prepare LogContainerRef */
        LogContainerRef logContainerRef;
        logContainerRef.filePosition = m_rawCompressedFile.tellg();

        /* read object header (not via read function as this would block) */
        DWORD signature;
        WORD headerSize;
        WORD headerVersion;
        DWORD objectSize;
        ObjectType objectType;
        m_rawCompressedFile.read(reinterpret_cast<char *>(&signature), sizeof(signature));
        if (m_rawCompressedFile.eof()) {
            break;
        }
        if (signature != ObjectSignature)
            throw Exception("StructuredCompressedFile::indexThread(): Object signature doesn't match at this position.");
        m_rawCompressedFile.read(reinterpret_cast<char *>(&headerSize), sizeof(headerSize));
        m_rawCompressedFile.read(reinterpret_cast<char *>(&headerVersion), sizeof(headerVersion));
        m_rawCompressedFile.read(reinterpret_cast<char *>(&objectSize), sizeof(objectSize));
        m_rawCompressedFile.read(reinterpret_cast<char *>(&objectType), sizeof(objectType));
        if (objectType != ObjectType::LOG_CONTAINER) {
            throw Exception("StructuredCompressedFile::indexThread(): Object is not a LogContainer.");
        }

        /* add log container reference */
        m_logContainerRefs.push_back(logContainerRef);

        /* jump to next log container */
        m_rawCompressedFile.seekg(logContainerRef.filePosition + RawCompressedFile::streamsize(objectSize + objectSize % 4));
    }
    m_rawCompressedFile.clear();

    /* seek back to first log container */
    RawCompressedFile::streampos rawFilePosition = m_logContainerRefs.front().filePosition;
    m_rawCompressedFile.seekg(rawFilePosition);
}

void StructuredCompressedFile::readThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo read containers from m_rawCompressedFile to m_logContainerRefs
}

void StructuredCompressedFile::writeThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo write containers from m_logContainerRefs to m_rawCompressedFile
}

}
}
