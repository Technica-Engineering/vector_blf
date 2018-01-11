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
     * clear the queue
     */
    virtual void close();

    /**
     * Check if queue is empty.
     *
     * @return true if empty
     */
    virtual bool empty() const;

    /**
     * Return number of objects in queue.
     *
     * @return number of objects
     */
    virtual size_t size() const;

    /**
     * Push an object to end of queue.
     *
     * nullptr can be pushed to indicate eof.
     *
     * @param[in] obj object
     */
    void push(ObjectHeaderBase * obj);

    /**
     * Get access to front of queue.
     *
     * @return object (or nullptr if empty)
     */
    virtual ObjectHeaderBase * front();

    /**
     * Pop the first object.
     */
    virtual void pop();

    /**
     * get end-of-file marker
     */
    virtual bool eof() const;

private:
    /** queue */
    std::queue<ObjectHeaderBase *> m_queue;

    /** end-of-file */
    bool m_eof;

    /** mutex */
    mutable std::mutex m_mutex;

    /** new data arrived */
    std::condition_variable m_newDataPushed;

};

}
}
