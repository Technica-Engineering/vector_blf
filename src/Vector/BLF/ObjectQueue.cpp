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
#include <Vector/BLF/LogContainer.h>

namespace Vector {
namespace BLF {

template<typename T>
ObjectQueue<T>::ObjectQueue() :
    tellgChanged(),
    tellpChanged(),
    m_is_open(false),
    m_queue(),
    m_tellg(0),
    m_tellp(0),
    m_maxSize(0xffffffff),
    m_totalObjectCount(0xffffffff),
    m_rdstate(std::ios_base::goodbit),
    m_mutex()
{
}

template<typename T>
ObjectQueue<T>::~ObjectQueue()
{
}

template<typename T>
void ObjectQueue<T>::open()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* reset */
    m_is_open = true;
    while(!m_queue.empty()) {
        T * ohb = m_queue.front();
        m_queue.pop();
        delete ohb;
    }
    m_tellg = 0;
    m_tellp = 0;
    m_maxSize = 0xffffffff;
    m_totalObjectCount = 0xffffffff;
    m_rdstate = std::ios_base::goodbit;
}

template<typename T>
void ObjectQueue<T>::close()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* stop */
    m_is_open = false;

    /* trigger blocked threads */
    tellgChanged.notify_all();
    tellpChanged.notify_all();
}

template<typename T>
T * ObjectQueue<T>::read()
{
    T * ohb = nullptr;
    {
        /* mutex lock */
        std::unique_lock<std::mutex> lock(m_mutex);

        /* wait for data */
        tellpChanged.wait(lock, [this]{
            return
                !m_queue.empty() ||
                !m_is_open ||
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
    tellgChanged.notify_all();

    return ohb;
}

template<typename T>
DWORD ObjectQueue<T>::tellg() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellg;
}

template<typename T>
void ObjectQueue<T>::write(T * obj)
{
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait for free space */
    tellgChanged.wait(lock, [this]{
        return
            !m_is_open ||
            static_cast<DWORD>(m_queue.size()) < m_maxSize;
    });

    /* push data */
    m_queue.push(obj);

    /* increase put count */
    m_tellp++;

    /* shift eof */
    if (m_tellp > m_totalObjectCount) {
        m_totalObjectCount = m_tellp;
    }

    lock.unlock();

    /* notify */
    tellpChanged.notify_all();
}

template<typename T>
DWORD ObjectQueue<T>::tellp() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellp;
}

template<typename T>
bool ObjectQueue<T>::eof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_rdstate & std::ios_base::eofbit);
}

template<typename T>
void ObjectQueue<T>::setTotalObjectCount(DWORD totalObjectCount)
{
    {
        /* mutex lock */
        std::lock_guard<std::mutex> lock(m_mutex);

        /* set object count */
        m_totalObjectCount = totalObjectCount;
    }

    /* notify */
    tellpChanged.notify_all();
}

template<typename T>
bool ObjectQueue<T>::atEof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* next is eof */
    return (m_tellg >= m_totalObjectCount);
}

template<typename T>
DWORD ObjectQueue<T>::size() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* size between put/write and get/read positions */
    return static_cast<DWORD>(m_queue.size());
}

template<typename T>
void ObjectQueue<T>::setMaxSize(DWORD maxSize)
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set max size */
    m_maxSize = maxSize;
}

template class VECTOR_BLF_EXPORT ObjectQueue<ObjectHeaderBase>;
template class VECTOR_BLF_EXPORT ObjectQueue<LogContainer>;

}
}
