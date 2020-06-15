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
        indexThread(); // @todo make this a thread
        // @todo start normal read thread
    }

    /* start write thread */
    if (m_openMode & std::ios_base::out) {
        // @todo write thread
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

    // @todo abort read thread
    // @todo wait till read/write threads finished

    return m_rawUncompressedFile.close();
}

ObjectHeaderBase * StructuredUncompressedFile::read() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* check if read position is valid */
    if (m_posg >= m_objectRefs.size()) {
        return nullptr;
    }

    /* seek to object */
    RawUncompressedFile::streampos rawFilePosition = m_objectRefs[m_posg].filePosition;
    m_rawUncompressedFile.seekg(rawFilePosition);

    /* read object header (not via read function as this would block) */
    DWORD signature;
    WORD headerSize;
    WORD headerVersion;
    DWORD objectSize;
    ObjectType objectType;
    if (m_rawUncompressedFile.read(reinterpret_cast<char *>(&signature), sizeof(signature)) != sizeof(signature)) {
        return nullptr;
    }
    if (signature != ObjectSignature)
        throw Exception("StructuredCompressedFile::indexThread(): Object signature doesn't match at this position.");
    m_rawUncompressedFile.read(reinterpret_cast<char *>(&headerSize), sizeof(headerSize));
    m_rawUncompressedFile.read(reinterpret_cast<char *>(&headerVersion), sizeof(headerVersion));
    m_rawUncompressedFile.read(reinterpret_cast<char *>(&objectSize), sizeof(objectSize));
    m_rawUncompressedFile.read(reinterpret_cast<char *>(&objectType), sizeof(objectType));
    m_rawUncompressedFile.seekg(rawFilePosition);

    /* read object */
    ObjectHeaderBase * ohb = makeObject(objectType);
    ohb->read(m_rawUncompressedFile);

    /* update status variables */
    m_posg++;

    return ohb;
}

StructuredUncompressedFile::streampos StructuredUncompressedFile::tellg() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

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
    StructuredCompressedFile::streampos pos;
    switch(way) {
    case std::ios_base::beg:
        pos = 0;
        break;
    case std::ios_base::cur:
        pos = m_posg;
        break;
    case std::ios_base::end:
        pos = m_objectRefs.size();
        break;
    default:
        assert(false);
    }
    pos += off;

    m_posg = pos;
}

bool StructuredUncompressedFile::write(ObjectHeaderBase * objectHeaderBase) {
    assert(objectHeaderBase);

    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo

    return false;
}

StructuredUncompressedFile::streampos StructuredUncompressedFile::tellp() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_posp;
}

void StructuredUncompressedFile::indexThread() {
    std::cout << __PRETTY_FUNCTION__ << ": IndexThread starts" << std::endl;
    // already locked by calling method open

    /* create index of all objects */
    assert(m_rawUncompressedFile.tellg() == 0);
    for(;;) {
        /* prepare ObjectRef */
        ObjectRef objectRef;
        objectRef.filePosition = m_rawUncompressedFile.tellg();
        std::cout << __PRETTY_FUNCTION__ << ": Checking file position 0x" << std::hex << m_rawUncompressedFile.tellg() << std::endl;

        /* read object header (not via read function as this would potentially throw an exception) */
        DWORD signature;
        WORD headerSize;
        WORD headerVersion;
        DWORD objectSize;
        ObjectType objectType;
        if (m_rawUncompressedFile.read(reinterpret_cast<char *>(&signature), sizeof(signature)) != sizeof(signature)) {
            break;
        }
        if (signature != ObjectSignature)
            throw Exception("StructuredUncompressedFile::indexThread(): Object signature doesn't match at this position.");
        m_rawUncompressedFile.read(reinterpret_cast<char *>(&headerSize), sizeof(headerSize));
        m_rawUncompressedFile.read(reinterpret_cast<char *>(&headerVersion), sizeof(headerVersion));
        m_rawUncompressedFile.read(reinterpret_cast<char *>(&objectSize), sizeof(objectSize));
        m_rawUncompressedFile.read(reinterpret_cast<char *>(&objectType), sizeof(objectType));

        /* add object reference */
        objectRef.objectSize = objectSize;
        objectRef.objectType = objectType;
        m_objectRefs.push_back(objectRef);
        std::cout << __PRETTY_FUNCTION__ << ": Object at 0x" << std::hex << objectRef.filePosition << " size 0x" << std::hex << objectRef.objectSize << std::endl;

        /* jump to next object */
        m_rawUncompressedFile.seekg(objectRef.filePosition + RawUncompressedFile::streamsize(objectSize));
    }

    /* seek back to first log container */
    RawUncompressedFile::streampos rawFilePosition = m_objectRefs.front().filePosition;
    m_rawUncompressedFile.seekg(rawFilePosition);
}

void StructuredUncompressedFile::readThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

void StructuredUncompressedFile::writeThread() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

}
}
