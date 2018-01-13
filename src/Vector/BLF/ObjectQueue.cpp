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

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

ObjectQueue::ObjectQueue() :
    m_queue(),
    m_tellg(0),
    m_tellgChanged(),
    m_tellp(0),
    m_tellpChanged(),
    m_totalObjectCount(0),
    m_rdstate(std::ios_base::goodbit),
    m_mutex()
{
}

ObjectQueue::~ObjectQueue()
{
}

void ObjectQueue::open()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* reset */
    while(!m_queue.empty()) {
        ObjectHeaderBase * ohb = m_queue.front();
        m_queue.pop();
        delete ohb;
    }
    m_tellg = 0;
    m_tellp = 0;
    m_totalObjectCount = 0xffffffff;
    m_rdstate = std::ios_base::goodbit;
}

void ObjectQueue::close()
{
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait till the queue is empty */
    m_tellgChanged.wait(lock, [this]{
       return m_queue.empty();
    });
}

ObjectHeaderBase * ObjectQueue::read()
{
    ObjectHeaderBase * ohb = nullptr;
    {
        /* mutex lock */
        std::unique_lock<std::mutex> lock(m_mutex);

        /* wait for data */
        m_tellpChanged.wait(lock, [this]{
            return
                !m_queue.empty() ||
                (m_tellg >= m_totalObjectCount);
        });

        /* get first entry */
        if (m_queue.empty()) {
            m_rdstate = std::ios_base::eofbit;
        } else {
            ohb = m_queue.front();
            m_queue.pop();

            /* set state */
            m_rdstate = std::ios_base::goodbit;

            /* increase get count */
            m_tellg++;
        }
    }

    /* notify */
    m_tellgChanged.notify_all();

    return ohb;
}

DWORD ObjectQueue::tellg() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellg;
}

void ObjectQueue::write(ObjectHeaderBase * obj)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* push data */
        m_queue.push(obj);

        /* increase put count */
        m_tellp++;

        /* shift eof */
        if (m_tellp > m_totalObjectCount) {
            m_totalObjectCount = m_tellp;
        }
    }

    /* notify */
    m_tellpChanged.notify_all();
}

DWORD ObjectQueue::tellp() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellp;
}

bool ObjectQueue::eof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_rdstate & std::ios_base::eofbit);
}

void ObjectQueue::setTotalObjectCount(DWORD totalObjectCount)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* set object count */
        m_totalObjectCount = totalObjectCount;
    }

    /* notify */
    m_tellpChanged.notify_all();
}

bool ObjectQueue::atEof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* next is eof */
    return (m_tellp >= m_totalObjectCount);
}

DWORD ObjectQueue::size() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* size between put/write and get/read positions */
    return (m_tellp - m_tellg);
}

}
}
