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

#include <Vector/BLF/ObjectQueue.h>
#include <Vector/BLF/RawUncompressedFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * This class allows object-wise access to the uncompressed file.
 */
class VECTOR_BLF_EXPORT StructuredUncompressedFile {
public:
    StructuredUncompressedFile(RawUncompressedFile & rawUncompressedFile);

    /* member types */
//    using value_type = std::shared_ptr<LogContainer>;
//    using reference = value_type&;
//    using const_reference = const value_type&;
//    using pointer = value_type*;
//    using const_pointer = const value_type*;
//    using size_type = std::size_t;

    /* Element access */
//    at
//    operator[]
//    reference front();
//    const_reference front() const;
//    reference back();
//    const_reference back() const;

    /* Iterators */
//    begin();
//    cbegin();
//    end();
//    cend();
//    rbegin();
//    crbegin();
//    rend();
//    crend();

    /* Capacity */
//    bool empty() const;
//    size_type size() const;

    /* Modifiers */
//    void push_back(const value_type & value);
//    void push_back(value_type && value);
//    void pop_front();

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
};

}
}
