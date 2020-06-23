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

#include <Vector/BLF/LogContainer.h>

namespace Vector {
namespace BLF {

RawUncompressedFile::~RawUncompressedFile() {
    close();
}

void RawUncompressedFile::open(const char * filename, std::ios_base::openmode mode) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* open file */
    m_structuredCompressedFile.open(filename, mode);
    if (!m_structuredCompressedFile.is_open()) {
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

bool RawUncompressedFile::is_open() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_structuredCompressedFile.is_open();
}

void RawUncompressedFile::close() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_structuredCompressedFile.is_open()) {
        return;
    }

    // @todo abort threads and wait to join

    /* close actions */
    if (m_openMode & std::ios_base::out) {
        /* finish log container */
        shrinkLogContainer();
        writeLogContainer();

        /* set FileStatistics::uncompressedFileSize */
        m_structuredCompressedFile.setUncompressedFileSize(m_statisticsSize);
    }

    m_structuredCompressedFile.close();
}

RawUncompressedFile::streamsize RawUncompressedFile::read(char * s, const RawUncompressedFile::streamsize n) {
    assert(s || !n); // if n>0, then s!=nullptr

    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* read data */
    streamsize totalSize = 0;
    while (totalSize < n) {
        /* find starting object */
        std::map<streampos, ObjectRef>::iterator objectRef =
                std::find_if(m_objectRefs.begin(), m_objectRefs.end(), [&](const std::pair<streampos, ObjectRef> & objectRef) {
            return (objectRef.first <= m_posg) &&
                   (m_posg < objectRef.first + objectRef.second.fileSize);
        });

        /* not found, so abort read here */
        if (objectRef == m_objectRefs.end()) {
            return totalSize;
        }

        /* load data if needed */
        if (objectRef->second.uncompressedFile.empty()) {
            /* read object */
            StructuredCompressedFile::indexpos index = std::distance(m_objectRefs.begin(), objectRef);
            m_structuredCompressedFile.seekg(index);
            ObjectHeaderBase * objectHeaderBase = nullptr;
            if (m_structuredCompressedFile.read(&objectHeaderBase)) {
                assert(objectHeaderBase);
                LogContainer * logContainer = dynamic_cast<LogContainer *>(objectHeaderBase);
                if (logContainer) {
                    logContainer->uncompress(objectRef->second.uncompressedFile); // @todo do this in readThread
                } else {
                    assert(false); // not implemented yet
                    // @todo copy if this is not a log container
                }
                delete objectHeaderBase;
            } else {
                assert(!objectHeaderBase); // no delete necessary
                return totalSize;
            }
        }

        /* copy data */
        streamoff offset = m_posg - objectRef->first;
        assert(offset >= 0);
        streamsize size = std::min(n - totalSize, objectRef->second.fileSize - offset);
        assert(size); // an empty objectRef doesn't make sense
        assert(objectRef->second.uncompressedFile.cbegin() + offset + size <= objectRef->second.uncompressedFile.cend()); // check source size
        std::copy(objectRef->second.uncompressedFile.cbegin() + offset,
                  objectRef->second.uncompressedFile.cbegin() + offset + size,
                  s);

        /* update counters */
        m_posg += size;
        s += size;
        totalSize += size;
    }

    return totalSize;
}

RawUncompressedFile::streampos RawUncompressedFile::tellg() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_structuredCompressedFile.is_open()) {
        return -1;
    }
    return m_posg;
}

void RawUncompressedFile::seekg(const RawUncompressedFile::streampos pos) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* new get position */
    m_posg = pos;
}

void RawUncompressedFile::seekg(const RawUncompressedFile::streamoff off, const std::ios_base::seekdir way) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* calculate new position */
    streampos ref;
    switch(way) {
    case std::ios_base::beg:
        ref = 0;
        break;
    case std::ios_base::cur:
        ref = m_posg;
        break;
    case std::ios_base::end:
        ref = m_posp; // posp is always at the end
        break;
    default:
        assert(false); // other cases should not happen
    }
    m_posg = ref + off;
}

RawUncompressedFile::streamsize RawUncompressedFile::write(const char * s, const RawUncompressedFile::streamsize n) {
    assert(s || !n); // if n>0, then s!=nullptr

    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* write data */
    streamsize totalSize = 0;
    while (totalSize < n) {
        /* find starting log container */
        std::map<streampos, ObjectRef>::iterator objectRef = m_objectRefs.find(m_posp);

        /* not found, so append new log container */
        if (objectRef == m_objectRefs.end()) {
            /* prepare log container reference */
            streampos newFilePosition = m_size;
            ObjectRef newObjectRef;

            /* write the current log container */
            if (!m_objectRefs.empty()) {
                /* compress and write log container */
                writeLogContainer();
            }

            /* append log container reference */
            newObjectRef.fileSize = m_defaultLogContainerSize;
            newObjectRef.uncompressedFile.resize(m_defaultLogContainerSize);
            assert(newObjectRef.uncompressedFile.size() == m_defaultLogContainerSize);
            m_objectRefs[newFilePosition] = newObjectRef;
            objectRef = std::prev(m_objectRefs.end());
        }
        assert(objectRef != m_objectRefs.end());
        if (objectRef->second.uncompressedFile.empty()) {
            assert(!objectRef->second.uncompressedFile.empty());
        }
        assert(objectRef->second.fileSize == std::streamsize(objectRef->second.uncompressedFile.size()));

        /* copy data */
        streamoff offset = m_posp - objectRef->first;
        streamsize size = std::min(n - totalSize, objectRef->second.fileSize - offset);
        assert(size); // logContainerRef would be wrong otherwise
        assert(objectRef->second.uncompressedFile.begin() + offset + size <= objectRef->second.uncompressedFile.end()); // check destination size
        std::copy(s,
                  s + size,
                  objectRef->second.uncompressedFile.begin() + offset);

        /* update counters */
        m_posp += size;
        s += size;
        totalSize += size;
    }

    return totalSize;
}

RawUncompressedFile::streampos RawUncompressedFile::tellp() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_structuredCompressedFile.is_open()) {
        return -1;
    }
    return m_posp;
}

void RawUncompressedFile::seekp(const RawUncompressedFile::streampos /*pos*/) {
    /* should not be used */
    assert(false);
}

void RawUncompressedFile::seekp(const RawUncompressedFile::streamoff off, const std::ios_base::seekdir way) {
    assert((off >= 0) && (way == std::ios_base::cur)); // only to be used to skip padding bytes

    std::vector<char> zero(off);
    write(zero.data(), zero.size()); // write does the lock
}

RawUncompressedFile::streamsize RawUncompressedFile::size() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_size;
}

RawUncompressedFile::streamsize RawUncompressedFile::statisticsSize() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_statisticsSize;
}

DWORD RawUncompressedFile::defaultLogContainerSize() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_defaultLogContainerSize;
}

void RawUncompressedFile::setDefaultLogContainerSize(DWORD defaultLogContainerSize) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set default log container size */
    m_defaultLogContainerSize = defaultLogContainerSize;
}

int RawUncompressedFile::compressionMethod() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_compressionMethod;
}

void RawUncompressedFile::setCompressionMethod(const int compressionMethod) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_compressionMethod = compressionMethod;
}

int RawUncompressedFile::compressionLevel() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_compressionLevel;
}

void RawUncompressedFile::setCompressionLevel(const int compressionLevel) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_compressionLevel = compressionLevel;
}

void RawUncompressedFile::finishLogContainer() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    shrinkLogContainer();
}

/* StructuredCompressedFile pass-thru methods */

StructuredCompressedFile::indexsize RawUncompressedFile::structuredCompressedFileSize() const {
    return m_structuredCompressedFile.size();
}

/* RawCompressedFile pass-thru methods */

RawCompressedFile::streamsize RawUncompressedFile::rawCompressedFileSize() const {
    return m_structuredCompressedFile.rawCompressedFileSize();
}

FileStatistics RawUncompressedFile::statistics() const {
    return m_structuredCompressedFile.statistics();
}

void RawUncompressedFile::setApplication(const BYTE id, const BYTE major, const BYTE minor, const BYTE build) {
    m_structuredCompressedFile.setApplication(id, major, minor, build);
}

void RawUncompressedFile::setApi(const BYTE major, const BYTE minor, const BYTE build, const BYTE patch) {
    m_structuredCompressedFile.setApi(major, minor, build, patch);
}

void RawUncompressedFile::setObjectCount(const DWORD objectCount) {
    m_structuredCompressedFile.setObjectCount(objectCount);
}

void RawUncompressedFile::setObjectsRead(const DWORD objectsRead) {
    m_structuredCompressedFile.setObjectsRead(objectsRead);
}

void RawUncompressedFile::setMeasurementStartTime(const SYSTEMTIME measurementStartTime) {
    m_structuredCompressedFile.setMeasurementStartTime(measurementStartTime);
}

void RawUncompressedFile::setLastObjectTime(const SYSTEMTIME lastObjectTime) {
    m_structuredCompressedFile.setLastObjectTime(lastObjectTime);
}

/* private methods */

void RawUncompressedFile::shrinkLogContainer() {
    if (m_objectRefs.empty()) {
        return;
    }

    /* last log container */
    std::map<streampos, ObjectRef>::iterator objectRef = std::prev(m_objectRefs.end(), 1);

    /* shrink_to_fit last log container */
    streamsize size = m_posp - objectRef->first;
    assert(size >= 0);
    if (size == 0) {
        m_objectRefs.erase(objectRef);
    } else {
        objectRef->second.uncompressedFile.resize(size);
        objectRef->second.fileSize = size;
    }
}

void RawUncompressedFile::writeLogContainer() {
    if (m_objectRefs.empty()) {
        return;
    }

    /* last log container */
    std::map<streampos, ObjectRef>::iterator objectRef = std::prev(m_objectRefs.end(), 1);
    if (objectRef->second.uncompressedFile.empty()) {
        return;
    }

    /* compress and write log container */
    LogContainer * logContainer = new LogContainer;
    logContainer->compress(objectRef->second.uncompressedFile, m_compressionMethod, m_compressionLevel);
    m_structuredCompressedFile.write(logContainer);

    /* update statistics */
    m_statisticsSize += logContainer->internalHeaderSize();
    m_statisticsSize += logContainer->uncompressedFileSize;
}

/* threads */

void RawUncompressedFile::indexThread() {
    // already locked by calling method open

    /* create index of all log containers */
    streampos filePosition = 0;
    m_statisticsSize = 0;
    for(;;) {
        ObjectHeaderBase * objectHeaderBase = nullptr;
        if (!m_structuredCompressedFile.read(&objectHeaderBase)) {
            break;
        }

        /* prepare object reference */
        ObjectRef objectRef;

        /* get log container */
        LogContainer * logContainer = dynamic_cast<LogContainer *>(objectHeaderBase);
        if (logContainer) {
            objectRef.fileSize = logContainer->uncompressedFileSize;

            /* add object reference */
            m_objectRefs[filePosition] = objectRef;

            /* update statistics */
            filePosition += logContainer->uncompressedFileSize;
            m_statisticsSize += logContainer->internalHeaderSize();
            m_statisticsSize += logContainer->uncompressedFileSize;
        } else {
            objectRef.fileSize = objectHeaderBase->objectSize;

            /* add object reference */
            m_objectRefs[filePosition] = objectRef;

            /* update statistics */
            filePosition += objectHeaderBase->objectSize;
            m_statisticsSize += objectHeaderBase->objectSize;
        }

        delete objectHeaderBase;
    }

    /* set file size */
    m_size = filePosition;

    /* seek back to first log container */
    m_structuredCompressedFile.seekg(0);
}

void RawUncompressedFile::readThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo RawUncompressedFile::readThread
}

void RawUncompressedFile::writeThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo RawUncompressedFile::writeThread
}

}
}
