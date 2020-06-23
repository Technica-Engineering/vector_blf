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

#include <Vector/BLF/GlobalMarker.h>
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

    /* read object */
    assert(m_objectRefs[m_posg].objectType != ObjectType::UNKNOWN);
    *objectHeaderBase = makeObject(m_objectRefs[m_posg].objectType);
    assert(*objectHeaderBase); // ensure memory is reserved
    (*objectHeaderBase)->read(m_rawCompressedFile);
    assert((*objectHeaderBase)->signature == ObjectSignature);

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

    /* seek to new file position */
    m_posg = pos;
    assert(m_posg < m_objectRefs.size()); // ensure posg is within index
    m_rawCompressedFile.seekg(m_objectRefs[pos].filePosition);
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

    /* seek to new file position */
    m_posg = ref + off;
    assert(m_posg < m_objectRefs.size()); // ensure posg is within index
    m_rawCompressedFile.seekg(m_objectRefs[m_posg].filePosition);
}

StructuredCompressedFile::indexsize StructuredCompressedFile::write(ObjectHeaderBase * objectHeaderBase) {
    assert(objectHeaderBase);

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* add object reference */
    ObjectRef objectRef;
    objectRef.filePosition = m_rawCompressedFile.tellp();
    objectRef.objectSize = objectHeaderBase->objectSize;
    objectRef.objectType = objectHeaderBase->objectType;
    m_objectRefs[m_objectRefs.size()] = objectRef;

    /* write log container */
    objectHeaderBase->write(m_rawCompressedFile); // @todo do this in writeThread
    delete objectHeaderBase;

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

    /* create index of all objects */
    assert(m_rawCompressedFile.tellg() == m_rawCompressedFile.statistics().statisticsSize); // ensure index starts at 0
    for(indexpos index = 0; ; ++index) {
        /* prepare object reference */
        ObjectRef objectRef;
        objectRef.filePosition = m_rawCompressedFile.tellg();

        /* read object header (not via read function as this would block or throw an exception) */
        DWORD signature;
        WORD headerSize;
        WORD headerVersion;
        //DWORD objectSize => objectRef.objectSize
        //ObjectType objectType => objectRef.objectType
        if (m_rawCompressedFile.read(reinterpret_cast<char *>(&signature), sizeof(signature)) != sizeof(signature)) {
            // end-of-file reached
            break;
        }
        if (signature != ObjectSignature) {
            throw Exception("StructuredCompressedFile::indexThread(): Object signature doesn't match at this position.");
        }
        if (m_rawCompressedFile.read(reinterpret_cast<char *>(&headerSize), sizeof(headerSize)) != sizeof(headerSize)) {
            throw Exception("StructuredCompressedFile::indexThread(): Header size cannot be read.");
        }
        if (m_rawCompressedFile.read(reinterpret_cast<char *>(&headerVersion), sizeof(headerVersion)) != sizeof(headerVersion)) {
            throw Exception("StructuredCompressedFile::indexThread(): Header version cannot be read.");
        }
        if (m_rawCompressedFile.read(reinterpret_cast<char *>(&objectRef.objectSize), sizeof(objectRef.objectSize)) != sizeof(objectRef.objectSize)) {
            throw Exception("StructuredCompressedFile::indexThread(): Object size cannot be read.");
        }
        if (m_rawCompressedFile.read(reinterpret_cast<char *>(&objectRef.objectType), sizeof(objectRef.objectType)) != sizeof(objectRef.objectType)) {
            throw Exception("StructuredCompressedFile::indexThread(): Object type cannot be read.");
        }

        /* fix object size */
        switch(objectRef.objectType) {
        case ObjectType::GLOBAL_MARKER: // 96
        {
            m_rawCompressedFile.seekg(objectRef.filePosition);
            GlobalMarker globalMarker;
            globalMarker.read(m_rawCompressedFile);
            objectRef.objectSize = globalMarker.calculateObjectSize();
        }
            break;
        default:
            break;
        }

        /* add object reference */
        m_objectRefs[index] = objectRef;

        /* jump to next object */
        RawCompressedFile::streamsize offset = objectRef.objectSize;
        switch(objectRef.objectType) {
        case ObjectType::ENV_INTEGER: // 6
        case ObjectType::ENV_DOUBLE: // 7
        case ObjectType::ENV_STRING: // 8
        case ObjectType::ENV_DATA: // 9
        case ObjectType::LOG_CONTAINER: // 10
        case ObjectType::MOST_PKT: // 32
        case ObjectType::MOST_PKT2: // 33
        case ObjectType::APP_TEXT: // 65
        case ObjectType::MOST_ALLOCTAB: // 69
        case ObjectType::ETHERNET_FRAME: // 71
        case ObjectType::SYS_VARIABLE: // 72
        case ObjectType::MOST_150_MESSAGE: // 76
        case ObjectType::MOST_150_PKT: // 77
        case ObjectType::MOST_ETHERNET_PKT: // 78
        case ObjectType::MOST_150_MESSAGE_FRAGMENT: // 79
        case ObjectType::MOST_150_PKT_FRAGMENT: // 80
        case ObjectType::MOST_ETHERNET_PKT_FRAGMENT: // 81
        case ObjectType::MOST_150_ALLOCTAB: // 83
        case ObjectType::MOST_50_MESSAGE: // 84
        case ObjectType::MOST_50_PKT: // 85
        case ObjectType::SERIAL_EVENT: // 90
        case ObjectType::EVENT_COMMENT: // 92
        case ObjectType::WLAN_FRAME: // 93
        case ObjectType::GLOBAL_MARKER: // 96
        case ObjectType::AFDX_FRAME: // 97
        case ObjectType::ETHERNET_RX_ERROR: // 102
            offset += objectRef.objectSize % 4;
        default:
            break;
        }
        m_rawCompressedFile.seekg(objectRef.filePosition + offset);
    }

    /* seek back to first object */
    RawCompressedFile::streampos rawFilePosition = m_objectRefs[0].filePosition;
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
