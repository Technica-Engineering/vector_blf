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

#include <Vector/BLF/Exceptions.h>
#include <Vector/BLF/File.h>
#include <Vector/BLF/ObjectHeaderBase.h>

namespace Vector {
namespace BLF {

StructuredUncompressedFile::StructuredUncompressedFile(RawUncompressedFile & rawUncompressedFile) :
    m_rawUncompressedFile(rawUncompressedFile)
{
}

StructuredUncompressedFile::~StructuredUncompressedFile() {
    abort();
}

/* iterators */

StructuredUncompressedFile::iterator StructuredUncompressedFile::begin() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_iterator StructuredUncompressedFile::begin() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_iterator StructuredUncompressedFile::cbegin() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::iterator StructuredUncompressedFile::end() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_iterator StructuredUncompressedFile::end() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_iterator StructuredUncompressedFile::cend() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::reverse_iterator StructuredUncompressedFile::rbegin() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_reverse_iterator StructuredUncompressedFile::rbegin() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_reverse_iterator StructuredUncompressedFile::crbegin() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::reverse_iterator StructuredUncompressedFile::rend() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_reverse_iterator StructuredUncompressedFile::rend() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_reverse_iterator StructuredUncompressedFile::crend() const noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

/* element access */

StructuredUncompressedFile::reference StructuredUncompressedFile::at(size_type n) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_reference StructuredUncompressedFile::at(size_type n) const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::reference StructuredUncompressedFile::operator[] (size_type n) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_reference StructuredUncompressedFile::operator[] (size_type n) const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::reference StructuredUncompressedFile::front() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_reference StructuredUncompressedFile::front() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::reference StructuredUncompressedFile::back() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::const_reference StructuredUncompressedFile::back() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

/* capacity */

bool StructuredUncompressedFile::empty() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

StructuredUncompressedFile::size_type StructuredUncompressedFile::size() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

/* modifiers */

void StructuredUncompressedFile::clear() noexcept {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

void StructuredUncompressedFile::push_back(const StructuredUncompressedFile::value_type & value) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

void StructuredUncompressedFile::push_back(StructuredUncompressedFile::value_type && value) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    // @todo
}

ObjectHeaderBase * StructuredUncompressedFile::read() {
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait for data */
    pospChanged.wait(lock, [&] {
        return
        m_abort ||
        (m_posg < m_posp) || // if data available
        (m_posg >= m_max); // if end reached
    });

    /* get first entry */
    ObjectHeaderBase * ohb = nullptr;
    if (m_posg >= m_posp) {
        m_rdstate = std::ios_base::eofbit | std::ios_base::failbit;
    } else {
        ohb = m_data[m_posg].object;
        assert(ohb);

        /* set state */
        m_rdstate = std::ios_base::goodbit;

        /* increase get count */
        ++m_posg;
    }

    /* notify */
    posgChanged.notify_all();

    return ohb;
}

void StructuredUncompressedFile::setMaxSize(size_type count) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set object count */
    m_max = count;

    /* notify */
    pospChanged.notify_all();
}

void StructuredUncompressedFile::write(ObjectHeaderBase * value) {
    assert(value);

    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait for free space */
    posgChanged.wait(lock, [&] {
        return
        m_abort ||
        ((m_posp - m_posg) < m_bufferSize);
    });

    if (m_posp >= m_data.size()) {
        m_data.resize(m_posp + 1);
    }

    /* push data */
    m_data[m_posp].object = value;

    /* increase put count */
    ++m_posp;

    /* notify */
    pospChanged.notify_all();
}

StructuredUncompressedFile::difference_type StructuredUncompressedFile::tellg() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_posg;
}

StructuredUncompressedFile::difference_type StructuredUncompressedFile::tellp() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_posp;
}

bool StructuredUncompressedFile::good() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_rdstate == std::ios_base::goodbit);
}

bool StructuredUncompressedFile::eof() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_rdstate & std::ios_base::eofbit);
}

void StructuredUncompressedFile::abort() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* stop */
    m_abort = true;

    /* trigger blocked threads */
    posgChanged.notify_all();
    pospChanged.notify_all();
}

void StructuredUncompressedFile::setBufferSize(DWORD bufferSize) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set max size */
    m_bufferSize = bufferSize;
}

void StructuredUncompressedFile::uncompressedFile2ReadWriteQueue() {
    /* identify type */
    ObjectHeaderBase ohb(0, ObjectType::UNKNOWN);
    ohb.read(m_rawUncompressedFile);
    if (!m_rawUncompressedFile.good()) {
        /* This is a normal eof. No objects ended abruptly. */
        return;
    }
    m_rawUncompressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);

    /* create object */
    ObjectHeaderBase * obj = makeObject(ohb.objectType);
    if (obj == nullptr) {
        /* in case of unknown objectType */
        throw Exception("StructuredUncompressedFile::uncompressedFile2ReadWriteQueue(): Unknown object.");
    }

    /* read object */
    obj->read(m_rawUncompressedFile);
    if (!m_rawUncompressedFile.good()) {
        delete obj;
        throw Exception("StructuredUncompressedFile::uncompressedFile2ReadWriteQueue(): Read beyond end of file.");
    }

    /* push data into readWriteQueue */
    write(obj);

    /* statistics */
    if (obj->objectType != ObjectType::Unknown115)
        currentObjectCount++;

    /* drop old data */
    m_rawUncompressedFile.dropOldData();
}

void StructuredUncompressedFile::readWriteQueue2UncompressedFile() {
    /* get from readWriteQueue */
    ObjectHeaderBase * ohb = read();

    /* process data */
    if (ohb == nullptr) {
        // Read intentionally returns, when the thread is aborted.
        return;
    }

    /* write into uncompressedFile */
    ohb->write(m_rawUncompressedFile);

    /* statistics */
    if (ohb->objectType != ObjectType::Unknown115)
        currentObjectCount++;

    /* delete object */
    delete ohb;
}

}
}
