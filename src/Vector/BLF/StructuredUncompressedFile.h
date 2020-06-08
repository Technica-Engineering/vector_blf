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

#include <Vector/BLF/ObjectQueue.h>
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

    /** object reference */
    struct ObjectRef {
        std::streampos filePosition;
        DWORD objectSize; // @ref ObjectHeaderBase::objectSize
        ObjectType objectType;

        std::shared_ptr<ObjectHeaderBase> object();

    private:
        std::shared_ptr<ObjectHeaderBase> m_object {};
    };

    /* member types */
    using value_type = ObjectRef;
    using allocator_type = std::allocator<value_type>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = std::iterator<std::random_access_iterator_tag, ObjectRef>;
    using const_iterator = std::iterator<std::random_access_iterator_tag, const ObjectRef>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

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

    /**
     * Current number of objects read
     *
     * Unknown115 is not counted.
     */
    std::atomic<DWORD> currentObjectCount {};

    /**
     * read/write queue
     *
     * When the write method is called the object is enqueued here, so that it returns quickly to the calling
     * application. The readWriteThread gets the objects out of the queue and puts them into the compressedFile.
     *
     * When the read method is called the object is taken out of the queue, so that it returns quickly to the calling
     * application. If there are no objects in the queue, the methods waits for the readWriteThread to finish.
     * The readWriteThread reads objects from the compressedfile and puts them into the queue.
     */
    ObjectQueue<ObjectHeaderBase> m_readWriteQueue {};

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
    std::vector<ObjectRef> m_data {};
};

}
}
