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

#include <iterator>
#include <memory>
#include <mutex>
#include <vector>

#include <Vector/BLF/LogContainer.h>
#include <Vector/BLF/RawCompressedFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * This class allows std::vector-like access to the compressed file.
 */
class VECTOR_BLF_EXPORT StructuredCompressedFile {
public:
    StructuredCompressedFile(RawCompressedFile & rawCompressedFile);

    /**
     * Get default log container size.
     *
     * @return default log container size
     */
    virtual DWORD defaultLogContainerSize() const;

    /**
     * Set default log container size.
     *
     * @param[in] defaultLogContainerSize default log container size
     */
    virtual void setDefaultLogContainerSize(DWORD defaultLogContainerSize);

    /** object reference */
    struct LogContainerRef {
        std::streampos filePosition;
        DWORD objectSize; // @ref ObjectHeaderBase::objectSize
        ObjectType objectType;

        std::shared_ptr<LogContainer> logContainer();

    private:
        std::shared_ptr<LogContainer> m_logContainer {};
    };

    /* member types */
    using value_type = std::shared_ptr<LogContainer>; // @todo change to LogContainerRef
    using allocator_type = std::allocator<value_type>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = std::iterator<std::random_access_iterator_tag, LogContainerRef>;
    using const_iterator = std::iterator<std::random_access_iterator_tag, const LogContainerRef>;
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
     * Returns the file container, which contains pos.
     *
     * Searches through the data vector to find the logContainer, which contains the position.
     * If the position is behind the last logContainer, return nullptr to indicate a new
     * LogContainer need to be appended.
     *
     * @param[in] pos position
     * @return log container or nullptr
     */
    value_type logContainerContaining(std::streampos pos);

private:
    /** raw compressed file */
    RawCompressedFile & m_rawCompressedFile;

    /** mutex */
    mutable std::mutex m_mutex {};

    /** data */
    std::vector<value_type> m_data {};

    /** default log container size */
    DWORD m_defaultLogContainerSize {0x20000};

    /** prepare a new log container */
    void init(reference logContainerRef);

    /** load log container from RawUncompressedFile */
    void load(reference logContainerRef);

    /** save log container to RawUncompressedFile */
    void save(reference logContainerRef);
};

}
}
