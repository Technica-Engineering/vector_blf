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

#include <Vector/BLF/ObjectQueue.h>

#include <iostream>

namespace Vector {
namespace BLF {

ObjectQueue::ObjectQueue() :
    m_queue(),
    m_eof(false),
    m_mutex(),
    m_newDataPushed()
{
}

ObjectQueue::~ObjectQueue()
{
    close();
}

void ObjectQueue::close()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* free objects */
    while(!m_queue.empty()) {
        ObjectHeaderBase * item = m_queue.front();
        m_queue.pop();
        delete item;
    }

    /* reset end-of-file marker */
    m_eof = false;
}

bool ObjectQueue::empty() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_queue.empty();
}

size_t ObjectQueue::size() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_queue.size();
}

void ObjectQueue::push(ObjectHeaderBase * obj)
{
    std::cout << "ObjectQueue::push()" << std::endl;

    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* push data */
        m_queue.push(obj);
    }

    /* notify */
    m_newDataPushed.notify_all();
}

ObjectHeaderBase * ObjectQueue::front()
{
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait for data */
    std::cout << "ObjectQueue::front(): wait" << std::endl;
    m_newDataPushed.wait(lock, [this]{
        return !m_queue.empty() || m_eof;
    });

    std::cout << "ObjectQueue::front(): proceed" << std::endl;

    /* get first entry */
    ObjectHeaderBase * ohb = nullptr;
    if (!m_queue.empty()) {
        ohb = m_queue.front();

        /* check for eof */
        if (ohb == nullptr) {
            m_queue.pop();
            m_eof = true;
        }
    }
    return ohb;
}

void ObjectQueue::pop()
{
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait for data */
    std::cout << "ObjectQueue::pop(): wait" << std::endl;
    m_newDataPushed.wait(lock, [this]{
        return !m_queue.empty() || m_eof;
    });

    /* pop data */
    std::cout << "ObjectQueue::pop(): proceed" << std::endl;
    if (!m_queue.empty()) {
        m_queue.pop();
    } else {
        m_eof = true;
    }
}

bool ObjectQueue::eof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_eof;
}

}
}
