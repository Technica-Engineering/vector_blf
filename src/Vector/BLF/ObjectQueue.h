/*
 * Copyright (C) 2013 Tobias Lorenz.
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
class VECTOR_BLF_EXPORT ObjectQueue {
public:
    explicit ObjectQueue();
    virtual ~ObjectQueue();

    /**
     * open the queue
     */
    virtual void open();

    /**
     * close the queue
     */
    virtual void close();

    /**
     * Get access to front of queue.
     *
     * @return object (or nullptr if empty)
     */
    virtual T * read();

    /** @copydoc AbstractFile::tellg */
    virtual DWORD tellg() const;

    /**
     * Enqueue an object to end of queue.
     *
     * nullptr can be pushed to indicate eof.
     *
     * @param[in] obj object
     */
    void write(T * obj);

    /** @copydoc AbstractFile::tellp */
    virtual DWORD tellp() const;

    /** @copydoc AbstractFile::flush */
    virtual void flush();

    /** @copydoc AbstractFile::good */
    virtual bool good() const;

    /** @copydoc AbstractFile::eof */
    virtual bool eof() const;

    /**
     * Set file size resp. end-of-file position.
     *
     * @param[in] totalObjectCount object count
     */
    virtual void setTotalObjectCount(DWORD totalObjectCount);

    /** @copydoc UncompressedFile::eof */
    virtual bool atEof() const;

    /**
     * Return size of data left to read.
     *
     * @return size
     */
    virtual DWORD size() const;

    /**
     * Sets the maximum queue size.
     * Write operations block, if the size is reached.
     *
     * @param[in] maxSize maximum queue size
     */
    virtual void setMaxSize(DWORD maxSize);

    /** data was dequeued */
    std::condition_variable tellgChanged;

    /** data was enqueued */
    std::condition_variable tellpChanged;

private:
    /** is queue open? */
    bool m_is_open;

    /** queue */
    std::queue<T *> m_queue;

    /** read position */
    DWORD m_tellg;

    /** write position */
    DWORD m_tellp;

    /** max size */
    DWORD m_maxSize;

    /** eof position */
    DWORD m_totalObjectCount;

    /** error state */
    std::ios_base::iostate m_rdstate;

    /** mutex */
    mutable std::mutex m_mutex;
};

template class VECTOR_BLF_EXPORT ObjectQueue<ObjectHeaderBase>;

}
}
