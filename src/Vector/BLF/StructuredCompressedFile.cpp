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

#include <Vector/BLF/LogContainer.h>

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

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
        indexThread(); // @todo start index thread
        // @todo start read thread
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

    // @todo abort threads and wait to join

    m_rawCompressedFile.close();
}

StructuredCompressedFile::indexsize StructuredCompressedFile::read(ObjectHeaderBase ** objectHeaderBase) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* check if read position is valid */
    if (m_posg >= m_objectRefs.size()) {
        *objectHeaderBase = nullptr;
        return 0;
    }

    /* seek to log container */
    assert(m_posg < m_objectRefs.size()); // ensured by if above
    m_rawCompressedFile.seekg(m_objectRefs[m_posg].filePosition);

    /* read log container */
    LogContainer * logContainer = new LogContainer;
    assert(logContainer); // ensure memory is reserved
    (logContainer)->read(m_rawCompressedFile);
    assert((logContainer)->objectType == ObjectType::LOG_CONTAINER); // ensure this is a log container
    *objectHeaderBase = logContainer;
    assert(m_rawCompressedFile.good()); // ensure read is successful, otherwise index is wrong

    /* update status variables */
    m_posg++;

    return 1;
}

StructuredCompressedFile::indexpos StructuredCompressedFile::tellg() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_rawCompressedFile.is_open()) {
        return -1;
    }
    return m_posg;
}

void StructuredCompressedFile::seekg(const StructuredCompressedFile::indexpos pos) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* get raw file position and seek there */
    assert(pos < m_objectRefs.size()); // pos should not be out of index
    RawCompressedFile::streampos rawFilePosition = m_objectRefs[pos].filePosition;
    m_rawCompressedFile.seekg(rawFilePosition);

    /* set get pointer */
    m_posg = pos;
}

void StructuredCompressedFile::seekg(const StructuredCompressedFile::indexoff off, const std::ios_base::seekdir way) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* calculate new position */
    indexpos ref;
    switch(way) {
    case std::ios_base::beg:
        ref = 0;
        break;
    case std::ios_base::cur:
        ref = m_posg;
        break;
    case std::ios_base::end:
        ref = m_objectRefs.size();
        break;
    default:
        assert(false); // other cases should not happen
    }
    m_posg = ref + off;

    /* get raw file position and seek there */
    assert(m_posg < m_objectRefs.size()); // ensure posg is within index
    RawCompressedFile::streampos rawFilePosition = m_objectRefs[m_posg].filePosition;
    m_rawCompressedFile.seekg(rawFilePosition);
}

StructuredCompressedFile::indexsize StructuredCompressedFile::write(ObjectHeaderBase * objectHeaderBase) {
    LogContainer * logContainer = dynamic_cast<LogContainer *>(objectHeaderBase);
    assert(logContainer); // write no LogContainer doesn't make sense

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* add log container reference */
    ObjectRef objectRef;
    objectRef.filePosition = m_rawCompressedFile.tellp();
    m_objectRefs.push_back(objectRef);

    /* write log container */
    logContainer->write(m_rawCompressedFile); // @todo do this in writeThread
    delete logContainer;

    return 1;
}

StructuredCompressedFile::indexpos StructuredCompressedFile::tellp() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_rawCompressedFile.is_open()) {
        return -1;
    }
    return m_objectRefs.size();
}

StructuredCompressedFile::indexsize StructuredCompressedFile::size() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_objectRefs.size();
}

/* RawUncompressedFile pass-thru methods */

RawCompressedFile::streamsize StructuredCompressedFile::rawCompressedFileSize() const {
    return m_rawCompressedFile.size();
}

FileStatistics StructuredCompressedFile::statistics() const {
    return m_rawCompressedFile.statistics();
}

void StructuredCompressedFile::setApplication(const BYTE id, const BYTE major, const BYTE minor, const BYTE build) {
    m_rawCompressedFile.setApplication(id, major, minor, build);
}

void StructuredCompressedFile::setApi(const BYTE major, const BYTE minor, const BYTE build, const BYTE patch) {
    m_rawCompressedFile.setApi(major, minor, build, patch);
}

void StructuredCompressedFile::setUncompressedFileSize(const ULONGLONG uncompressedFileSize) {
    m_rawCompressedFile.setUncompressedFileSize(uncompressedFileSize);
}

void StructuredCompressedFile::setObjectCount(const DWORD objectCount) {
    m_rawCompressedFile.setObjectCount(objectCount);
}

void StructuredCompressedFile::setObjectsRead(const DWORD objectsRead) {
    m_rawCompressedFile.setObjectsRead(objectsRead);
}

void StructuredCompressedFile::setMeasurementStartTime(const SYSTEMTIME measurementStartTime) {
    m_rawCompressedFile.setMeasurementStartTime(measurementStartTime);
}

void StructuredCompressedFile::setLastObjectTime(const SYSTEMTIME lastObjectTime) {
    m_rawCompressedFile.setLastObjectTime(lastObjectTime);
}

/* threads */

void StructuredCompressedFile::indexThread() {
    // already locked by calling method open

    /* create index of all log containers */
    while(!m_rawCompressedFile.eof()) {
        /* prepare log container reference */
        ObjectRef objectRef;
        objectRef.filePosition = m_rawCompressedFile.tellg();

        /* read object header (not via read function as this would block) */
        DWORD signature;
        WORD headerSize;
        WORD headerVersion;
        DWORD objectSize;
        ObjectType objectType;
        if (m_rawCompressedFile.read(reinterpret_cast<char *>(&signature), sizeof(signature)) != sizeof(signature)) {
            // end-of-file reached
            break;
        }
        if (signature != ObjectSignature) {
            throw Exception("StructuredCompressedFile::indexThread(): Object signature doesn't match at this position.");
        }
        if (m_rawCompressedFile.read(reinterpret_cast<char *>(&headerSize), sizeof(headerSize)) +
            m_rawCompressedFile.read(reinterpret_cast<char *>(&headerVersion), sizeof(headerVersion)) +
            m_rawCompressedFile.read(reinterpret_cast<char *>(&objectSize), sizeof(objectSize)) +
            m_rawCompressedFile.read(reinterpret_cast<char *>(&objectType), sizeof(objectType)) !=
            sizeof(headerSize) + sizeof(headerVersion) + sizeof(objectSize) + sizeof(objectType)) {
            throw Exception("StructuredCompressedFile::indexThread(): Object Header cannot be read.");
        }
        if (objectType != ObjectType::LOG_CONTAINER) {
            throw Exception("StructuredCompressedFile::indexThread(): Object is not a LogContainer.");
        }

        /* add log container reference */
        m_objectRefs.push_back(objectRef);

        /* jump to next log container */
        RawCompressedFile::streamsize offset = objectSize;
        offset += objectSize % 4; // for ObjectType::LOG_CONTAINER;
        m_rawCompressedFile.seekg(objectRef.filePosition + offset);
    }
    m_rawCompressedFile.clear();

    /* seek back to first log container */
    RawCompressedFile::streampos rawFilePosition = m_objectRefs.front().filePosition;
    m_rawCompressedFile.seekg(rawFilePosition);
}

void StructuredCompressedFile::readThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo StructuredCompressedFile::readThread
}

void StructuredCompressedFile::writeThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo StructuredCompressedFile::writeThread
}

}
}
