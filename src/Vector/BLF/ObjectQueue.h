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

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * Thread-safe queue for ObjectHeaderBase
 */
class VECTOR_BLF_EXPORT ObjectQueue {
public:
    explicit ObjectQueue();
    virtual ~ObjectQueue();

    /**
     * open the queue
     */
    virtual void open();

    /**
     * close the queue, but let the queue empty before
     */
    virtual void close();

    /**
     * Get access to front of queue.
     *
     * @return object (or nullptr if empty)
     */
    virtual ObjectHeaderBase * read();

    /** @copydoc AbstractFile::tellg */
    virtual DWORD tellg() const;

    /**
     * Enqueue an object to end of queue.
     *
     * nullptr can be pushed to indicate eof.
     *
     * @param[in] obj object
     */
    void write(ObjectHeaderBase * obj);

    /** @copydoc AbstractFile::tellp */
    virtual DWORD tellp() const;

    /** @copydoc AbstractFile::eof */
    virtual bool eof() const;

    /**
     * Set file size resp. end-of-file position.
     *
     * @param[in] totalObjectCount object count
     */
    virtual void setTotalObjectCount(DWORD totalObjectCount);

    /**
     * Return size of data left to read.
     *
     * @return size
     */
    virtual DWORD size() const;

private:
    /** queue */
    std::queue<ObjectHeaderBase *> m_queue;

    /** read position */
    DWORD m_tellg;

    /** data was dequeued */
    std::condition_variable m_tellgChanged;

    /** write position */
    DWORD m_tellp;

    /** data was enqueued */
    std::condition_variable m_tellpChanged;

    /** eof position */
    DWORD m_totalObjectCount;

    /** error state */
    std::ios_base::iostate m_rdstate;

    /** mutex */
    mutable std::mutex m_mutex;
};

}
}
