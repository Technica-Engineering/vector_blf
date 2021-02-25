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

#include <condition_variable>
#include <limits>
#include <mutex>
#include <queue>

#include <Vector/BLF/ObjectHeaderBase.h>
#include <Vector/BLF/LogContainer.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Thread-safe queue for ObjectHeaderBase
 */
template <typename T>
class VECTOR_BLF_EXPORT ObjectQueue final {
  public:
    explicit ObjectQueue() = default;
    ~ObjectQueue();

    /**
     * Get access to front of queue.
     *
     * @return object (or nullptr if empty)
     */
    T * read();

    /** @copydoc AbstractFile::tellg */
    uint32_t tellg() const;

    /**
     * Enqueue an object to end of queue.
     *
     * nullptr can be pushed to indicate eof.
     *
     * @param[in] obj object
     */
    void write(T * obj);

    /** @copydoc AbstractFile::tellp */
    uint32_t tellp() const;

    /** @copydoc AbstractFile::good */
    bool good() const;

    /** @copydoc AbstractFile::eof */
    bool eof() const;

    /** @copydoc UncompressedFile::abort */
    void abort();

    /** @copydoc UncompressedFile::setFileSize */
    void setFileSize(uint32_t fileSize);

    /** @copydoc UncompressedFile::setBufferSize */
    void setBufferSize(uint32_t bufferSize);

    /** data was dequeued */
    std::condition_variable tellgChanged;

    /** data was enqueued */
    std::condition_variable tellpChanged;

  private:
    /** abort further operations */
    bool m_abort {};

    /** queue */
    std::queue<T *> m_queue {};

    /** read position */
    uint32_t m_tellg {};

    /** write position */
    uint32_t m_tellp {};

    /** max size */
    uint32_t m_bufferSize {std::numeric_limits<uint32_t>::max()};

    /** eof position */
    uint32_t m_fileSize {std::numeric_limits<uint32_t>::max()};

    /** error state */
    std::ios_base::iostate m_rdstate {std::ios_base::goodbit};

    /** mutex */
    mutable std::mutex m_mutex {};
};

/* explicit template instantiation */
extern template class ObjectQueue<ObjectHeaderBase>;

}
}
