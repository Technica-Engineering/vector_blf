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

#pragma once

#include <Vector/BLF/platform.h>

#include <atomic>
#include <iterator>
#include <vector>

#include <Vector/BLF/ObjectHeaderBase.h>
#include <Vector/BLF/RawUncompressedFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * This class allows std::vector-like access to the uncompressed file.
 */
class VECTOR_BLF_EXPORT StructuredUncompressedFile {
public:
    StructuredUncompressedFile(RawUncompressedFile & rawUncompressedFile);
    ~StructuredUncompressedFile();

    /** object reference */
    struct ObjectRef {
        std::streampos filePosition{0};
        DWORD objectSize {0}; // @ref ObjectHeaderBase::objectSize
        ObjectType objectType {ObjectType::UNKNOWN}; // @ref ObjectHeaderBase::objectType
        ObjectHeaderBase * object {nullptr};
    };

    /* member types */
    using list_type = std::vector<ObjectRef>;
    using value_type = list_type::value_type;
    using allocator_type = list_type::allocator_type;
    using size_type = list_type::size_type;
    using difference_type = list_type::difference_type;
    using reference = list_type::reference;
    using const_reference = list_type::const_reference;
    using pointer = list_type::pointer;
    using const_pointer = list_type::const_pointer;
    using iterator = list_type::iterator;
    using const_iterator = list_type::const_iterator;
    using reverse_iterator = list_type::reverse_iterator;
    using const_reverse_iterator = list_type::const_reverse_iterator;

    /* iterators */
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    /* element access */
    reference at(size_type n);
    const_reference at(size_type n) const;
    reference operator[] (size_type n);
    const_reference operator[] (size_type n) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    /* capacity */
    bool empty() const;
    size_type size() const;

    /* modifiers */
    void clear() noexcept;
    void push_back(const value_type & value);
    void push_back(value_type && value);
    ObjectHeaderBase * read();
    void setMaxSize(size_type count);
    void write(ObjectHeaderBase * value);

    /** @copydoc AbstractFile::tellg */
    virtual difference_type tellg() const;

    /** @copydoc AbstractFile::tellp */
    virtual difference_type tellp() const;

    /** @copydoc AbstractFile::good */
    virtual bool good() const;

    /** @copydoc AbstractFile::eof */
    virtual bool eof() const;

    /** @copydoc UncompressedFile::abort */
    virtual void abort();

    /** @copydoc UncompressedFile::setBufferSize */
    virtual void setBufferSize(DWORD bufferSize);

    /** data was dequeued */
    std::condition_variable posgChanged;

    /** data was enqueued */
    std::condition_variable pospChanged;

    /**
     * Current number of objects read
     *
     * Unknown115 is not counted.
     */
    std::atomic<DWORD> currentObjectCount {};

    /**
     * Read data from uncompressedFile into readWriteQueue.
     */
    void uncompressedFile2ReadWriteQueue();

    /**
     * Write data from readWriteQueue into uncompressedFile.
     */
    void readWriteQueue2UncompressedFile();

private:
    /** raw uncompressed file */
    RawUncompressedFile & m_rawUncompressedFile;

    /** mutex */
    mutable std::mutex m_mutex {};

    /** data */
    list_type m_data {};

    /** abort further operations */
    bool m_abort {false};

    /** get position */
    size_type m_posg {0};

    /** put position */
    size_type m_posp {0};

    /** max position */
    size_type m_max {std::numeric_limits<size_type>::max()};

    /** max buffer size (put pos - get pos) */
    DWORD m_bufferSize {std::numeric_limits<DWORD>::max()};

    /** error state */
    std::ios_base::iostate m_rdstate {std::ios_base::goodbit};
};

}
}
