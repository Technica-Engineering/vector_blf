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

#include <list>
#include <memory>
#include <mutex>

#include <Vector/BLF/LogContainer.h>
#include <Vector/BLF/RawCompressedFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * This class allows object-wise access to the compressed file.
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

    /* member types */
    using value_type = std::shared_ptr<LogContainer>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = std::size_t;

    /* Element access */
//    at
//    operator[]
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

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
    bool empty() const;
//    size_type size() const;

    /* Modifiers */
    void push_back(const value_type & value);
    void push_back(value_type && value);
    void pop_front();

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
    std::list<std::shared_ptr<LogContainer>> m_data {};

    /** default log container size */
    DWORD m_defaultLogContainerSize {0x20000};
};

}
}
