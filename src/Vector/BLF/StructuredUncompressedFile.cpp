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

#include <Vector/BLF/StructuredUncompressedFile.h>

#undef NDEBUG
#include <cassert>
#include <iostream>

#include <Vector/BLF/Exceptions.h>
#include <Vector/BLF/File.h>

namespace Vector {
namespace BLF {

StructuredUncompressedFile::StructuredUncompressedFile(RawUncompressedFile & rawUncompressedFile) :
    m_rawUncompressedFile(rawUncompressedFile)
{
}

StructuredUncompressedFile::~StructuredUncompressedFile() {
    close();
}

void StructuredUncompressedFile::open(const char * filename, std::ios_base::openmode mode) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* open file */
    m_rawUncompressedFile.open(filename, mode);
    if (!m_rawUncompressedFile.is_open()) {
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

bool StructuredUncompressedFile::is_open() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_rawUncompressedFile.is_open();
}

void StructuredUncompressedFile::close() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo abort threads and wait to join

    return m_rawUncompressedFile.close();
}

StructuredUncompressedFile::streamsize StructuredUncompressedFile::read(ObjectHeaderBase ** objectHeaderBase) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* check if read position is valid */
    if (m_posg >= m_objectRefs.size()) {
        *objectHeaderBase = nullptr;
        return 0;
    }

    /* seek to object */
    assert(m_posg < m_objectRefs.size()); // ensure posg is within index
    m_rawUncompressedFile.seekg(m_objectRefs[m_posg].filePosition);

    /* read object */
    *objectHeaderBase = makeObject(m_objectRefs[m_posg].objectType);
    assert(*objectHeaderBase); // ensure object is initialized
    (*objectHeaderBase)->read(m_rawUncompressedFile);
    assert((*objectHeaderBase)->objectType == m_objectRefs[m_posg].objectType); // type should match, otherwise index is wrong

    /* update status variables */
    m_posg++;

    return 1;
}

StructuredUncompressedFile::streampos StructuredUncompressedFile::tellg() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_rawUncompressedFile.is_open()) {
        return -1;
    }
    return m_posg;
}

void StructuredUncompressedFile::seekg(const StructuredUncompressedFile::streampos pos) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_posg = pos;
}

void StructuredUncompressedFile::seekg(const StructuredUncompressedFile::streamoff off, const std::ios_base::seekdir way) {
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
        ref = m_objectRefs.size();
        break;
    default:
        assert(false); // other cases should not happen
    }
    m_posg = ref + off;
}

bool StructuredUncompressedFile::write(ObjectHeaderBase * objectHeaderBase) {
    assert(objectHeaderBase); // write no object doesn't make sense

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo StructuredUncompressedFile::write

    return false;
}

StructuredUncompressedFile::streampos StructuredUncompressedFile::tellp() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_rawUncompressedFile.is_open()) {
        return -1;
    }
    return m_objectRefs.size();
}

StructuredUncompressedFile::streamsize StructuredUncompressedFile::size() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_objectRefs.size();
}

FileStatistics StructuredUncompressedFile::statistics() const {
    // no lock needed as just pass-thru
    return m_rawUncompressedFile.statistics();
}

void StructuredUncompressedFile::setStatistics(const Vector::BLF::FileStatistics & statistics) {
    // no lock needed as just pass-thru
    m_rawUncompressedFile.setStatistics(statistics);
}

void StructuredUncompressedFile::indexThread() {
    // already locked by calling method open

    /* create index of all objects */
    assert(m_rawUncompressedFile.tellg() == 0); // ensure index starts at 0
    for(;;) {
        /* prepare object reference */
        ObjectRef objectRef;
        objectRef.filePosition = m_rawUncompressedFile.tellg();

        /* read object header (not via read function as this would potentially throw an exception) */
        DWORD signature;
        WORD headerSize;
        WORD headerVersion;
        // DWORD objectSize => objectRef.objectSize
        // ObjectType objectType => objectRef.objectType
        if (m_rawUncompressedFile.read(reinterpret_cast<char *>(&signature), sizeof(signature)) != sizeof(signature)) {
            // end-of-file reached
            break;
        }
        if (signature != ObjectSignature) {
            throw Exception("StructuredUncompressedFile::indexThread(): Object signature doesn't match at this position.");
        }
        if (m_rawUncompressedFile.read(reinterpret_cast<char *>(&headerSize), sizeof(headerSize)) +
            m_rawUncompressedFile.read(reinterpret_cast<char *>(&headerVersion), sizeof(headerVersion)) +
            m_rawUncompressedFile.read(reinterpret_cast<char *>(&objectRef.objectSize), sizeof(objectRef.objectSize)) +
            m_rawUncompressedFile.read(reinterpret_cast<char *>(&objectRef.objectType), sizeof(objectRef.objectType)) !=
            sizeof(headerSize) + sizeof(headerVersion) + sizeof(objectRef.objectSize) + sizeof(objectRef.objectType)) {
            throw Exception("StructuredUncompressedFile::indexThread(): Object Header cannot be read.");
        }

        /* add object reference */
        m_objectRefs.push_back(objectRef);

        /* jump to next object */
        RawUncompressedFile::streamsize offset = objectRef.objectSize;
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
        m_rawUncompressedFile.seekg(objectRef.filePosition + offset);
    }

    /* seek back to first log container */
    RawUncompressedFile::streampos rawFilePosition = m_objectRefs.front().filePosition;
    m_rawUncompressedFile.seekg(rawFilePosition);
}

void StructuredUncompressedFile::readThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo StructuredUncompressedFile::readThread
}

void StructuredUncompressedFile::writeThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo StructuredUncompressedFile::writeThread
}

}
}
